/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 15:18:27 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/02 00:10:24 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void	breadth_first_search_2(t_lem0 *st0)
{
	t_sol_links	*way_keeper;

	delete_flags(st0);
	weight_zeroing(st0);
	ways_weight_modifier(st0);
	way_keeper = bfs_collision_modifier(st0);
	if (way_keeper)
	{
		way_keeper_reverse(&way_keeper);
		st0->solution->prev = (t_solution *)ft_memalloc(sizeof(t_solution));
		st0->solution->prev->prev = 0;
		st0->solution->prev->next = st0->solution;
		st0->solution->prev->sol_links = way_keeper;
		st0->solution = st0->solution->prev;
	}
}

bool	bfs_mdf(t_lem1 *current_vertex, t_lem0 *st0,
t_queue *buff_queue, bool criterion)
{
	if (current_vertex != st0->end)
		criterion = false;
	parents_deleter(st0);
	queue_deleter(buff_queue);
	return (criterion);
}

bool	b_f_s_2(t_lem0 *st0, t_queue *buff_queue, int *j)
{
	bool criterion;

	criterion = true;
	parents_deleter(st0);
	queue_deleter(buff_queue);
	if (*j == 0)
		criterion = false;
	return (criterion);
}

void	b_f_s(t_lem1 *current_vertex,
	t_lem0 *st0, t_queue *buff_queue, int *j)
{
	ways_destroyer(current_vertex);
	parents_deleter(st0);
	queue_deleter(buff_queue);
	*j += 1;
}

void	bfs_expand(t_lem0 *st0)
{
	t_solution *buff_solution;

	buff_solution = st0->solution;
	while (buff_solution)
	{
		breadth_first_search_2(st0);
		buff_solution = buff_solution->prev;
	}
}
