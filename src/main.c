/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/06 14:15:37 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		main(int ac, char **av)
{
	int numbered;

	numbered = 0;
	if (ac >= 2)
	{
		if (ac == 2 && !(ft_strcmp(av[1], "-n")))
			numbered = 1;
		else
		{
			ft_putstr("usage: ./lem-in < map_file\nUse -n flag to see "
				"number of moves and number of ants, that took each path\n");
			return (0);
		}
	}
	parsing(numbered, 0, 0);
	return (0);
}
