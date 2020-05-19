/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_expand_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 20:54:11 by gtapioca          #+#    #+#             */
/*   Updated: 2020/03/31 00:05:56 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool	negative_weigth_finder(t_parents *begin_way, t_parents *way2)
{
	t_links *buff_links;
	t_links *buff_links_2;

	buff_links = begin_way->vertex->links;
	while (buff_links->connection_room != way2->vertex)
		buff_links = buff_links->prev;
	if (buff_links->weight == -1)
	{
		buff_links_2 = way2->vertex->links;
		while (buff_links_2->connection_room != begin_way->vertex)
			buff_links_2 = buff_links_2->prev;
		buff_links_2->weight = -1;
		return (true);
	}
	return (false);
}

bool	parents_contain_way(t_queue *buff_queue)
{
	t_parents *parent;

	parent = 0;
	while (buff_queue)
	{
		parent = buff_queue->vertex->parents;
		while (parent)
		{
			if (parent->vertex->flag == 1)
				return (true);
			parent = parent->prev;
		}
		buff_queue = buff_queue->next;
	}
	return (false);
}

bool	ways_destroyer(t_lem1 *current_vertex)
{
	t_parents *parent;

	parent = current_vertex->current;
	while (parent->prev)
	{
		negative_weigth_finder(parent, parent->prev);
		parent = parent->prev;
	}
	return (false);
}

bool	destroyed_links_finder(t_links *direct_link, t_lem1 *current_vertex)
{
	t_links *buff_link;

	if (direct_link->weight == -1)
	{
		buff_link = direct_link->connection_room->links;
		while (buff_link)
		{
			if (buff_link->connection_room == current_vertex)
			{
				if (buff_link->weight == -1)
					return (true);
			}
			buff_link = buff_link->prev;
		}
	}
	return (false);
}

void	bfs_cycle_finder_helper(t_lem1 **current_vertex,
t_queue **queue, t_lem0 *st0)
{
	t_links *buff_links;

	buff_links = (*current_vertex)->links;
	while (buff_links != 0)
	{
		if (!(destroyed_links_finder(buff_links, *current_vertex))
			&& buff_links->connection_room->flag != 1)
		{
			if (buff_links->connection_room->parents == 0 &&
				buff_links->connection_room != st0->start)
				queue_creator(current_vertex, queue, &buff_links, false);
		}
		buff_links = buff_links->prev;
	}
}
