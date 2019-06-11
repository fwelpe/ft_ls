/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:30:25 by thaley            #+#    #+#             */
/*   Updated: 2019/06/11 22:58:04 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls(char **argv, t_flags *flag, int i)
{
	t_ls		*ls;
	int			blocks;

	blocks = 0;
	ls = NULL;
	if (!flag->outside_flist)
	{
		ls = parse_direct(".", flag);
		blocks = all_info(ls);
		ls = sort_list(ls, flag);
		print_ls(ls, flag, blocks);
	}
	else
	{
		while (argv[i])
		{
			if ((ls = parse_direct(argv[i], flag)))
			{
				blocks = all_info(ls);
				ls = sort_list(ls, flag);
				print_ls(ls, flag, blocks);
			}
			i++;
		}
	}
}

/* void			ls_dir(char *name, t_flags *flag, int name_n_indent)
{
	t_ls		*ls;
	int			blocks;
	
	blocks = 0;
	ls = NULL;
	ls = parse_direct(name, flag);
	blocks = all_info(ls);
	ls = sort_list(ls, flag);
	print_ls(ls, flag, blocks);
} */