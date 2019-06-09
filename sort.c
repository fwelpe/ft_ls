/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:39:07 by thaley            #+#    #+#             */
/*   Updated: 2019/06/09 15:07:15 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_string(t_ls *ls, t_flags *flag)
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
	if (flag->l)
	{
		blocks = all_info(ls);
		user_info(ls);
	}
	print_ls(ls, flag, blocks);
	return (blocks);
}

t_ls	*rm_dotf(t_ls *ls)
{
	t_ls	*head;

	head = ls;
	while (ls->name[0] == '.')
	{
		head = ls->next;
		free(ls->path);
		free(ls->name);
		free(ls);
		ls = head;
	}
	while (ls)
	{
		if (ls->name[0] == '.')
		{
			while (head && head->next != ls)
				head = head->next;
			head->next = ls->next;
			free(ls->path);
			free(ls->name);
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
		i = ft_strcmp(ls->name, head->name);
		order == 1 ? (i = -1 * i) : (i = i * 1);
		if (i > 0)
		{
			tmp = head->name;
			head->name = ls->name;
			ls->name = tmp;
			tmp = head->path;
			head->path = ls->path;
			ls->path = tmp;
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
		s_time = (ls->unix_time - head->unix_time);
		s_letter = ft_strcmp(ls->name, head->name);
		if (s_time > 0 || (s_time == 0 && s_letter < 0))
		{
			tmp = head->name;
			head->name = ls->name;
			ls->name = tmp;
			tmp = head->path;
			head->path = ls->path;
			ls->path = tmp;
			temp = head->unix_time;
			head->unix_time = ls->unix_time;
			ls->unix_time = temp;
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
	t_ls		*head;

	head = ls;
	while (ls)
	{
		stat(ls->path, &buf);
		ls->unix_time = buf.st_mtime;
		ls = ls->next;
	}
	ls = head;
	test_time_sort(ls);
	return (0);
}
