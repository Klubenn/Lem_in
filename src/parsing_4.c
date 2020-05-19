/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <gtristan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/02 14:38:49 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_lem1		*new_lem1(char *name, t_lem1 *prev, t_lem1 *next)
{
	t_lem1 *lem1;

	lem1 = ft_memalloc(sizeof(t_lem1));
	if (!lem1)
		return (NULL);
	lem1->room_name = name;
	lem1->prev = prev;
	lem1->next = next;
	return (lem1);
}

static int	check_dupl_room(t_lem1 *room, char *name)
{
	while (room)
	{
		if (!(ft_strcmp(room->room_name, name)))
			return (1);
		room = room->prev;
	}
	return (0);
}

static void	check_rooms3(t_lem0 *st0, char **arr, int i)
{
	if (!(st0->lem1[i]))
		st0->lem1[i] = new_lem1(arr[0], NULL, NULL);
	else
	{
		if (!(check_dupl_room(st0->lem1[i], arr[0])))
		{
			st0->lem1[i]->next = new_lem1(arr[0], st0->lem1[i], NULL);
			st0->lem1[i] = st0->lem1[i]->next;
		}
		else
			error_management(st0, "ERROR: duplicate room name\n");
	}
	if (st0->tmp_info == START)
		st0->start = st0->lem1[i];
	else if (st0->tmp_info == END)
		st0->end = st0->lem1[i];
	st0->lem1[i]->room_type = st0->tmp_info;
	st0->tmp_info = 0;
	st0->lem1[i]->position[0] = atoi_lem(arr[1], st0);
	st0->lem1[i]->position[1] = atoi_lem(arr[2], st0);
}

static int	check_rooms2(t_lem0 *st0, char *line, int j)
{
	char	**arr;
	int		i;

	if (!(arr = split(line, ' ')))
		error_management(st0, "ERROR: wrong file contents or malloc fail\n");
	while (arr[j])
		j++;
	if (j != 3)
	{
		free_arr(arr, j);
		return (1);
	}
	if (!*arr[0] || check_coord(arr[1], arr[2]))
	{
		free_arr(arr, j);
		error_management(st0, "ERROR: wrong room name or coordinates\n");
	}
	i = hash_func(arr[0]);
	check_rooms3(st0, arr, i);
	arr[0] = NULL;
	free_arr(arr, j);
	st0->print->next = ft_lstnew(line, ft_strlen(line) + 1);
	st0->print = st0->print->next;
	return (0);
}

int			check_rooms1(t_lem0 *st0, char *line)
{
	int i;

	i = 0;
	if (!line || !*line || *line == 'L')
		error_management(st0, "ERROR\n");
	if (*line == '#' && *(line + 1) == '#')
		instructions1(st0, line, 1);
	else if (*line == '#')
	{
		st0->print->next = ft_lstnew(line, ft_strlen(line) + 1);
		st0->print = st0->print->next;
	}
	else
		i = check_rooms2(st0, line, 0);
	return (i);
}
