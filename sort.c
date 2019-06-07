/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:39:07 by thaley            #+#    #+#             */
/*   Updated: 2019/06/07 17:11:31 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_string(t_ls *ls, t_flags *flag, t_access *access)
{
	int		blocks;

	blocks = 0;
	if (flag->r)
		ascii_sort(ls, 2);
	else
		ascii_sort(ls, 1);
	if (!flag->a)
		ls = rm_dotf(ls);
	if (flag->t)
	{
		time_sort(ls, 1);
	}
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

int		time_sort(t_ls *ls, int order)
{
	struct stat	buf;
	t_date		*date;
	t_ls		*head;

	date = NULL;
	head = ls;
	while (ls)
	{
		stat(ls->name, &buf);
		ls->sort_time = ft_strdup(ctime(&buf.st_mtime));
		ls = ls->next;
	}
	ls = head;
	date = mod_time(ls);
	sort(date, ls, order);
	return (0);
}

int		sort(t_date *date, t_ls *ls, int order)
{
	t_ls	*head;
	t_date	*h;
	t_date	*temp;
	t_date	*tdate;
	char	*tmp;
	int		i;

	i = 0;
	head = ls;
	h = date;
	tmp = NULL;
	temp = NULL;
	tdate = NULL;
	if (date == NULL || ls == NULL)
		return (1);
	while (date && ls)
	{
		i = ft_datecmp(date, h);
		order == 1 ? (i = -1 * i) : (i = i * 1);
		if (i > 0)
		{
			tmp = head->print_name;
			head->print_name = ls->print_name;
			ls->print_name = tmp;
			tmp = head->name;
			head->name = ls->name;
			ls->name = tmp;
			tdate = date->next;
			h->next = tdate;
			date->next = h;
		}
		ls = ls->next;
		date = date->next;
		if (date == NULL || ls == NULL)
		{
			if (sort(h->next, head->next, order))
				return (1);
		}
	}
	return (0);
}

int		ft_datecmp(t_date *date, t_date *next)
{
	if (date->year == next->year)
	{
		if (date->mnth == next->mnth)
		{
			if (date->week == next->week)
			{
				if (date->day == next->day)
				{
					if (date->hour == next->hour)
					{
						if (date->min == next->min)
							return (date->sek - next->sek);
						else
							return (date->min - next->min);
					}
					else
						return (date->hour - next->hour);
				}
				else
					return (date->day - next->day);
			}
			else
				return (date->week - next->week);
		}
		else
			return (date->mnth - next->mnth);
	}
	return (date->year - next->year);
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
		ls->sort_time = ft_strdup(ctime(&buf.st_mtime));
		printf("%s\n", ls->sort_time);
		ls = ls->next;
	}
	ls = head;
	while (ls)
	{
		i = ft_strlen(ls->sort_time);

	}
	return (0);
}
