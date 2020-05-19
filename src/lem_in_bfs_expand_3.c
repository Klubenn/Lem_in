/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_expand_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 20:55:25 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/01 22:55:21 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool	breadth_first_search_cycle_finder_2(t_queue **queue,
t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0)
{
	t_queue *deleter_queue;

	while ((*current_vertex != st0->end &&
		*buff_queue != 0 && *current_vertex != NULL))
	{
		deleter_queue = *buff_queue;
		bfs_cycle_finder_helper(current_vertex, queue, st0);
		if (*buff_queue)
			*buff_queue = (*buff_queue)->next;
		if (*buff_queue)
			(*current_vertex) = (*buff_queue)->vertex;
		free(deleter_queue);
	}
	if (*current_vertex == st0->end)
		return (true);
	return (false);
}

bool	negative_link_checker(t_lem1 *current_vertex, t_links *link)
{
	t_links *buff_link;

	buff_link = link->connection_room->links;
	while (buff_link && buff_link->connection_room != current_vertex)
		buff_link = buff_link->prev;
	if (buff_link != 0 && buff_link->weight == -1)
		return (true);
	return (false);
}

t_links	*is_vertex_has_negative_links(t_lem1 *current_vertex,
		t_queue *buff_queue)
{
	t_links *buff_link;
	t_links *buff_link2;

	buff_link = current_vertex->links;
	while (buff_link != 0)
	{
		buff_link2 = buff_link->connection_room->links;
		while (buff_link2 != 0 &&
				buff_link2->connection_room != current_vertex)
			buff_link2 = buff_link2->prev;
		if (buff_link2 != 0 && buff_link2->weight == -1
				&& buff_link2->connection_room == current_vertex
				&& buff_queue->state == false)
		{
			if (buff_link->weight != -1)
				return (buff_link);
		}
		buff_link = buff_link->prev;
	}
	return (0);
}

bool	destroyed_link_checker(t_lem1 *current_vertex)
{
	t_links *buff_links;
	t_links *buff_links_2;

	buff_links = current_vertex->links;
	while (buff_links)
	{
		if (buff_links->weight == -1)
		{
			buff_links_2 = buff_links->connection_room->links;
			while (buff_links_2 &&
				buff_links_2->connection_room != current_vertex)
				buff_links_2 = buff_links_2->prev;
			if (buff_links_2 && buff_links_2->weight == -1)
				return (true);
		}
		buff_links = buff_links->prev;
	}
	return (false);
}

void	parents_deleter_current_vertex(t_lem1 *current_vertex)
{
	free(current_vertex->current);
	current_vertex->current = 0;
	current_vertex->parents = 0;
}
