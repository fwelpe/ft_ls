/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:30:25 by thaley            #+#    #+#             */
/*   Updated: 2019/06/10 19:23:54 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls(char **arg, t_flags *flag, int i)
{
	t_ls		*ls;
	int			blocks;

	blocks = 0;
	ls = NULL;
	if (!arg[i])
	{
		ls = parse_direct(".", flag);
		blocks = all_info(ls);
		ls = sort_list(ls, flag);
		print_ls(ls, flag, blocks);
	}
	else
	{
		while (arg[i])
		{
			ls = parse_direct(arg[i], flag);
			blocks = all_info(ls);
			ls = sort_list(ls, flag);
			print_ls(ls, flag, blocks);
			i++;
		}
	}
}