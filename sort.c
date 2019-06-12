/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:39:07 by thaley            #+#    #+#             */
/*   Updated: 2019/06/12 17:10:10 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls		*sort_list(t_ls *ls, t_flags *flag)
{
	if (flag->r)
		ascii_sort(&ls, -1);
	else
		ascii_sort(&ls, 1);
	if (flag->t && flag->r)
		time_sort(&ls, -1);
	else if (flag->t && !flag->r)
		time_sort(&ls, 1);
	if (flag->l)
	{
		user_info(ls);
	}
	return (ls);
}

void		ascii_sort(t_ls **ls_head, int order)
{
	t_ls	*prev;
	t_ls	*curr;
	t_ls	*next;

	prev = NULL;
	curr = *ls_head;
	while (curr)
	{
		next = curr->next;
		if (next && ft_strcmp(curr->name, next->name) * order > 0)
		{
			if (prev)
				prev->next = next;
			if (curr == *ls_head)
				*ls_head = next;
			curr->next = next->next;
			next->next = curr;
			curr = *ls_head;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void		time_sort(t_ls **ls_head, int order)
{
	t_ls	*prev;
	t_ls	*curr;
	t_ls	*next;

	prev = NULL;
	curr = *ls_head;
	while (curr)
	{
		next = curr->next;
		if (next && (((curr->unix_time - next->unix_time) * order) < 0))
		{
			if (prev)
				prev->next = next;
			if (curr == *ls_head)
				*ls_head = next;
			curr->next = next->next;
			next->next = curr;
			curr = *ls_head;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
