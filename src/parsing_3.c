/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/05 19:26:54 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_links		*new_link(t_links *prev, t_links *next, t_lem1 *connect)
{
	t_links *link;

	link = (t_links *)ft_memalloc(sizeof(t_links));
	if (!link)
		return (NULL);
	link->prev = prev;
	link->next = next;
	link->connection_room = connect;
	link->weight = 0;
	return (link);
}

static int	check_dupl_link(t_links *link, t_lem1 *room)
{
	while (link)
	{
		if (link->connection_room == room)
			return (1);
		link = link->prev;
	}
	return (0);
}

static void	check_links3(t_lem0 *st0, t_lem1 *tmp1, t_lem1 *tmp2)
{
	int		j;

	j = 0;
	if (!tmp1->links)
		tmp1->links = new_link(NULL, NULL, tmp2);
	else if (!(j = check_dupl_link(tmp1->links, tmp2)))
	{
		tmp1->links->next = new_link(tmp1->links, NULL, tmp2);
		tmp1->links = tmp1->links->next;
	}
	if (!tmp2->links)
		tmp2->links = new_link(NULL, NULL, tmp1);
	else if (!j)
	{
		tmp2->links->next = new_link(tmp2->links, NULL, tmp1);
		tmp2->links = tmp2->links->next;
	}
	if (!tmp1->links || !tmp2->links)
		error_management(st0, "ERROR: memory wasn't allocated\n");
}

static void	check_links2(t_lem0 *st0, char **arr, int i)
{
	int		k;
	t_lem1	*tmp1;
	t_lem1	*tmp2;

	k = hash_func(arr[0]);
	tmp1 = st0->lem1[k];
	while (tmp1 && ft_strcmp(tmp1->room_name, arr[0]))
		tmp1 = tmp1->prev;
	k = hash_func(arr[1]);
	tmp2 = st0->lem1[k];
	while (tmp2 && ft_strcmp(tmp2->room_name, arr[1]))
		tmp2 = tmp2->prev;
	if (!tmp1 || !tmp2)
	{
		free_arr(arr, i);
		error_management(st0, "ERROR: wrong link\n");
	}
	if (tmp1 != tmp2)
		check_links3(st0, tmp1, tmp2);
	free_arr(arr, i);
}

void		check_links(t_lem0 *st0, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	if (line == 0 || (*line) == '\0' || *line == 'L')
		error_management(st0, "ERROR\n");
	if (*line != '#')
	{
		arr = split(line, '-');
		while (arr[i])
			i++;
		if (i != 2)
		{
			free_arr(arr, i);
			error_management(st0, "ERROR: wrong link\n");
		}
		check_links2(st0, arr, i);
	}
	st0->print->next = ft_lstnew(line, ft_strlen(line) + 1);
	st0->print = st0->print->next;
}
