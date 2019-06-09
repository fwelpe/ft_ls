/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:32:28 by thaley            #+#    #+#             */
/*   Updated: 2019/06/09 15:10:05 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_ls(t_ls *ls, t_flags *flag, int blocks)
{
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
			printf("%1s\n", ls->name);
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
