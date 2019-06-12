/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:30:25 by thaley            #+#    #+#             */
/*   Updated: 2019/06/12 14:00:26 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls(char **argv, t_flags *flag, int i)
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
		print_ls(ls, flag, blocks, 0);
	}
	else
	{
		while (argv[i])
		{
			if ((ls = parse_direct(argv[i], flag)))
			{
				blocks = all_info(ls);
				ls = sort_list(ls, flag);
				print_ls(ls, flag, blocks, 0);
			}
			i++;
		}
	}
}

void	ls_dir(char *name, t_flags *flag, char **av, int name_n_indent)
{
	t_ls		*ls;
	int			blocks;

	if (!ft_strcmp(name, "..") || (name_n_indent && !ft_strcmp(name, ".")))
		return ;
	ls = parse_direct(name, flag);
	if (!flag->a)
		ls = rm_dotf(ls);
	blocks = all_info(ls);
	ls = sort_list(ls, flag);
	print_ls(ls, flag, blocks, name_n_indent ? name : 0);
	if (flag->R)
		while (ls)
		{
			if (ls->type == DT_DIR)
				ls_dir(ls->path, flag, 0, 1);
			ls = ls->next;
		}
}