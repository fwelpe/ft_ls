/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   date.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:33:43 by thaley            #+#    #+#             */
/*   Updated: 2019/04/03 15:44:32 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_date	*mod_time(t_ls *ls)
{
	t_date	*new;
	t_date	*head;

	new = crt_date(NULL);
	head = new;
	while (ls)
	{
		if (new->year)
		{
			new->next = crt_date(new);
			new = new->next;
		}
		new->week = take_week(ls->sort_time);
		new->mnth = take_month(ls->sort_time);
		take_other(ls, new);
		ls = ls->next;
	}
	new = head;
	return (new);
}

int		take_week(char *sort_time)
{
	int		new;
	char	*week;

	week = ft_strsub(sort_time, 0, 3);
	new = 0;
	(ft_strcmp(week, "Mon") == 0) ? new = 1 : 0;
	(ft_strcmp(week, "Tue") == 0) ? new = 2 : 0; 
	(ft_strcmp(week, "Wed") == 0) ? new = 3 : 0; 
	(ft_strcmp(week, "Thu") == 0) ? new = 4 : 0; 
	(ft_strcmp(week, "Fri") == 0) ? new = 5 : 0; 
	(ft_strcmp(week, "Sat") == 0) ? new = 6 : 0; 
	(ft_strcmp(week, "Sun") == 0) ? new = 7 : 0;
	free(week);
	week = NULL; 
	return (new);
}

int		take_month(char *sort_time)
{
	int		m;
	char	*month;

	m = 0;
	month = ft_strsub(sort_time, 4, 3);
	(ft_strcmp(month, "Jan") == 0) ? m = 1 : 0;
	(ft_strcmp(month, "Feb") == 0) ? m = 2 : 0;
	(ft_strcmp(month, "Mar") == 0) ? m = 3 : 0;
	(ft_strcmp(month, "Apr") == 0) ? m = 4 : 0;
	(ft_strcmp(month, "May") == 0) ? m = 5 : 0;
	(ft_strcmp(month, "Jun") == 0) ? m = 6 : 0;
	(ft_strcmp(month, "Jul") == 0) ? m = 7 : 0;
	(ft_strcmp(month, "Aug") == 0) ? m = 8 : 0;
	(ft_strcmp(month, "Sep") == 0) ? m = 9 : 0;
	(ft_strcmp(month, "Oct") == 0) ? m = 10 : 0;
	(ft_strcmp(month, "Nov") == 0) ? m = 11 : 0;
	(ft_strcmp(month, "Dec") == 0) ? m = 12 : 0;
	return (m);
}

int		take_other(t_ls *ls, t_date *date)
{
	char	*day;
	char	*hour;
	char	*minu;
	char	*seco;
	char	*year;

	day = ft_strsub(ls->sort_time, 8, 2);
	hour = ft_strsub(ls->sort_time, 11, 2);
	minu = ft_strsub(ls->sort_time, 14, 2);
	seco = ft_strsub(ls->sort_time, 17, 2);
	year = ft_strsub(ls->sort_time, 20, 4);
	date->day = ft_atoi(day);
	date->hour = ft_atoi(hour);
	date->min = ft_atoi(minu);
	date->sek = ft_atoi(seco);
	date->year = ft_atoi(year);
	return (0);
}