/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_bfs_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:09:00 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/05 19:15:31 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void		way_keeper_modifier(bool criterion, t_sol_links *way_keeper,
	t_lem0 *st0, int *arr)
{
	if (criterion)
		ways_weight_modifier_1(way_keeper, st0);
	if (arr[1] == 0 && criterion == false)
	{
		free(way_keeper);
		error_management(st0, "ERROR: no way\n");
	}
	arr[1]++;
}

t_sol_links	*breadth_first_search_helper(t_lem0 *st0, t_sol_links *way_keeper)
{
	t_lem1		*cur_vert;
	t_queue		*queue;
	t_queue		*buff_queue;
	int			arr[2];
	bool		criterion;

	criterion = true;
	arr[0] = 0;
	arr[1] = 0;
	while (criterion)
	{
		current_vertex_and_queue_initializer(&cur_vert, &queue, &buff_queue,
				st0);
		breadth_first_search_cycle_finder(&queue, &buff_queue, &cur_vert, st0);
		if (cur_vert == st0->end)
			ways_creator(cur_vert, st0, &(arr[0]), &way_keeper);
		if (cur_vert != st0->end)
			criterion = false;
		arr[0] = 1;
		parents_deleter(st0);
		queue_deleter(buff_queue);
		way_keeper_modifier(criterion, way_keeper, st0, arr);
	}
	return (way_keeper);
}

void		breadth_first_search(t_lem0 *st0)
{
	t_sol_links	*buff_keeper;

	buff_keeper = (t_sol_links *)ft_memalloc(sizeof(t_sol_links));
	buff_keeper->next = 0;
	breadth_first_search_helper(st0, buff_keeper);
	st0->solution = (t_solution *)ft_memalloc(sizeof(t_solution));
	st0->solution->next = 0;
	st0->solution->prev = 0;
	st0->solution->sol_links = buff_keeper;
	bfs_expand(st0);
	calc_length(st0);
	memory_deleter_1(st0);
}
