/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:32:28 by thaley            #+#    #+#             */
/*   Updated: 2019/06/10 18:03:29 by cdenys-a         ###   ########.fr       */
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

int		print_ls(t_ls *ls, t_flags *flag, int blocks)
{
	char	buf[100];

	if (flag->l == 1)
	{
		printf("total: %d\n", blocks);
		while (ls)
		{
			printf("%s", ls->access.type);
			printf("%s", ls->access.user);
			printf("%s", ls->access.group);
			printf("%s ", ls->access.other);
			printf("%4d ", ls->link);
			printf("%3s ", ls->user_name);
			printf("%2s ", ls->group_name);
			printf("%6d ", ls->size);
			printf("%-1s ", ls->m_time);
			printf("%1s", ls->name);
			if (ls->type == 10)
			{
				buf[readlink(ls->path, buf, 100)] = '\0';
				printf(" -> %s", buf);
			}
			printf("\n");
			ls = ls->next;
		}
	}
	else if (flag->l == 0)
	{
		while (ls)
		{
			printf("%s  ", ls->name);
			ls = ls->next;
		}
		printf("\n");
	}
	return (0);
}
