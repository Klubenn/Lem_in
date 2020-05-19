/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <gtristan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/02 14:38:49 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		free_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}

int			check_coord(char *a, char *b)
{
	if (!*a || !*b)
		return (-1);
	if (*a == '+' || *a == '-')
		a++;
	if (*b == '+' || *b == '-')
		b++;
	while (*a)
	{
		if (*a < '0' || *a > '9')
			return (-1);
		a++;
	}
	while (*b)
	{
		if (*b < '0' || *b > '9')
			return (-1);
		b++;
	}
	return (0);
}

int			hash_func(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i += *str;
		i %= 10;
		str++;
	}
	return (i);
}

static void	instructions2(t_lem0 *st0, char *line)
{
	if (!st0->print)
	{
		st0->print = ft_lstnew(line, ft_strlen(line) + 1);
		st0->head_print = st0->print;
	}
	else
	{
		st0->print->next = ft_lstnew(line, ft_strlen(line) + 1);
		st0->print = st0->print->next;
	}
}

void		instructions1(t_lem0 *st0, char *line, int launch)
{
	int start;

	if (!(start = ft_strcmp(line, "##start")) || !(ft_strcmp(line, "##end")))
	{
		if (st0->tmp_info)
			error_management(st0, "ERROR: multiple instructions"
									" for one room\n");
		else if (!launch)
			error_management(st0, "ERROR: room specification before"
									" defining number of ants\n");
		if (!start)
			st0->tmp_info = START;
		else
			st0->tmp_info = END;
		if ((st0->start && st0->tmp_info == START) ||
			(st0->end && st0->tmp_info == END))
			error_management(st0, "ERROR: multiple start or end rooms\n");
	}
	instructions2(st0, line);
}
