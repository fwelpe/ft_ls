/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:30:25 by thaley            #+#    #+#             */
/*   Updated: 2019/06/12 16:27:21 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* void	ls(char **argv, t_flags *flag, int i)
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
} */

int		calc_i_start(char **av)
{
	int	i;

	i = 1;
	while(av[i][0] == '-')
		i++;
	return (i);
}

t_ls	*cut_n_error(t_ls *ls)
{
	ft_putstr("ft_ls: ");
	ft_putstr(ls->name);
	ft_putendl(": No such file or directory");

}

t_ls	*ls_filter(t_ls *ls, char **av)
{
	t_ls	*ls_head;
	int		i_start;
	int		i;
	int		exist;
	
	i_start = calc_i_start(av);
	ascii_sort(&ls, 1);
	ls_head = ls;
	while (ls)
	{
		exist = 0;
		i = i_start;
		while(av[i])
		{
			if (!ft_strcmp(ls->name, av[i]))
				exist = 1;
			i++;
		}
		if (!exist)
			ls = cut_n_error(ls);
		ls = ls->next;
	}
}

void	ls_dir(char *name, t_flags *flag, char **av, int name_n_indent)
{
	t_ls		*ls;
	int			blocks;

	ls = parse_direct(name, flag);
	if (!flag->a)
		ls = rm_dotf(ls);
	blocks = all_info(ls);
	if (av)
		ls = ls_filter(ls, av);
	ls = sort_list(ls, flag);
	print_ls(ls, flag, blocks, name_n_indent ? name : 0);
	if (flag->R)
		while (ls)
		{
			if (ls->type == DT_DIR &&
			(ft_strcmp(ls->name, ".") && ft_strcmp(ls->name, "..")))
				ls_dir(ls->path, flag, 0, 1);
			ls = ls->next;
		}
}
