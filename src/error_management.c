/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <gtristan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:38:24 by gtristan          #+#    #+#             */
/*   Updated: 2019/10/21 09:18:44 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	error_management2(t_lem0 *st, int i)
{
	t_lem1	*room;
	t_links	*link;

	while (st->lem1[i])
	{
		room = st->lem1[i];
		while (st->lem1[i]->links)
		{
			link = st->lem1[i]->links;
			st->lem1[i]->links = st->lem1[i]->links->prev;
			free(link);
		}
		st->lem1[i] = st->lem1[i]->prev;
		free(room->room_name);
		free(room);
	}
}

void	error_management(t_lem0 *st, char *str)
{
	t_list	*list;
	int		i;

	if (str)
		ft_putstr_fd(str, 2);
	i = -1;
	while (++i < 10)
		error_management2(st, i);
	while (st->head_print)
	{
		list = st->head_print;
		st->head_print = st->head_print->next;
		free(list->content);
		free(list);
	}
	free(st);
	exit(1);
}
