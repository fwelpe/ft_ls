/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:30:25 by thaley            #+#    #+#             */
/*   Updated: 2019/06/10 13:56:01 by thaley           ###   ########.fr       */
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
		ls = write_info(".", flag);
		blocks = all_info(ls);
		ls = sort_list(ls, flag);
		print_ls(ls, flag, blocks);
	}
	else
	{
		while (arg[i])
		{
			ls = write_info(arg[i], flag);
			blocks = all_info(ls);
			ls = sort_list(ls, flag);
			print_ls(ls, flag, blocks);
			i++;
		}
	}
}