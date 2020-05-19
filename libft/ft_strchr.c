/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:27:06 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/10 12:01:24 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char c1;
	char *c2;

	c1 = (char)c;
	c2 = (char*)s;
	while (*c2 != c1 && *c2)
		c2++;
	if (*c2 == c1)
		return (c2);
	else
		return (NULL);
}
