/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <gtristan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:37:40 by gtristan          #+#    #+#             */
/*   Updated: 2020/04/02 14:38:49 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			atoi_lem(char *str, t_lem0 *st0)
{
	long long	res;
	int			sign;
	int			len;
	int			err;

	sign = 1;
	res = 0;
	len = 0;
	err = 0;
	if (str[len] == '-' && ++err)
	{
		sign = -1;
		len++;
	}
	else if (str[len] == '+' && ++err)
		len++;
	while (str[len] >= '0' && str[len] <= '9' && len <= 11)
	{
		res = res * 10 + (str[len] - '0');
		len++;
	}
	if ((res > 2147483647 && sign == 1) || (res > 2147483648 && sign == -1)
		|| len > 11 || str[len] || (len == 1 && err == 1))
		error_management(st0, "ERROR: wrong number for ants or coordinates\n");
	return ((int)res * sign);
}
