/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:43:28 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/06/19 17:08:05 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	illegal_opt_err(char opt)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(opt, 2);
	ft_putendl_fd("\nusage: ft_ls [-Ralrt] [file ...]", 2);
	exit(1);
}

int		opening_check(char *name)
{
	DIR	*dir;

	if (!name)
		return (1);
	if (!(dir = opendir(name)))
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (0);
	}
	closedir(dir);
	return (1);
}

void	perroring(char *msg)
{
	ft_putstr_fd("ft_ls: ", 2);
	perror(msg);
}
