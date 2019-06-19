/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:32:28 by thaley            #+#    #+#             */
/*   Updated: 2019/06/19 17:41:45 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_for_noprint(t_ls *ls)
{
	while (ls)
	{
		if (ls->print)
			return (1);
		ls = ls->next;
	}
	return (0);
}

int		is_last(t_ls *ls)
{
	while (ls)
	{
		ls = ls->next;
		if (ls && ls->print)
			return (0);
	}
	return (1);
}

void	print_standart(t_ls *ls, t_flags *flag)
{
	while (ls)
	{
		if (ls->print)
		{
			ft_putstr(ls->name);
			if (!is_last(ls))
				flag->one_opt ? write(1, "\n", 1) : write(1, "   ", 3);
		}
		ls = ls->next;
	}
	write(1, "\n", 1);
}

int		print_ls(t_ls *ls, t_flags *flag, int blocks, char *dir_name)
{
	int	files_to_print;

	files_to_print = check_for_noprint(ls);
	if ((files_to_print || dir_name) && !flag->first)
		write(1, "\n", 1);
	if (dir_name)
	{
		ft_putstr(dir_name);
		write(1, ":\n", 2);
		flag->first = 0;
	}
	if (!opening_check(dir_name) || !files_to_print)
		return (0);
	if (flag->l)
		print_ls_l(ls, blocks, flag);
	else
	{
		print_standart(ls, flag);
	}
	flag->first = 0;
	return (0);
}
