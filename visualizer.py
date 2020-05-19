import sys
import re
from tkinter import *


def print_movement():
    global c1
    for ant in movement:
        if abs(n[ant[1]][0] - ants_state[ant[0]][0]) >= 0.01 or abs(n[ant[1]][1] - ants_state[ant[0]][1]) >= 0.01:
            c1.move(ants_state[ant[0]][2], speed_mass[ant[0]][0], speed_mass[ant[0]][1])
            ants_state[ant[0]][0] += (speed_mass[ant[0]][0] / 10)
            ants_state[ant[0]][1] += (speed_mass[ant[0]][1] / 10)


def helper():
    global i
    global movement
    global rooms
    global j
    global speed_mass
    if i == j:
        for ants in movements[i]:
            speed_x = (n[ants[1]][0] * 10 - ants_state[ants[0]][0] * 10)/100
            speed_y = (n[ants[1]][1] * 10 - ants_state[ants[0]][1] * 10)/100
            speed_mass[ants[0]] = [speed_x, speed_y]
        j += 1
    movement = movements[i]
    print_movement()


def main_1():
    global i
    helper()
    if abs(rooms[movement[0][1]][0] - ants_state[movement[0][0]][0]) <= 0.01 and abs(
            rooms[movement[0][1]][1] - ants_state[movement[0][0]][1]) <= 0.01:
        i += 1
    if i < len(movements):
        root.after(4, main_1)


q = []
a = "uuu"
movements = {}
i = 0
n = {}
j = 0
start = ''
for line in sys.stdin:
    line = line.strip('\n')
    if i == 0:
        count = int(line)
    elif re.search(line, '#'):
        continue
    elif line.__eq__("##start"):
        line = sys.stdin.readline()
        line = line.strip('\n')
        a = line.split(' ')
        start = a[0]
        n[a[0]] = [float(a[1]) * 1.5, float(a[2]) * 1.5]
    elif re.search("L", line):
        k = line.split(' ')
        movements[j] = []
        for t in k:
            movements[j].append([int(t[1:t.find('-')]), t[t.find('-') + 1:]])
        j += 1
    elif re.search(" ", line):
        a = line.split(' ')
        if a[1] == 'is':
            continue
        n[a[0]] = [float(a[1]) * 1.5, float(a[2]) * 1.5]
    elif re.search("-", line):
        m = line[0:line.find('-')]
        q = line[line.find('-') + 1:]
        n[m].append([n[q][0], n[q][1]])
    i += 1


root = Tk()
root.title("lem-in visualizer")
max_1 = 0
max_2 = 0
for t in n:
    if n[t][0] > max_1:
        max_1 = n[t][0]
    if n[t][1] > max_2:
        max_2 = n[t][1]
c1 = Canvas(root, height=10 * max_2 + 100, width=10 * max_1 + 100, bg='black')
for hh in n:
    for j in range(2, len(n[hh])):
        c1.create_line(50 + n[hh][0] * 10, 50 + n[hh][1] * 10,
                       50 + n[hh][j][0] * 10, 50 + n[hh][j][1] * 10, fill="green")
for hh in n:
    c1.create_oval(50 + n[hh][0] * 10 - 10, 50 + n[hh][1] * 10 - 10, 50 + n[hh][0] * 10 + 10,
                   50 + n[hh][1] * 10 + 10, fill='white', outline="red")

ants_state = {}

for i in range(1, count + 1):
    ants_state[i] = [n[start][0], n[start][1],
                     c1.create_oval(50 + n[start][0]*10 - 5, 50 + n[start][1]*10 - 5,
                                    50 + n[start][0] * 10 + 5, 50 + n[start][1]*10 + 5, fill="orange")]

c1.pack()
speed_mass = {}
i = 0
j = 0
rooms = n
main_1()
root.mainloop()
