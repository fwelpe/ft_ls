/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:01:27 by thaley            #+#    #+#             */
/*   Updated: 2019/06/18 17:22:04 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		parse_validate_flags(t_flags *flag, char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[i] && av[i][0] == '-' && av[i][1])
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'R')
				flag->recursive = 1;
			else if (av[i][j] == 'a')
				flag->a = 1;
			else if (av[i][j] == 'l')
				flag->l = 1;
			else if (av[i][j] == 'r')
				flag->r = 1;
			else if (av[i][j] == 't')
				flag->t = 1;
			else if (av[i][j] == '1')
				flag->one_opt = 1;
			else if (av[i][j] == '-' && !av[i][j + 1])
				return (i + 1);
			else
				illegal_opt_err(av[i][j]);
			j++;
		}
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
