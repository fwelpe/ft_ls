/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:47:14 by thaley            #+#    #+#             */
/*   Updated: 2019/06/09 13:24:00 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags	*create_flag()
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
	}
	return (flag);
}

t_ls	*add_list(t_ls *head)
{
	t_ls	*tmp;
	t_ls	*new;

	tmp = head;
	new = (t_ls *)malloc(sizeof(t_ls));
	ft_bzero(new, sizeof(t_ls));
	if (tmp == NULL)
		head = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_access	*creat_access(t_access *head)
{
	t_access	*new;
	t_access	*tmp;

	tmp = head;
	new = (t_access *)malloc(sizeof(t_access));
	ft_bzero(new, sizeof(t_access));
	if (tmp == NULL)
		head = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}
