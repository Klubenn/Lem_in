/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_expand_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 20:59:47 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/01 21:54:46 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int			one_way_creator(t_links *begin_way, t_parents *parent,
t_links **way2, t_lem0 *st0)
{
	int length;

	length = 0;
	while (parent)
	{
		*way2 = (t_links *)ft_memalloc(sizeof(t_links));
		(*way2)->connection_room = parent->vertex;
		if (parent->vertex != st0->end
			&& parent->vertex != st0->start)
			(*way2)->connection_room->flag = 1;
		(*way2)->next = begin_way;
		begin_way->prev = *way2;
		begin_way = *way2;
		(*way2)->prev = 0;
		parent = parent->prev;
		length += 1;
	}
	return (length);
}

void		ways_creator_2(t_lem1 *current_vertex, t_lem0 *st0,
			t_sol_links **way_keeper)
{
	t_parents	*parent;
	t_links		*begin_way;
	t_links		*way2;
	int			length;

	length = 0;
	parent = current_vertex->current;
	begin_way = (t_links *)ft_memalloc(sizeof(t_links));
	begin_way->connection_room = parent->vertex;
	begin_way->next = 0;
	begin_way->prev = 0;
	parent = parent->prev;
	length = one_way_creator(begin_way, parent, &way2, st0);
	ways_array_creator(way_keeper, length, way2);
}

void		way_keeper_reverse(t_sol_links **way_keeper)
{
	t_sol_links	*buff_way;
	t_sol_links	*buff_way_2;
	int			i;

	buff_way = *way_keeper;
	while (buff_way->next)
		buff_way = buff_way->next;
	*way_keeper = buff_way;
	i = 0;
	while (buff_way)
	{
		buff_way->next = buff_way->prev;
		if (i == 0)
			buff_way->prev = 0;
		else
			buff_way->prev = buff_way_2;
		buff_way_2 = buff_way;
		buff_way = buff_way->next;
		i++;
	}
}

t_sol_links	*bfs_collision_modifier_2(t_lem1 *current_vertex, t_queue *queue,
t_lem0 *st0, t_queue *buff_queue)
{
	t_sol_links	*way_keeper;
	bool		criterion;

	way_keeper = 0;
	criterion = true;
	while (criterion)
	{
		current_vertex_and_queue_initializer(&current_vertex,
			&queue, &buff_queue, st0);
		if (!breadth_first_search_cycle_finder_2(&queue, &buff_queue,
			&current_vertex, st0))
		{
			parents_deleter(st0);
			queue_deleter(buff_queue);
			break ;
		}
		if (current_vertex == st0->end)
			ways_creator_2(current_vertex, st0, &way_keeper);
		criterion = bfs_mdf(current_vertex, st0, buff_queue, criterion);
	}
	return (way_keeper);
}

t_sol_links	*bfs_collision_modifier(t_lem0 *st0)
{
	t_lem1		*cur_vert;
	t_queue		*queue;
	t_queue		*buff_queue;
	int			j;
	bool		criterion;

	j = 0;
	criterion = true;
	while (true)
	{
		current_vertex_and_queue_initializer(&cur_vert,
			&queue, &buff_queue, st0);
		if (!breadth_first_search_cycle_finder_1(&queue, &buff_queue,
			&cur_vert, st0))
		{
			criterion = b_f_s_2(st0, buff_queue, &j);
			break ;
		}
		b_f_s(cur_vert, st0, buff_queue, &j);
	}
	if (criterion)
		return (bfs_collision_modifier_2(cur_vert, queue, st0, buff_queue));
	return (0);
}
