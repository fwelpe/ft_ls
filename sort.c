/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:39:07 by thaley            #+#    #+#             */
/*   Updated: 2019/06/09 12:12:17 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_string(t_ls *ls, t_flags *flag, t_access *access)
{
	int		blocks;

	blocks = 0;
	if (!flag->a)
		ls = rm_dotf(ls);
	if (flag->t)
	{
		time_sort(ls, 1);
	}
	else if (flag->r)
		ascii_sort(ls, 2);
	else
		ascii_sort(ls, 1);
	// if (flag->t && flag->r)
	// 	time_sort(ls, 2);
	// if (flag->t)
	// {
	// 	take_stime(ls);
		// time_sort(ls, 1);
	// }
	if (flag->l)
	{
		blocks = all_info(ls);
		user_info(ls);
		take_rights(ls, access);
	}
	print_ls(ls, flag, access, blocks);
	return (blocks);
}

t_ls	*rm_dotf(t_ls *ls)
{
	t_ls	*head;

	head = ls;
	while (ls->print_name[0] == '.')
	{
		head = ls->next;
		free(ls->name);
		free(ls->print_name);
		free(ls);
		ls = head;
	}
	while (ls)
	{
		if (ls->print_name[0] == '.')
		{
			while (head && head->next != ls)
				head = head->next;
			head->next = ls->next;
			free(ls->name);
			free(ls->print_name);
			free(ls);
			ls = head;
		}
		ls = ls->next;
	}
	ls = head;
	return (ls);
}

int		ascii_sort(t_ls *ls, int order)
{
	t_ls	*head;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (ls == NULL)
		return (1);
	head = ls;
	while (ls)
	{
		i = ft_strcmp(ls->print_name, head->print_name);
		order == 1 ? (i = -1 * i) : (i = i * 1);
		if (i > 0)
		{
			tmp = head->print_name;
			head->print_name = ls->print_name;
			ls->print_name = tmp;
			tmp = head->name;
			head->name = ls->name;
			ls->name = tmp;
		}
		ls = ls->next;
		if (ls == NULL)
		{
			if (ascii_sort(head->next, order))
				return (1);
		}
	}
	return (0);
}

int		test_time_sort(t_ls *ls)
{
	char		*tmp;
	long int	temp;
	t_ls		*head;
	int			s_time;
	int			s_letter;

	tmp = NULL;
	if (ls == NULL)
		return (1);
	head = ls;
	while (ls)
	{
		s_time = (ls->sort_time - head->sort_time);
		s_letter = ft_strcmp(ls->print_name, head->print_name);
		if (s_time > 0 || (s_time == 0 && s_letter < 0))
		{
			tmp = head->print_name;
			head->print_name = ls->print_name;
			ls->print_name = tmp;
			tmp = head->name;
			head->name = ls->name;
			ls->name = tmp;
			temp = head->sort_time;
			head->sort_time = ls->sort_time;
			ls->sort_time = temp;
		}
		ls = ls->next;
		if (ls == NULL)
		{
			if (test_time_sort(head->next))
				return (1);
		}
	}
	return (0);
}

int		time_sort(t_ls *ls, int order)
{
	struct stat	buf;
	t_date		*date;
	t_ls		*head;
	long int	ttime;

	date = NULL;
	head = ls;
	while (ls)
	{
		stat(ls->name, &buf);
		ls->sort_time = buf.st_mtime;
		ls = ls->next;
	}
	ls = head;
	test_time_sort(ls);
	return (0);
}

int		take_stime(t_ls *ls)
{
	struct stat	buf;
	t_ls		*head;
	size_t		i;

	i = 0;
	head = ls;
	while (ls)
	{
		stat(ls->name, &buf);
		ls->sort_time = buf.st_mtime;
		ls = ls->next;
	}
	ls = head;
	return (0);
}
