/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepares.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 19:34:11 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/06/09 12:27:37 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parse_flags(t_flags *flag, char **av)
{
    char	*radix;
    int		i;
	int		j;

    *radix = "lRart";
	i = 1;
	while (av[i] && av[i][0] == "-")
	{

	}
}

