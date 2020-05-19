/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/01 22:28:16 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../includes/lem_in.h"

void	current_vertex_and_queue_initializer(t_lem1 **current_vertex,
t_queue **queue, t_queue **buff_queue, t_lem0 *st0)
{
	(*current_vertex) = st0->start;
	(*queue) = (t_queue *)ft_memalloc(sizeof(t_queue));
	(*queue)->vertex = (*current_vertex);
	(*buff_queue) = (*queue);
	(*queue)->next = NULL;
	(*current_vertex)->current =
	(t_parents *)ft_memalloc(sizeof(t_parents));
	(*current_vertex)->current->prev = NULL;
	(*current_vertex)->current->vertex = (*current_vertex);
	(*current_vertex)->parents = NULL;
}

void	parents_deleter(t_lem0 *st0)
{
	t_lem1	*buff_lem;
	int		i;

	i = 0;
	while (i < 10)
	{
		buff_lem = st0->lem1[i];
		while (buff_lem)
		{
			free(buff_lem->current);
			buff_lem->current = NULL;
			buff_lem->parents = NULL;
			buff_lem = buff_lem->prev;
		}
		i++;
	}
}

void	queue_deleter(t_queue *queue)
{
	t_queue *buff_queue;

	while (queue)
	{
		buff_queue = queue;
		queue = queue->next;
		free(buff_queue);
	}
}

int		length_counter(t_links **way2, t_links *begin_way,
t_parents *parent, t_lem0 *st0)
{
	int	length;

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

int		ways_creator_helper(t_lem1 *current_vertex,
t_links **way2, t_lem0 *st0)
{
	t_parents	*parent;
	t_links		*begin_way;

	parent = current_vertex->current;
	begin_way = (t_links *)ft_memalloc(sizeof(t_links));
	begin_way->connection_room = parent->vertex;
	begin_way->next = 0;
	begin_way->prev = 0;
	parent = parent->prev;
	return (length_counter(way2, begin_way, parent, st0));
}
