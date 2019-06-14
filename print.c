/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:32:28 by thaley            #+#    #+#             */
/*   Updated: 2019/06/14 16:15:38 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_w_indent(char *s, int indt)
{
	int	l;
	int indt_modulo;

	l = ft_strlen(s);
	indt_modulo = indt < 0 ? -indt : indt;
	if (indt_modulo < l)
		ft_putstr(s);
	else if (indt > 0)
	{
		indt_modulo -= l;
		while (indt_modulo--)
			ft_putchar(' ');
		ft_putstr(s);
	}
	else
	{
		ft_putstr(s);
		while (indt_modulo > l)
		{
			ft_putchar(' ');
			indt_modulo--;
		}
	}
}

int		*max_len(t_ls *ls)
{
	int		*max_len;

	max_len = (int *)malloc(sizeof(int) * 8);
	ft_bzero(max_len, (sizeof(int) * 8));
	while (ls)
	{
		if (ls->print)
		{
			max_len[0] < ft_strlen(ls->link)
			? max_len[0] = ft_strlen(ls->link) : 0;
			max_len[1] < ft_strlen(ls->user_name)
			? max_len[1] = ft_strlen(ls->user_name) : 0;
			max_len[2] < ft_strlen(ls->group_name)
			? max_len[2] = ft_strlen(ls->group_name) : 0;
			max_len[3] < ft_strlen(ls->size)
			? max_len[3] = ft_strlen(ls->size) : 0;
			max_len[4] < ft_strlen(ls->month)
			? max_len[4] = ft_strlen(ls->month) : 0;
			max_len[5] < ft_strlen(ls->day)
			? max_len[5] = ft_strlen(ls->day) : 0;
			max_len[6] < ft_strlen(ls->time)
			? max_len[6] = ft_strlen(ls->time) : 0;
			max_len[7] = ft_strlen(ls->name)
			? max_len[7] = ft_strlen(ls->name) : 0;
		}
		ls = ls->next;
	}
	return (max_len);
}

void	print_symlink(t_ls *ls)
{
	char	buf[100];

	print_w_indent(ls->name, ft_strlen(ls->name));
	buf[readlink(ls->path, buf, 100)] = '\0';
	print_w_indent(" -> ", 0);
	ft_putstr(buf);
}

void	write_ls_l(t_ls *ls, int blocks)
{
	int		*len;

	len = max_len(ls);
	ft_putstr("total ");
	ft_putnbr(blocks);
	write(1, "\n", 1);
	while (ls)
	{
		if (ls->print)
		{
			ft_putstr(ls->access.type);
			ft_putstr(ls->access.user);
			ft_putstr(ls->access.group);
			print_w_indent(ls->access.other, 3);
			write(1, "  ", 2);
			print_w_indent(ls->link, len[0]);
			write(1, " ", 1);
			print_w_indent(ls->user_name, len[1] * -1);
			write(1, "  ", 2);
			print_w_indent(ls->group_name, len[2] * -1);
			write(1, "  ", 2);
			print_w_indent(ls->size, len[3]);
			write(1, " ", 1);
			print_w_indent(ls->month, len[4]);
			write(1, " ", 1);
			print_w_indent(ls->day, len[5]);
			write(1, " ", 1);
			print_w_indent(ls->time, len[6]);
			write(1, " ", 1);
			if (ls->type == 10)
				print_symlink(ls);
			else
				print_w_indent(ls->name, (len[7] * -1));
			write(1, "\n", 1);
		}
		ls = ls->next;
	}
}

int		print_ls(t_ls *ls, t_flags *flag, int blocks, char *dir_name)
{
	if (dir_name)
	{
		write(1, "\n", 1);
		ft_putstr(dir_name);
		write(1, ":\n", 2);
	}
	if (flag->l)
		write_ls_l(ls, blocks);
	else
	{
		while (ls)
		{
			if (ls->print)
			{
				ft_putstr(ls->name);
				write(1, "   ", 3);
			}
			ls = ls->next;
		}
		write(1, "\n", 1);
	}
	return (0);
}
