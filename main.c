/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:01:27 by thaley            #+#    #+#             */
/*   Updated: 2019/06/19 17:01:04 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parse_validate_flag(int *j, char f, t_flags *flag, char avijplus1)
{
	if (f == 'R')
		flag->recursive = 1;
	else if (f == 'a')
		flag->a = 1;
	else if (f == 'l')
		flag->l = 1;
	else if (f == 'r')
		flag->r = 1;
	else if (f == 't')
		flag->t = 1;
	else if (f == '1')
		flag->one_opt = 1;
	else if (f == '-' && !avijplus1)
		return (1);
	else
		illegal_opt_err(f);
	*j += 1;
	return (0);
}

int		parse_validate_flags(t_flags *flag, char **av)
{
	int		i;
	int		j;
	int		ifnonzero;

	i = 1;
	while (av[i] && av[i][0] == '-' && av[i][1])
	{
		j = 1;
		while (av[i][j])
			if ((ifnonzero = parse_validate_flag(&j, av[i][j], flag,
			av[i][j + 1])))
				return (i + 1);
		i++;
	}
	return (i);
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
	t_flags	flag;

	flag = create_flag();
	i = parse_validate_flags(&flag, argv);
	argv_sort(argc, argv, i, 1);
	if (i != argc)
	{
		flag.outside_flist = 1;
		flag.onedir = is_onlyonedir(argc, argv, i);
	}
	flag.outside_flist ? ls_custom(argv, i, &flag) : ls_dir(".", &flag, 0);
	return (0);
}
