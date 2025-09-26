#!/usr/bin/env python3
import sys
import re
import pygame
import math
import time
from collections import defaultdict

# Initialize Pygame
pygame.init()

# Colors (beautiful modern palette)
COLORS = {
    'background': (25, 25, 35),
    'grid': (45, 45, 55),
    'room_normal': (220, 220, 230),
    'room_start': (102, 255, 102),
    'room_end': (255, 102, 102),
    'room_border': (60, 60, 70),
    'connection': (100, 200, 100),
    'ant': (255, 165, 0),
    'ant_trail': (255, 200, 100),
    'text': (255, 255, 255),
    'button': (70, 130, 180),
    'button_hover': (100, 149, 237),
    'button_text': (255, 255, 255)
}

class Button:
    def __init__(self, x, y, width, height, text, action):
        self.rect = pygame.Rect(x, y, width, height)
        self.text = text
        self.action = action
        self.hovered = False
        self.font = pygame.font.Font(None, 24)
    
    def handle_event(self, event):
        if event.type == pygame.MOUSEMOTION:
            self.hovered = self.rect.collidepoint(event.pos)
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if self.rect.collidepoint(event.pos):
                self.action()
    
    def draw(self, screen):
        color = COLORS['button_hover'] if self.hovered else COLORS['button']
        pygame.draw.rect(screen, color, self.rect)
        pygame.draw.rect(screen, COLORS['button_text'], self.rect, 2)
        
        text_surface = self.font.render(self.text, True, COLORS['button_text'])
        text_rect = text_surface.get_rect(center=self.rect.center)
        screen.blit(text_surface, text_rect)

class Ant:
    def __init__(self, ant_id, start_pos):
        self.id = ant_id
        self.pos = list(start_pos)
        self.target_pos = list(start_pos)
        self.current_room = None
        self.trail = [start_pos.copy()]
        self.base_speed = 3.0
        self.current_speed = 3.0
        self.movement_queue = []  # Queue of positions to visit
        self.movement_start_time = 0
        self.movement_duration = 1.0  # Time to complete current movement
        
    def update(self, current_time):
        # If we have movements in queue and reached current target
        if self.movement_queue and self.at_target():
            next_move = self.movement_queue.pop(0)
            self.start_movement_to(next_move['pos'], next_move['room'], current_time, next_move.get('duration', 1.0))
        
        # Smooth movement towards current target based on time
        if self.movement_start_time > 0:
            elapsed = current_time - self.movement_start_time
            progress = min(elapsed / self.movement_duration, 1.0)
            
            if progress >= 1.0:
                # Movement complete
                self.pos = self.target_pos.copy()
                self.movement_start_time = 0
            else:
                # Interpolate position
                start_x, start_y = self.movement_start_pos
                target_x, target_y = self.target_pos
                self.pos[0] = start_x + (target_x - start_x) * progress
                self.pos[1] = start_y + (target_y - start_y) * progress
            
        # Update trail (keep last 10 positions)
        if len(self.trail) == 0 or math.sqrt((self.trail[-1][0] - self.pos[0])**2 + (self.trail[-1][1] - self.pos[1])**2) > 5:
            self.trail.append(self.pos.copy())
            if len(self.trail) > 10:
                self.trail.pop(0)
    
    def at_target(self):
        """Check if ant has reached its current target"""
        return self.movement_start_time == 0
    
    def start_movement_to(self, pos, room, start_time, duration=1.0):
        """Start movement to new position with specified duration"""
        self.movement_start_pos = self.pos.copy()
        self.target_pos = list(pos)
        self.current_room = room
        self.movement_start_time = start_time
        self.movement_duration = duration
    
    def add_movement(self, pos, room, duration=1.0):
        """Add movement to queue with duration"""
        self.movement_queue.append({'pos': list(pos), 'room': room, 'duration': duration})
    
    def set_target(self, pos, room, current_time):
        """Set immediate target (for step mode)"""
        self.start_movement_to(pos, room, current_time, 1.0)
    
    def draw(self, screen):
        # Draw trail
        for i, trail_pos in enumerate(self.trail):
            alpha = (i + 1) / len(self.trail)
            radius = int(3 * alpha)
            if radius > 0:
                color = tuple(int(c * alpha + COLORS['background'][j] * (1 - alpha)) 
                             for j, c in enumerate(COLORS['ant_trail']))
                pygame.draw.circle(screen, color, (int(trail_pos[0]), int(trail_pos[1])), radius)
        
        # Draw ant body
        pygame.draw.circle(screen, COLORS['ant'], (int(self.pos[0]), int(self.pos[1])), 8)
        pygame.draw.circle(screen, (200, 120, 0), (int(self.pos[0]), int(self.pos[1])), 8, 2)
        
        # Draw ant ID
        font = pygame.font.Font(None, 16)
        text = font.render(str(self.id), True, (0, 0, 0))
        text_rect = text.get_rect(center=(int(self.pos[0]), int(self.pos[1])))
        screen.blit(text, text_rect)

