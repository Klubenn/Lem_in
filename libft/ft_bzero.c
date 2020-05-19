/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:16:57 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/24 15:07:36 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*u;
	size_t			i;

	u = s;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			u[i] = 0;
			i++;
		}
		s = u;
	}
}
