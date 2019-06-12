/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:01:27 by thaley            #+#    #+#             */
/*   Updated: 2019/06/12 15:53:23 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	erroring1(char msg)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(msg, 2);
	ft_putendl_fd("\nusage: ft_ls [-Ralrt] [file ...]",	2);
	exit(1);
}

void	erroring2(int argc, char **argv, int i)
{
	DIR				*dir;

	while (i < argc)
	{
		if ((dir = opendir(argv[i])) == NULL)
		{
			ft_putstr("ft_ls: ");
			perror(argv[i]);
		}
		else
			closedir(dir);
		dir = NULL;
		i++;
	}
}

int		parse_validate_flags(t_flags *flag, char *arg)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'R')
			flag->R = 1;
		else if (arg[i] == 'a')
			flag->a = 1;
		else if (arg[i] == 'l')
			flag->l = 1;
		else if (arg[i] == 'r')
			flag->r = 1;
		else if (arg[i] == 't')
			flag->t = 1;
		else
			erroring1(arg[i]);
		i++;
	}
	return (1);
}

void	argv_sort(int argc, char **argv, int i, int order)
{
	char	*tmp;
	int		i_mem;

	i_mem = i;
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], argv[i + 1]) * order > 0)
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
			i = i_mem;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	int		i;
	t_flags	*flag;

	i = 1;
	flag = create_flag();
	while (argv[i] && argv[i][0] == '-')
	{
		parse_validate_flags(flag, argv[i]);
		i++;
	}
	if (i != argc)
		flag->outside_flist = 1;
	// argv_sort(argc, argv, i, 1);
	// erroring2(argc, argv, i);
	// if (flag->r)
	// 	argv_sort(argc, argv, i, -1);
	// ls(argv, flag, i);
	ls_dir(".", flag, flag->outside_flist ? argv : 0, 0);
	return (0);
}
