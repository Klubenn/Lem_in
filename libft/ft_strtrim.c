/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtristan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:02:42 by gtristan          #+#    #+#             */
/*   Updated: 2019/09/12 18:41:50 by gtristan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblank(char const s)
{
	if (s == ' ' || s == '\n' || s == '\t')
		return (1);
	return (0);
}

static void	ft_i_init(size_t *i)
{
	int a;

	a = 0;
	while (a < 10)
	{
		i[a] = 0;
		a++;
	}
}

char		*ft_strtrim(char const *s)
{
	size_t	i[10];
	char	*str;

	ft_i_init(i);
	if (s == NULL)
		return (NULL);
	while (ft_isblank(s[i[0]]) == 1)
		i[0]++;
	i[1] = i[0];
	while (s[i[0]])
		i[0]++;
	while (--i[0] > i[1] && ft_isblank(s[i[0]]) == 1)
		;
	i[2] = i[0] - i[1] + 1;
	str = (char *)malloc(sizeof(char) * (i[2] + (i[1] > 0)));
	if (!str || (i[2] + 1 == 0))
		return (NULL);
	while (i[3] < i[2])
	{
		str[i[3]] = (char const)s[i[1]];
		i[3]++;
		i[1]++;
	}
	str[i[3]] = '\0';
	return (str);
}
