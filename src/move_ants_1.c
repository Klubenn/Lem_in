/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/06 12:52:30 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void			calc_ants_pass(t_solution *solution, t_sol_links *sol_link,
					int ant, int ants)
{
	t_sol_links *tmp;

	tmp = solution->sol_links;
	while (tmp && tmp != sol_link->next && ant < ants)
	{
		tmp->ants_to_pass += 1;
		tmp->ants_to_pass_num += 1;
		ant++;
		tmp = tmp->next;
	}
}

static int			calc_moves2(t_lem0 *lem0, int ant, int counter,
					t_solution *sol)
{
	int			moves;
	t_sol_links	*sol_link;

	moves = 0;
	sol_link = sol->sol_links;
	while (ant < lem0->ants && sol_link)
	{
		if (sol_link->next && sol_link->length + sol_link->ants_to_pass
				< sol_link->next->length)
		{
			calc_ants_pass(sol, sol_link, ant, lem0->ants);
			ant += counter;
			moves++;
		}
		else if (sol_link->next && ++counter)
			sol_link = sol_link->next;
		else
		{
			calc_ants_pass(sol, sol_link, ant, lem0->ants);
			ant += counter;
			moves++;
		}
	}
	return (moves);
}

static void			calc_moves1(t_lem0 *lem0)
{
	int			ant;
	int			counter;
	int			moves;
	t_solution	*sol;

	sol = lem0->solution;
	while (sol)
	{
		ant = 0;
		counter = 1;
		moves = calc_moves2(lem0, ant, counter, sol);
		sol->moves = moves + sol->sol_links->length - 1;
		sol = sol->next;
	}
}

static t_solution	*best_solution(t_lem0 *lem0)
{
	t_solution	*sol;
	t_solution	*tmp;
	int			moves;

	tmp = lem0->solution;
	moves = tmp->moves;
	sol = tmp;
	while (tmp)
	{
		if (moves > tmp->moves)
		{
			moves = tmp->moves;
			sol = tmp;
		}
		tmp = tmp->next;
	}
	return (sol);
}

void				calc_length(t_lem0 *lem0)
{
	t_solution	*sol;
	t_links		*link;
	t_sol_links	*sol_link;

	sol = lem0->solution;
	if (!sol)
		ft_printf("NO SOLUTION");
	while (sol)
	{
		sol_link = sol->sol_links;
		while (sol_link)
		{
			link = sol_link->links;
			while (link->next)
				link = link->next;
			sol_link->links_end = link;
			sol_link = sol_link->next;
		}
		sol = sol->next;
	}
	calc_moves1(lem0);
	move_ants1(best_solution(lem0), lem0, 0, 0);
}
