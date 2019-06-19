/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:39:07 by thaley            #+#    #+#             */
/*   Updated: 2019/06/19 17:39:41 by cdenys-a         ###   ########.fr       */
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
	t_ls	*head;
	t_ls	*curr;
	t_ls	*next;

	head = NULL;
	while (*ls_head)
	{
		curr = *ls_head;
		*ls_head = (*ls_head)->next;
		if (head == NULL || ft_strcmp(curr->name, head->name) * order < 0)
		{
			curr->next = head;
			head = curr;
		}
		else
		{
			next = head;
			while (next->next != NULL && ft_strcmp(curr->name,
			next->next->name) * order > 0)
				next = next->next;
			curr->next = next->next;
			next->next = curr;
		}
	}
	*ls_head = head;
}

void		timesort_swap(t_ls **ls_h, t_ls **prev, t_ls **curr, t_ls **next)
{
	if (*prev)
		(*prev)->next = *next;
	if (*curr == *ls_h)
		*ls_h = *next;
	(*curr)->next = (*next)->next;
	(*next)->next = *curr;
	*curr = *next;
}

void		timesort_gotohead(t_ls **prev, int *s, t_ls **ls_head, t_ls **curr)
{
	*prev = NULL;
	*curr = *ls_head;
	*s = 1;
}

void		time_sort(t_ls **ls_head, int order)
{
	t_ls	*prev;
	t_ls	*curr;
	t_ls	*next;
	int		sorted;

	prev = NULL;
	curr = *ls_head;
	sorted = 1;
	while (curr)
	{
		next = curr->next;
		if (next && (((curr->unix_time - next->unix_time) * order) < 0))
		{
			sorted = 0;
			timesort_swap(ls_head, &prev, &curr, &next);
		}
		else if (!next && !sorted)
			timesort_gotohead(&prev, &sorted, ls_head, &curr);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
