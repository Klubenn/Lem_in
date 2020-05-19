/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_expand_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 20:56:54 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/05 22:47:32 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void	bfs_expand_helper_queue_maker(t_queue **queue,
t_lem1 **current_vertex, t_lem0 *st0)
{
	t_links *buff_links;

	buff_links = (*current_vertex)->links;
	if (destroyed_link_checker(*current_vertex) == false)
	{
		buff_links = (*current_vertex)->links;
		while (buff_links != 0)
		{
			if (buff_links->weight != -1)
			{
				if (buff_links->connection_room->parents == 0 &&
					buff_links->connection_room != st0->start)
				{
					queue_creator(current_vertex, queue, &buff_links,
						negative_link_checker(*current_vertex, buff_links));
				}
			}
			buff_links = buff_links->prev;
		}
	}
}

void	bfs_expand_helper(t_queue **queue,
t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0)
{
	t_links *buff_links;

	if ((*buff_queue)->state == false && (buff_links =
			is_vertex_has_negative_links(*current_vertex, *buff_queue)))
	{
		if (buff_links->connection_room != st0->start
			&& buff_links->connection_room->parents == 0)
			queue_creator(current_vertex, queue, &buff_links, true);
		else if (buff_links->connection_room == st0->start)
			parents_deleter_current_vertex(*current_vertex);
	}
	else
		bfs_expand_helper_queue_maker(queue, current_vertex, st0);
}

bool	breadth_first_search_cycle_finder_1(t_queue **queue,
t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0)
{
	t_queue *deleter_queue;

	while ((*current_vertex != st0->end &&
		*buff_queue != 0 && *current_vertex != NULL))
	{
		deleter_queue = *buff_queue;
		bfs_expand_helper(queue, buff_queue, current_vertex, st0);
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

void	link_deleter_helper(t_links *link, t_lem1 *buff)
{
	if (buff->links == link)
	{
		buff->links = link->prev;
		if (buff->links != 0)
			buff->links->next = 0;
		free(link);
	}
	else if (link->prev != 0)
	{
		link->next->prev = link->prev;
		link->prev->next = link->next;
		free(link);
	}
	else
	{
		link->next->prev = 0;
		free(link);
	}
}

void	link_deleter(t_links *link_1, t_links *link_2,
t_lem1 *buff_1, t_lem1 *buff_2)
{
	link_deleter_helper(link_1, buff_1);
	link_deleter_helper(link_2, buff_2);
}
