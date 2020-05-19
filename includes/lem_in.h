/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 20:59:47 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/06 14:47:12 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define START 1
# define END 2
# include "../libft/libft.h"
# include "../libft/ft_printf/includes/header_pf.h"
# include <stdbool.h>
# include "lem_in_struct.h"

int			atoi_lem(char *str, t_lem0 *st0);
char		**split(char *line, char c);
void		error_management(t_lem0 *st, char *str);
int			get_next_line(int fd, char **line);
void		calc_length(t_lem0 *lem0);
void		parsing(int numbered, int i, int j);
void		instructions1(t_lem0 *st0, char *line, int launch);
void		check_links(t_lem0 *st0, char *line);
int			check_rooms1(t_lem0 *st0, char *line);
t_lem1		*new_lem1(char *name, t_lem1 *prev, t_lem1 *next);
t_links		*new_link(t_links *prev, t_links *next, t_lem1 *connect);
void		free_arr(char **arr, int i);
int			check_coord(char *a, char *b);
int			hash_func(char *str);
void		move_ants1(t_solution *solution, t_lem0 *lem0, int antnum, int mov);
void		breadth_first_search(t_lem0 *st0);
void		breadth_first_search_2(t_lem0 *st0);
void		bfs_expand(t_lem0 *st0);
t_links		*is_vertex_has_negative_links(t_lem1 *current_vertex,
				t_queue *buff_queue);
t_sol_links *bfs_collision_modifier(t_lem0 *st0);
void		bfs_expand(t_lem0 *st0);
void		b_f_s(t_lem1 *current_vertex,
				t_lem0 *st0, t_queue *buff_queue, int *j);
bool		b_f_s_2(t_lem0 *st0, t_queue *buff_queue, int *j);
bool		bfs_mdf(t_lem1 *current_vertex, t_lem0 *st0,
				t_queue *buff_queue, bool criterion);
void		breadth_first_search_2(t_lem0 *st0);
t_sol_links *bfs_collision_modifier(t_lem0 *st0);
t_sol_links *bfs_collision_modifier_2(t_lem1 *current_vertex, t_queue *queue,
				t_lem0 *st0, t_queue *buff_queue);
void		way_keeper_reverse(t_sol_links **way_keeper);
void		ways_creator_2(t_lem1 *current_vertex, t_lem0 *st0,
				t_sol_links **way_keeper);
int			one_way_creator(t_links *begin_way, t_parents *parent,
				t_links **way2, t_lem0 *st0);
t_sol_links *bfs_collision_modifier(t_lem0 *st0);
void		weight_zeroing_helper(t_lem1 *buff);
void		weight_zeroing(t_lem0 *st0);
void		delete_flags(t_lem0 *st0);
void		ways_weight_modifier(t_lem0 *st0);
void		ways_array_creator(t_sol_links **way_keeper,
				int length, t_links *way2);
void		bfs_expand_helper_queue_maker(t_queue **queue,
				t_lem1 **current_vertex, t_lem0 *st0);
void		bfs_expand_helper(t_queue **queue,
				t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0);
bool		breadth_first_search_cycle_finder_1(t_queue **queue,
				t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0);
void		link_deleter_helper(t_links *link, t_lem1 *buff);
void		link_deleter(t_links *link_1, t_links *link_2,
				t_lem1 *buff_1, t_lem1 *buff_2);
bool		breadth_first_search_cycle_finder_2(t_queue **queue,
				t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0);
bool		negative_link_checker(t_lem1 *current_vertex, t_links *link);
t_links		*is_vertex_has_negative_links(t_lem1 *current_vertex,
				t_queue *buff_queue);
bool		destroyed_link_checker(t_lem1 *current_vertex);
void		parents_deleter_current_vertex(t_lem1 *current_vertex);
void		bfs_cycle_finder_helper(t_lem1 **current_vertex,
				t_queue **queue, t_lem0 *st0);
bool		destroyed_links_finder(t_links *direct_link,
				t_lem1 *current_vertex);
bool		ways_destroyer(t_lem1 *current_vertex);
bool		parents_contain_way(t_queue *buff_queue);
bool		negative_weigth_finder(t_parents *begin_way, t_parents *way2);
void		current_vertex_and_queue_initializer(t_lem1 **current_vertex,
				t_queue **queue, t_queue **buff_queue, t_lem0 *st0);
void		parents_deleter(t_lem0 *st0);
void		queue_deleter(t_queue *queue);
int			length_counter(t_links **way2, t_links *begin_way,
				t_parents *parent, t_lem0 *st0);
int			ways_creator_helper(t_lem1 *current_vertex,
				t_links **way2, t_lem0 *st0);
void		ways_weight_modifier_1(t_sol_links *way_keeper, t_lem0 *st0);
void		breadth_first_search_cycle_finder(t_queue **queue,
				t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0);
void		ways_creator(t_lem1 *current_vertex, t_lem0 *st0,
				int *i, t_sol_links **way_keeper);
void		queue_creator(t_lem1 **current_vertex,
				t_queue **queue, t_links **buff_links, bool state);
void		memory_deleter_1(t_lem0 *st0);
void		ways_deleter(t_solution *solution);
void		rooms_deleter(t_lem0 *st0);

#endif
