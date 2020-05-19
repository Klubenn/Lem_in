/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_expand_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 15:18:27 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/06 12:25:22 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void	weight_zeroing_helper(t_lem1 *buff)
{
	t_links *buff_link;
	t_links *buff_link_2;
	t_links *buff_link_1;

	while (buff)
	{
		buff_link = buff->links;
		while (buff_link)
		{
			buff_link_2 = buff_link->connection_room->links;
			buff_link_1 = buff_link;
			buff_link = buff_link->prev;
			while (buff_link_2 &&
				buff_link_2->connection_room != buff)
				buff_link_2 = buff_link_2->prev;
			if (buff_link_2 && buff_link_2->weight == -1
				&& buff_link_1->weight == -1)
				link_deleter(buff_link_1, buff_link_2, buff,
					buff_link_1->connection_room);
			else if (buff_link_1->weight == -1)
				buff_link_1->weight = 0;
		}
		buff = buff->prev;
	}
}

void	weight_zeroing(t_lem0 *st0)
{
	int		i;
	t_lem1	*buff;

	i = 0;
	while (i < 10)
	{
		buff = (st0->lem1[i]);
		weight_zeroing_helper(buff);
		i++;
	}
}

void	delete_flags(t_lem0 *st0)
{
	int		i;
	int		j;
	t_lem1	*buff;

	i = 0;
	j = 0;
	while (i < 10)
	{
		buff = st0->lem1[i];
		while (buff)
		{
			if (buff->flag == 1)
				buff->flag = 0;
			buff = buff->prev;
			j++;
		}
		i++;
	}
}

void	ways_weight_modifier(t_lem0 *st0)
{
	t_links		*buff_link;
	t_links		*buff_link_2;
	t_sol_links	*buff_sol;

	buff_sol = st0->solution->sol_links;
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

void	ways_array_creator(t_sol_links **way_keeper, int length, t_links *way2)
{
	if (*way_keeper == 0)
	{
		(*way_keeper) = (t_sol_links *)ft_memalloc(sizeof(t_sol_links));
		(*way_keeper)->links = way2;
		(*way_keeper)->next = 0;
		(*way_keeper)->prev = 0;
		(*way_keeper)->length = length;
	}
	else
	{
		(*way_keeper)->prev = (t_sol_links *)ft_memalloc(sizeof(t_sol_links));
		(*way_keeper)->prev->links = way2;
		(*way_keeper)->prev->next = (*way_keeper);
		(*way_keeper) = (*way_keeper)->prev;
		(*way_keeper)->length = length;
		(*way_keeper)->prev = 0;
	}
}
