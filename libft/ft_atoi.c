/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:52:40 by cdenys-a          #+#    #+#             */
/*   Updated: 2018/12/01 19:09:01 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

int	ft_atoi(const char *str_in)
{
	long long	num;
	long long	sign;
	char		*str;

	num = 0;
	sign = 1;
	str = (char*)str_in;
	while (*str == '\n' || *str == ' ' || *str == '\t' || *str == '\r' ||
			*str == '\v' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= 0x30 && *str <= 0x39)
	{
		num = num * 10 + *str++ - '0';
	}
	return ((int)(num * sign));
}