class LemInVisualizer:
    def __init__(self):
        self.screen = pygame.display.set_mode((1200, 800))
        pygame.display.set_caption("Lem-in Visualizer - Pygame Edition")
        self.clock = pygame.time.Clock()
        
        self.nodes = {}
        self.movements = {}
        self.ants = {}
        self.start_room = ""
        self.end_room = ""
        self.ant_count = 0
        
        # Animation state
        self.current_step = 0
        self.is_playing = False
        self.speed = 60  # FPS
        self.step_delay = 0
        self.last_step_time = 0
        self.step_duration = 1.5  # Duration for each step in seconds
        
        # UI elements
        self.buttons = []
        self.font = pygame.font.Font(None, 36)
        self.small_font = pygame.font.Font(None, 24)
        
        self.setup_ui()
        
    def setup_ui(self):
        # Control buttons
        button_y = 20
        self.buttons = [
            Button(20, button_y, 80, 40, "Play", self.play),
            Button(110, button_y, 80, 40, "Pause", self.pause),
            Button(200, button_y, 80, 40, "Reset", self.reset),
            Button(290, button_y, 80, 40, "Step", self.step),
        ]
    
    def parse_input(self):
        """Parse lem-in input"""
        i = 0
        j = 0
        
        for line in sys.stdin:
            line = line.strip()
            if i == 0:
                self.ant_count = int(line)
            elif line.startswith('#'):
                if line == "##start":
                    line = sys.stdin.readline().strip()
                    parts = line.split(' ')
                    self.start_room = parts[0]
                    self.nodes[parts[0]] = {
                        'x': float(parts[1]),
                        'y': float(parts[2]),
                        'connections': [],
                        'type': 'start'
                    }
                elif line == "##end":
                    line = sys.stdin.readline().strip()
                    parts = line.split(' ')
                    self.end_room = parts[0]
                    self.nodes[parts[0]] = {
                        'x': float(parts[1]),
                        'y': float(parts[2]),
                        'connections': [],
                        'type': 'end'
                    }
            elif 'L' in line:
                moves = line.split(' ')
                self.movements[j] = []
                for move in moves:
                    if 'L' in move and '-' in move:
                        ant_num = int(move[1:move.find('-')])
                        room = move[move.find('-') + 1:]
                        self.movements[j].append([ant_num, room])
                j += 1
            elif ' ' in line and not line.startswith('#'):
                parts = line.split(' ')
                if len(parts) >= 3 and parts[1] != 'is':
                    room_name = parts[0]
                    if room_name not in self.nodes:
                        self.nodes[room_name] = {
                            'x': float(parts[1]),
                            'y': float(parts[2]),
                            'connections': [],
                            'type': 'normal'
                        }
            elif '-' in line and not line.startswith('#'):
                parts = line.split('-')
                if len(parts) == 2:
                    room1, room2 = parts[0], parts[1]
                    if room1 in self.nodes and room2 in self.nodes:
                        self.nodes[room1]['connections'].append(room2)
                        self.nodes[room2]['connections'].append(room1)
            i += 1
        
        self.normalize_coordinates()
        self.create_ants()
    
    def normalize_coordinates(self):
        """Normalize coordinates to fit the screen"""
        if not self.nodes:
            return
            
        min_x = min(node['x'] for node in self.nodes.values())
        max_x = max(node['x'] for node in self.nodes.values())
        min_y = min(node['y'] for node in self.nodes.values())
        max_y = max(node['y'] for node in self.nodes.values())
        
        # Canvas area (leaving space for UI)
        canvas_x = 50
        canvas_y = 100
        canvas_width = self.screen.get_width() - 100
        canvas_height = self.screen.get_height() - 150
        
        # Scale to fit canvas
        scale_x = canvas_width / (max_x - min_x) if max_x != min_x else 1
        scale_y = canvas_height / (max_y - min_y) if max_y != min_y else 1
        scale = min(scale_x, scale_y) * 0.8  # 80% of available space
        
        for node in self.nodes.values():
            node['screen_x'] = canvas_x + (node['x'] - min_x) * scale
            node['screen_y'] = canvas_y + (node['y'] - min_y) * scale
    
    def create_ants(self):
        """Create ant objects"""
        if self.start_room in self.nodes:
            start_pos = [self.nodes[self.start_room]['screen_x'], 
                        self.nodes[self.start_room]['screen_y']]
            for i in range(1, self.ant_count + 1):
                self.ants[i] = Ant(i, start_pos)
    
    def play(self):
        self.is_playing = True
    
    def pause(self):
        self.is_playing = False
    
    def reset(self):
        self.is_playing = False
        self.current_step = 0
        # Clear movement queues and reset positions
        if self.start_room in self.nodes:
            start_pos = [self.nodes[self.start_room]['screen_x'], 
                        self.nodes[self.start_room]['screen_y']]
            for i in range(1, self.ant_count + 1):
                self.ants[i] = Ant(i, start_pos)
    
    def step(self):
        self.is_playing = False
        if self.current_step < len(self.movements):
            moves = self.movements.get(self.current_step, [])
            current_time = time.time()
            
            for ant_num, room in moves:
                if ant_num in self.ants and room in self.nodes:
                    target_pos = [self.nodes[room]['screen_x'], self.nodes[room]['screen_y']]
                    # In step mode, set target directly for immediate movement
                    self.ants[ant_num].set_target(target_pos, room, current_time)
            self.current_step += 1
    
    def advance_step(self):
        """Advance one step in the animation"""
        if self.current_step < len(self.movements):
            moves = self.movements.get(self.current_step, [])
            current_time = time.time()
            
            for ant_num, room in moves:
                if ant_num in self.ants and room in self.nodes:
                    target_pos = [self.nodes[room]['screen_x'], self.nodes[room]['screen_y']]
                    # Add movement to queue with synchronized duration
                    self.ants[ant_num].add_movement(target_pos, room, self.step_duration)
            self.current_step += 1
    
    def draw_connections(self):
        """Draw connections between rooms"""
        drawn = set()
        for room_name, node in self.nodes.items():
            for connected_room in node['connections']:
                connection = tuple(sorted([room_name, connected_room]))
                if connection not in drawn:
                    drawn.add(connection)
                    start_pos = (int(node['screen_x']), int(node['screen_y']))
                    end_pos = (int(self.nodes[connected_room]['screen_x']), 
                              int(self.nodes[connected_room]['screen_y']))
                    pygame.draw.line(self.screen, COLORS['connection'], start_pos, end_pos, 3)
    
    def draw_rooms(self):
        """Draw room nodes"""
        for room_name, node in self.nodes.items():
            pos = (int(node['screen_x']), int(node['screen_y']))
            
            # Room circle
            if node['type'] == 'start':
                color = COLORS['room_start']
            elif node['type'] == 'end':
                color = COLORS['room_end']
            else:
                color = COLORS['room_normal']
            
            pygame.draw.circle(self.screen, color, pos, 20)
            pygame.draw.circle(self.screen, COLORS['room_border'], pos, 20, 3)
            
            # Room name
            text = self.small_font.render(room_name, True, COLORS['text'])
            text_rect = text.get_rect(center=(pos[0], pos[1] + 35))
            self.screen.blit(text, text_rect)
    
    def draw_ui(self):
        """Draw UI elements"""
        # Title
        title = self.font.render("Lem-in Visualizer", True, COLORS['text'])
        self.screen.blit(title, (400, 25))
        
        # Step counter
        step_text = f"Step: {self.current_step} / {len(self.movements)}"
        step_surface = self.small_font.render(step_text, True, COLORS['text'])
        self.screen.blit(step_surface, (600, 35))
        
        # Ant counter
        ant_text = f"Ants: {self.ant_count}"
        ant_surface = self.small_font.render(ant_text, True, COLORS['text'])
        self.screen.blit(ant_surface, (750, 35))
        
        # Speed control
        speed_text = f"Speed: {self.step_duration:.1f}s per step"
        speed_surface = self.small_font.render(speed_text, True, COLORS['text'])
        self.screen.blit(speed_surface, (850, 35))
        
        # Draw buttons
        for button in self.buttons:
            button.draw(self.screen)
    
    def handle_events(self):
        """Handle pygame events"""
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                return False
            
            # Handle button events
            for button in self.buttons:
                button.handle_event(event)
            
            # Speed control with mouse wheel
            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 4:  # Mouse wheel up - faster
                    self.step_duration = max(0.5, self.step_duration - 0.2)
                elif event.button == 5:  # Mouse wheel down - slower
                    self.step_duration = min(3.0, self.step_duration + 0.2)
            
            # Keyboard shortcuts
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    if self.is_playing:
                        self.pause()
                    else:
                        self.play()
                elif event.key == pygame.K_r:
                    self.reset()
                elif event.key == pygame.K_s:
                    self.step()
        
        return True
    
    def update(self):
        """Update animation state"""
        current_time = time.time()
        
        # Update ants with current time
        for ant in self.ants.values():
            ant.update(current_time)
        
        # Auto-advance steps - wait for step duration before next step
        if self.is_playing:
            if current_time - self.last_step_time >= self.step_duration:
                if self.current_step < len(self.movements):
                    self.advance_step()
                    self.last_step_time = current_time
                else:
                    self.is_playing = False
    
    def draw(self):
        """Draw everything"""
        self.screen.fill(COLORS['background'])
        
        # Draw grid pattern for aesthetics
        for x in range(0, self.screen.get_width(), 50):
            pygame.draw.line(self.screen, COLORS['grid'], (x, 100), (x, self.screen.get_height()), 1)
        for y in range(100, self.screen.get_height(), 50):
            pygame.draw.line(self.screen, COLORS['grid'], (0, y), (self.screen.get_width(), y), 1)
        
        self.draw_connections()
        self.draw_rooms()
        
        # Draw ants
        for ant in self.ants.values():
            ant.draw(self.screen)
        
        self.draw_ui()
        pygame.display.flip()
    
    def run(self):
        """Main game loop"""
        self.parse_input()
        
        running = True
        while running:
            running = self.handle_events()
            self.update()
            self.draw()
            self.clock.tick(60)  # 60 FPS
        
        pygame.quit()

def main():
    visualizer = LemInVisualizer()
    visualizer.run()

if __name__ == "__main__":
    main()