/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:01:27 by thaley            #+#    #+#             */
/*   Updated: 2019/06/07 20:29:33 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Seg time sort, dont work -r flag!!

int		main(int argc, char ** argv)
{
	int		i;
	int		count;
	t_flags	*flag;

	i = 1;
	count = 0;
	flag = creat_flag();
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			find_flags(flag, argv[i]);
			i++;
		}
		if (argv[i])
		{
			take_dir(argv[i], flag);
			i++;
			count++;
		}
	}
	if (!count || argc == 1)
		take_dir(".", flag);
	return (0);
}

int		take_dir(char *argv, t_flags *flag) //TODO: count numb of directories
{
	char	*direct;

	direct = NULL;
	if ((direct = ft_strdup(argv)))
		write_info(direct, flag);
	else
	{
		perror("can't malloc memmory\n");
		return (0);
	}
	return (1);
}

int		find_flags(t_flags *flag, char *arg)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'l')
			flag->l = 1;
		else if (arg[i] == 'R')
			flag->R = 1;
		else if (arg[i] == 'a')
			flag->a = 1;
		else if (arg[i] == 'r')
			flag->r = 1;
		else if (arg[i] == 't')
			flag->t = 1;
		else
			return (0);
		i++;
	}
	return (1);
}
