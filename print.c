/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:32:28 by thaley            #+#    #+#             */
/*   Updated: 2019/06/18 17:06:45 by cdenys-a         ###   ########.fr       */
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
		indt_modulo -= l;
		ft_putstr(s);
		while (indt_modulo--)
			ft_putchar(' ');
	}
}

void	max_len(t_ls *ls, int **max_len)
{
	int		len;

	while (ls)
	{
		if (ls->print)
		{
			if ((*max_len)[0] < (len = ft_strlen(ls->link)))
				(*max_len)[0] = ft_strlen(ls->link);
			if ((*max_len)[1] < (len = ft_strlen(ls->user_name)))
				(*max_len)[1] = ft_strlen(ls->user_name);
			if ((*max_len)[2] < (len = ft_strlen(ls->group_name)))
				(*max_len)[2] = ft_strlen(ls->group_name);
			if ((*max_len)[3] < (len = ft_strlen(ls->size)))
				(*max_len)[3] = ft_strlen(ls->size);
			if ((*max_len)[4] < (len = ft_strlen(ls->month)))
				(*max_len)[4] = ft_strlen(ls->month);
			if ((*max_len)[5] < (len = ft_strlen(ls->day)))
				(*max_len)[5] = ft_strlen(ls->day);
			if ((*max_len)[6] < (len = ft_strlen(ls->time)))
				(*max_len)[6] = ft_strlen(ls->time);
			if ((*max_len)[7] < (len = ft_strlen(ls->name)))
				(*max_len)[7] = ft_strlen(ls->name);
		}
		ls = ls->next;
	}
}

void	print_ls_info(t_ls *ls, int *len, char *buf)
{
	ft_putstr(ls->access.type);
	ft_putstr(ls->access.user);
	ft_putstr(ls->access.group);
	print_w_indent(ls->access.other, -5);
	print_w_indent(ls->link, len[0]);
	write(1, " ", 1);
	print_w_indent(ls->user_name, (len[1] + 2) * -1);
	print_w_indent(ls->group_name, (len[2] + 2) * -1);
	print_w_indent(ls->size, len[3]);
	print_w_indent(ls->month, len[4] + 1);
	write(1, " ", 1);
	print_w_indent(ls->day, len[5]);
	write(1, " ", 1);
	print_w_indent(ls->time, len[6]);
	write(1, " ", 1);
	if (ls->type == 10)
	{
		print_w_indent(ls->name, ft_strlen(ls->name));
		buf[readlink(ls->path, buf, 100)] = '\0';
		write(1, " -> ", 4);
		ft_putstr(buf);
	}
	else
		print_w_indent(ls->name, 0);
}

void	print_ls_l(t_ls *ls, int blocks, t_flags *f)
{
	int		*len;
	char	buf[225];

	len = (int *)malloc(sizeof(int) * 8);
	ft_bzero(len, (sizeof(int) * 8));
	max_len(ls, &len);
	if (blocks != -1)
	{
		ft_putstr("total ");
		ft_putnbr(blocks);
		write(1, "\n", 1);
	}
	while (ls)
	{
		if (ls->print)
		{
			f->indt_custom = 1;
			print_ls_info(ls, len, buf);
			write(1, "\n", 1);
		}
		ls = ls->next;
	}
	free(len);
}

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

int    opening_check(char *name)
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
	flag->first = 0;
	return (0);
}
