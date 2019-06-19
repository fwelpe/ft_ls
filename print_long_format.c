/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 17:40:28 by thaley            #+#    #+#             */
/*   Updated: 2019/06/19 17:41:19 by thaley           ###   ########.fr       */
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
	if (ls->type == 10 || ls->type == 14)
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
