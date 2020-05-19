/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 15:17:21 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/01 21:25:59 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void	ways_creator(t_lem1 *current_vertex, t_lem0 *st0,
		int *i, t_sol_links **way_keeper)
{
	t_links	*way2;
	int		length;

	length = ways_creator_helper(current_vertex, &way2, st0);
	if (*i == 0)
	{
		(*way_keeper)->links = way2;
		(*way_keeper)->next = 0;
		(*way_keeper)->prev = 0;
		(*way_keeper)->length = length;
	}
	else
	{
		(*way_keeper)->next = (t_sol_links *)ft_memalloc(sizeof(t_sol_links));
		(*way_keeper)->next->links = way2;
		(*way_keeper)->next->prev = (*way_keeper);
		(*way_keeper) = (*way_keeper)->next;
		(*way_keeper)->length = length;
		(*way_keeper)->next = 0;
	}
}

void	queue_creator(t_lem1 **current_vertex, t_queue **queue,
		t_links **buff_links, bool state)
{
	(*queue)->next = (t_queue *)ft_memalloc(sizeof(t_queue));
	(*queue)->next->vertex = (*buff_links)->connection_room;
	(*queue)->next->state = state;
	(*queue)->next->vertex->current =
			(t_parents *)ft_memalloc(sizeof(t_parents));
	(*queue)->next->vertex->current->prev = (*current_vertex)->current;
	(*queue)->next->vertex->current->vertex = (*queue)->next->vertex;
	(*queue)->next->vertex->parents = (*current_vertex)->current;
	(*queue) = (*queue)->next;
	(*queue)->next = NULL;
}

void	bf_mover(t_queue **queue, t_lem1 **current_vertex, t_lem0 *st0)
{
	t_links *buff_links;

	buff_links = (*current_vertex)->links;
	while (buff_links != 0)
	{
		if (buff_links->connection_room->flag == 0 && buff_links->weight != -1)
			if (buff_links->connection_room->parents == 0 &&
				buff_links->connection_room != st0->start)
				queue_creator(current_vertex, queue,
				&buff_links, false);
		buff_links = buff_links->prev;
	}
}

void	breadth_first_search_cycle_finder(t_queue **queue,
t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0)
{
	t_queue *deleter_queue;

	while (*current_vertex != st0->end &&
		*buff_queue != 0 && *current_vertex != NULL)
	{
		deleter_queue = *buff_queue;
		bf_mover(queue, current_vertex, st0);
		if (*buff_queue)
			*buff_queue = (*buff_queue)->next;
		if (*buff_queue)
			(*current_vertex) = (*buff_queue)->vertex;
		free(deleter_queue);
	}
}

void	ways_weight_modifier_1(t_sol_links *way_keeper, t_lem0 *st0)
{
	t_links		*buff_link;
	t_links		*buff_link_2;
	t_sol_links	*buff_sol;

	buff_sol = way_keeper;
	while (buff_sol)
	{
		buff_link = buff_sol->links;
		while (buff_link && buff_link->connection_room != st0->end)
		{
			buff_link_2 = buff_link->connection_room->links;
			while (buff_link_2)
			{
				if (buff_link_2->connection_room ==
				buff_link->next->connection_room)
					buff_link_2->weight = -1;
				buff_link_2 = buff_link_2->prev;
			}
			buff_link = buff_link->next;
		}
		buff_sol = buff_sol->next;
	}
}
