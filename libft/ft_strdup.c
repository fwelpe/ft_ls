/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:31:33 by cdenys-a          #+#    #+#             */
/*   Updated: 2018/12/01 14:51:45 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	int		full_l;
	int		i;
	char	*s;

	full_l = ft_strlen(s1) + 1;
	i = 0;
	s = (char *)malloc(full_l);
	if (!s)
		return (NULL);
	while (i < full_l)
	{
		s[i] = s1[i];
		i++;
	}
	return (s);
}
