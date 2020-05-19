/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <gtristan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/02 14:38:49 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	print_numbered(t_solution *solution, t_lem0 *lem0)
{
	t_sol_links *link;

	link = solution->sol_links;
	if (lem0->numbered)
	{
		ft_printf("{cyan}\nHere is the number of ants that took various "
			"paths:\n{eoc}");
		while (link && link->ants_to_pass_num)
		{
			ft_printf("Path length - %3d:{red}%5d{eoc} ants\n",
					link->length, link->ants_to_pass_num);
			link = link->next;
		}
	}
}

static void	print_moves2(int num, int mov)
{
	if (num)
	{
		ft_putnbr(mov);
		write(1, ":\t", 2);
	}
}

static void	print_moves(t_solution *solution, int first_print, int num, int mov)
{
	t_sol_links *path;
	t_links		*room;

	print_moves2(num, mov);
	path = solution->sol_links;
	while (path)
	{
		room = path->links_end;
		while (room->prev)
		{
			if (room->ant_number && first_print-- > 0)
				write(1, "L", 1);
			else if (room->ant_number && first_print <= 0)
				write(1, " L", 2);
			if (room->ant_number)
			{
				ft_putnbr(room->ant_number);
				write(1, "-", 1);
				ft_putstr(room->connection_room->room_name);
			}
			room = room->prev;
		}
		path = path->next;
	}
	ft_putchar('\n');
}

static void	move_ants2(t_sol_links *sol_link, int antnum)
{
	t_links		*link;

	link = sol_link->links_end;
	while (link->prev->prev)
	{
		link->ant_number = link->prev->ant_number;
		link = link->prev;
	}
	link->ant_number = antnum;
}

void		move_ants1(t_solution *solution, t_lem0 *lem0, int antnum, int mov)
{
	t_sol_links *sol_link;

	while (solution->moves > 0)
	{
		sol_link = solution->sol_links;
		while (sol_link && antnum < lem0->ants)
		{
			if ((sol_link->ants_to_pass)-- > 0 && ++antnum)
				move_ants2(sol_link, antnum);
			else
				move_ants2(sol_link, 0);
			sol_link = sol_link->next;
		}
		if (sol_link && antnum >= lem0->ants)
		{
			while (sol_link)
			{
				move_ants2(sol_link, 0);
				sol_link = sol_link->next;
			}
		}
		print_moves(solution, 1, lem0->numbered, ++mov);
		solution->moves -= 1;
	}
	print_numbered(solution, lem0);
}
