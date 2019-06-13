/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:32:28 by thaley            #+#    #+#             */
/*   Updated: 2019/06/13 12:28:18 by cdenys-a         ###   ########.fr       */
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
		indt_modulo += l;
		ft_putstr(s);
		while (indt_modulo--)
			ft_putchar(' ');
	}

}

int		take_len(char *abs)
{
	int		max_len;
	size_t	len;

	len = ft_strlen(abs);
	if (max_len < len)
		max_len = len;
	return (max_len);
}

int		*max_len(t_ls *ls)
{
	int				*max_len;

	max_len[0] = 10;
	while (ls)
	{
		max_len[1] = take_len(ft_itoa(ls->link));
		max_len[2] = take_len(ls->user_name);
		max_len[3] = take_len(ls->group_name);
		max_len[4] = take_len(ft_itoa(ls->size));
		max_len[5] = take_len(ls->month);
		max_len[6] = take_len(ls->day);
		max_len[7] = take_len(ls->time);
		max_len[8] = take_len(ls->name);
		ls = ls->next;
	}
	return (max_len);
}

int		print_ls(t_ls *ls, t_flags *flag, int blocks, char *dir_name)
{
	char	buf[100];

		if (dir_name)
	{
		printf("\n");
		printf("%s", dir_name);
		printf(":\n");
	}
	if (flag->l == 1)
	{
		printf("total: %d\n", blocks);
		while (ls)
		{
			if (ls->print || dir_name)
			{
				printf("%s", ls->access.type);
				printf("%s", ls->access.user);
				printf("%s", ls->access.group);
				printf("%s ", ls->access.other);
				printf("%4d ", ls->link);
				printf("%3s ", ls->user_name);
				printf("%2s ", ls->group_name);
				printf("%6d ", ls->size);
				printf("%-3s ", ls->month);
				printf("%-2s ", ls->day);
				printf("%-5s ", ls->time);
				printf("%1s", ls->name);
				if (ls->type == 10)
				{
					buf[readlink(ls->path, buf, 100)] = '\0';
					printf(" -> %s", buf);
				}
				printf("\n");
			}
			ls = ls->next;
		}
	}
	else if (flag->l == 0)
	{
		while (ls)
		{
			if (ls->print || dir_name)
				printf("%s  ", ls->name);
			ls = ls->next;
		}
		printf("\n");
	}
	return (0);
}
