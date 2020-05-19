/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_deleter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 18:54:11 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/06 12:09:03 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void	rooms_deleter(t_lem0 *st0)
{
	t_links	*link;
	t_lem1	*room;
	int		i;

	i = 0;
	while (i < 10)
	{
		if (st0->lem1[i])
		{
			while (st0->lem1[i])
			{
				while (st0->lem1[i]->links)
				{
					link = st0->lem1[i]->links;
					st0->lem1[i]->links = st0->lem1[i]->links->prev;
					free(link);
				}
				room = st0->lem1[i];
				st0->lem1[i] = st0->lem1[i]->prev;
				free(room->room_name);
				free(room);
			}
		}
		i++;
	}
}

void	ways_deleter(t_solution *solution)
{
	t_sol_links *sol_link;
	t_links		*link;

	while (solution->sol_links)
	{
		while (solution->sol_links->links)
		{
			link = solution->sol_links->links;
			solution->sol_links->links = solution->sol_links->links->next;
			free(link);
		}
		sol_link = solution->sol_links;
		solution->sol_links = solution->sol_links->next;
		free(sol_link);
	}
}

void	memory_deleter_1(t_lem0 *st0)
{
	t_solution *solution;

	while (st0->solution)
	{
		ways_deleter(st0->solution);
		solution = st0->solution;
		st0->solution = st0->solution->next;
		free(solution);
	}
	rooms_deleter(st0);
	free(st0);
}
