/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 23:47:09 by cdenys-a          #+#    #+#             */
/*   Updated: 2018/12/01 14:52:20 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*pre_rt;
	char			cell;
	char			*rt;

	if (!s || !f)
		return (NULL);
	i = 0;
	j = 0;
	pre_rt = (char *)malloc(ft_strlen(s) + 1);
	if (!pre_rt)
		return (NULL);
	while (s[i])
	{
		if ((cell = f(i, s[i])))
			pre_rt[j++] = cell;
		i++;
	}
	pre_rt[j] = '\0';
	rt = ft_strdup(pre_rt);
	free(pre_rt);
	if (!rt)
		return (NULL);
	return (rt);
}
