/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:32:28 by thaley            #+#    #+#             */
/*   Updated: 2019/04/02 19:56:33 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_ls(t_ls *ls, t_flags *flag, t_access *access, int blocks)
{
	if (flag->l == 1)
	{
		printf("total: %d\n", blocks);
		while (ls)
		{
			printf("%s", access->type);
			printf("%s", access->user);
			printf("%s", access->group);
			printf("%s ", access->other);
			printf("%4d ", ls->link);
			printf("%3s ", ls->user_name);
			printf("%2s ", ls->group_name);
			printf("%6d ", ls->size);
			printf("%-1s ", ls->m_time);
			printf("%1s\n", ls->print_name);
			ls = ls->next;
			access = access->next;
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
