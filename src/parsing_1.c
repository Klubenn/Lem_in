/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vladimir <vladimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/08 21:51:37 by vladimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	check_ants(t_lem0 *st0, char *line)
{
	if (!line || !*line)
		error_management(st0, "ERROR: no or empty line\n");
	if (*line == '#')
	{
		instructions1(st0, line, 0);
		return (0);
	}
	st0->ants = atoi_lem(line, st0);
	if (st0->ants < 0)
		error_management(st0, "ERROR: wrong number of ants\n");
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
	return (1);
}

static void	print_subject(t_lem0 *st0)
{
	while (st0->head_print)
	{
		st0->print = st0->head_print;
		ft_putstr(st0->head_print->content);
		ft_putchar('\n');
		st0->head_print = st0->head_print->next;
		free(st0->print->content);
		st0->print->content = NULL;
		free(st0->print);
		st0->print = NULL;
	}
	ft_putchar('\n');
}

static void	check_conditions(t_lem0 *st0)
{
	if (!st0->start || !st0->end)
		error_management(st0, "ERROR: no start or end room\n");
	if (!st0->ants)
		error_management(st0, "No ants present\n");
	if (st0->end->links == 0 || !(st0->start->links))
		error_management(st0, "ERROR: no access from start to end\n");
}

void		parsing(int numbered, int i, int j)
{
	int		gnl;
	char	*line;
	t_lem0	*st0;

	if (!(st0 = ft_memalloc(sizeof(t_lem0))))
		error_management(st0, "ERROR: memory wasn't allocated\n");
	while ((gnl = get_next_line(0, &line)))
	{
		if (gnl == -1)
			error_management(st0, "ERROR: can't read from file descriptor\n");
		if (i == 0)
			i = check_ants(st0, line);
		else if (j == 0)
			j = check_rooms1(st0, line);
		if (j)
			check_links(st0, line);
		free(line);
	}
	if (numbered)
		st0->numbered = 1;
	check_conditions(st0);
	print_subject(st0);
	breadth_first_search(st0);
}
