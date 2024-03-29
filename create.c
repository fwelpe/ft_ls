/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:47:14 by thaley            #+#    #+#             */
/*   Updated: 2019/06/18 13:59:20 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags		create_flag(void)
{
	t_flags	flag;

	flag.l = 0;
	flag.a = 0;
	flag.r = 0;
	flag.recursive = 0;
	flag.t = 0;
	flag.outside_flist = 0;
	flag.indt_custom = 0;
	flag.onedir = 0;
	flag.one_opt = 0;
	flag.first = 1;
	return (flag);
}

t_ls		*add_list(t_ls *last)
{
	t_ls	*tmp;
	t_ls	*new;

	tmp = last;
	new = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(new, sizeof(t_ls));
	if (tmp == NULL)
		return (new);
	else
	{
		tmp->next = new;
		new->next = NULL;
	}
	return (new);
}
