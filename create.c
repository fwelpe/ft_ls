/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:47:14 by thaley            #+#    #+#             */
/*   Updated: 2019/06/12 17:59:47 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags		*create_flag(void)
{
	t_flags	*flag;

	flag = NULL;
	{
		if (!(flag = (t_flags *)malloc(sizeof(t_flags))))
			return (NULL);
		flag->l = 0;
		flag->a = 0;
		flag->r = 0;
		flag->R = 0;
		flag->t = 0;
		flag->outside_flist = 0;
	}
	return (flag);
}

t_ls		*add_list(t_ls *head)
{
	t_ls	*tmp;
	t_ls	*new;

	tmp = head;
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
