/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:01:27 by thaley            #+#    #+#             */
/*   Updated: 2019/06/09 18:44:22 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	erroring1(char msg)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(msg, 2);
	ft_putendl_fd(
	"\nusage: ft_ls [-laRrt] [file ...]",
	2);
	exit(1);
}

int		find_validate_flags(t_flags *flag, char *arg)
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
			erroring1(arg[i]);
		i++;
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int		i;
	int		count;
	t_flags	*flag;
	char	wrong_flag[3];

	i = 1;
	count = 0;
	flag = create_flag();
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			find_validate_flags(flag, argv[i]);
			i++;
		}
		if (argv[i])
		{
			write_info(argv[i], flag);
			i++;
			count++;
		}
	}
	if (!count || argc == 1)
		write_info(".", flag);
	return (0);
}
