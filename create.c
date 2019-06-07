/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 14:47:14 by thaley            #+#    #+#             */
/*   Updated: 2019/04/03 15:09:43 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags	*creat_flag()
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
	new->count = 0;
	new->size = 0;
	new->link = 0;
	new->uid = 0;
	new->name = NULL;
	new->acess = NULL;
	new->m_time = NULL;
	new->sort_time = NULL;
	new->user_name = NULL;
	new->group_name = NULL;
	new->print_name = NULL;
	new->next = NULL;
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
	new->group = NULL;
	new->other = NULL;
	new->type = NULL;
	new->user = NULL;
	new->next = NULL;
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

t_date		*crt_date(t_date *head)
{
	t_date	*new;
	t_date	*tmp;

	tmp = head;
	new = (t_date *)malloc(sizeof(t_date));
	new->next = NULL;
	new->sek = 0;
	new->day = 0;
	new->week = 0;
	new->mnth = 0;
	new->min = 0;
	new->year = 0;
	new->hour = 0;
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
