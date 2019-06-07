/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:01:27 by thaley            #+#    #+#             */
/*   Updated: 2019/06/07 17:09:24 by thaley           ###   ########.fr       */
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
			find_flag(flag, argv[i]);
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

int		find_flag(t_flags *flag, char *argv)
{
	int		i;
	int		j;
	char tmp[5] = {'l', 'a', 'r', 'R', 't'};

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i] != 'l' && argv[i] != 'a' && argv[i] != 'r'
			&& argv[i] != 'R' && argv[i] != 't')
			return(0);
		while (tmp[j])
		{
			if (argv[i] == tmp[j])
			{
				j == 0 ? (flag->l = 1) : 0;
				j == 1 ? (flag->a = 1) : 0;
				j == 2 ? (flag->r = 1) : 0;
				j == 3 ? (flag->R = 1) : 0;
				j == 4 ? (flag->t = 1) : 0;
			}
			j++;
		}
		i++;
	}
	return (1);
}

