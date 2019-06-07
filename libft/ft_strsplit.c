/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 13:31:38 by cdenys-a          #+#    #+#             */
/*   Updated: 2018/12/02 17:01:09 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	mlc_count(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i + 1);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**result;
	int			i;
	size_t		j;
	char const	*crwr;

	if (!s)
		return (NULL);
	result = (char**)malloc(sizeof(char*) * (ft_countwords(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	crwr = s;
	while ((j < ft_countwords(s, c)) && *crwr)
	{
		while (*crwr == c)
			crwr++;
		result[j] = (char*)malloc(sizeof(char) * mlc_count(crwr, c));
		while ((*crwr != c) && *crwr)
			result[j][i++] = *(crwr++);
		result[j++][i] = '\0';
		i = 0;
	}
	result[j] = (NULL);
	return (result);
}
