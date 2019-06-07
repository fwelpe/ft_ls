/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:50:06 by cdenys-a          #+#    #+#             */
/*   Updated: 2018/12/01 14:52:06 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	full_l;
	size_t	i;
	char	*pre_rt;
	char	*rt;

	if (!s1 || !s2)
		return (NULL);
	full_l = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	rt = (char *)malloc(full_l);
	if (!rt)
		return (NULL);
	pre_rt = ft_strdup(s1);
	rt = ft_strcat(pre_rt, s2);
	return (rt);
}
