/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 20:34:02 by thaley            #+#    #+#             */
/*   Updated: 2019/06/07 17:16:56 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_print(char *str, int count, unsigned short n)
{
	while (count > 0)
	{
		str[count - 1] = n % 8 + '0';
		count--;
		n /= 8;
	}
}

char		*ft_unitoa(unsigned short n)
{
	char			*str;
	int				count;
	unsigned short	n_len;

	count = 1;
	n_len = n;
	// printf("+\n");
	while (n_len / 8)
	{
		n_len /= 8;
		count++;
	}
	if (!(str = ft_strnew(count)))
		return (NULL);
	ft_print(str, count, n);
	return (str);
}
