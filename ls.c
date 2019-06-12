/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:30:25 by thaley            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/12 17:28:34 by thaley           ###   ########.fr       */
=======
/*   Updated: 2019/06/12 18:13:30 by cdenys-a         ###   ########.fr       */
>>>>>>> master
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

void	nofile_err(char *filename)
{
	ft_putstr("ft_ls: ");
	ft_putstr(filename);
	ft_putendl(": No such file or directory");
}

void	report_nonexist(t_ls *ls, char **av)
{
	int		i;
	t_ls	*ls_head;
	int		report;

	i = calc_i_start(av);
	ls_head = ls;
	while(av[i])
	{
		ls = ls_head;
		report = 1;
		while (ls)
		{
			if (ft_strcmp(ls->name, av[i]))
				report = 0;
			ls = ls->next;
		}
		if (report)
			nofile_err(av[i]);
		i++;
	}
}

void	ls_argv_filter(t_ls **ls, char **av)
{
	t_ls	*ls_iter;
	int		i_start;
	int		i;
	int		exist;
	
	i_start = calc_i_start(av);
	ascii_sort(ls, 1);
	ls_iter = *ls;
	while (ls_iter)
	{
		ls_iter->print = 0;
		i = i_start;
		while(av[i])
		{
			if (!ft_strcmp(ls_iter->name, av[i]))
				ls_iter->print = 1;
			i++;
		}
		ls_iter = ls_iter->next;
	}
}

void	ls_dir(char *name, t_flags *flag, char **av, int name_n_indent)
{
	t_ls		*ls;
	int			blocks;

	ls = parse_direct(name, flag);
<<<<<<< HEAD
	blocks = all_info(ls, flag);
=======
	// if (!flag->a)
	// 	ls = rm_dotf(ls);
	blocks = all_info(ls);
>>>>>>> master
	if (av)
	{
		report_nonexist(ls, av);
		ls_argv_filter(&ls, av);
	}
	ls = sort_list(ls, flag);
	print_ls(ls, flag, blocks, name_n_indent ? name : 0);
	if (flag->R)
		while (ls)
		{
			if (ls->type == DT_DIR && ls->print &&
			(ft_strcmp(ls->name, ".") && ft_strcmp(ls->name, "..")))
				ls_dir(ls->path, flag, 0, 1);
			ls = ls->next;
		}
}
