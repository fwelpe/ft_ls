/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:14:49 by thaley            #+#    #+#             */
/*   Updated: 2019/06/19 16:15:43 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*take_path(char *direct)
{
	char	*new;

	if (direct[(ft_strlen(direct)) - 1] == '/')
		new = ft_strdup(direct);
	else
	{
		new = ft_strnew(ft_strlen(direct) + 1);
		new = ft_strcpy(new, direct);
		new = ft_strcat(new, "/");
	}
	return (new);
}

void			split_time(t_ls *ls)
{
	time_t		older_half_y;
	time_t		newer_half_y;

	older_half_y = time(NULL);
	newer_half_y = time(NULL) + 1;
	older_half_y = older_half_y - 18144000;
	ls->month = ft_strsub(ls->m_time, 4, 3);
	ls->day = ft_strsub(ls->m_time, 8, 2);
	if (ls->unix_time >= newer_half_y && ft_strlen(ls->m_time) > 25)
		ls->time = ft_strsub(ls->m_time, (ft_strlen(ls->m_time) - 7), 6);
	else if (ls->unix_time <= older_half_y || ls->unix_time >= newer_half_y)
		ls->time = ft_strsub(ls->m_time, 19, 5);
	else
		ls->time = ft_strsub(ls->m_time, 11, 5);
}

void			write_info(struct stat sb1, t_ls *ls)
{
	take_rights(ls, sb1);
	ls->block = sb1.st_blocks;
	ls->link = ft_itoa(sb1.st_nlink);
	ls->size = ft_itoa(sb1.st_size);
	ls->unix_time = sb1.st_mtime;
	ls->m_time = ft_strdup(ctime(&sb1.st_mtime));
	split_time(ls);
	ls->uid = sb1.st_uid;
	ls->gid = sb1.st_gid;
}

int				all_info(t_ls *ls, t_flags *flag)
{
	struct stat		sb1;
	struct stat		sb2;
	long long int	blocks;

	blocks = 0;
	while (ls)
	{
		lstat(ls->path, &sb1);
		stat(ls->path, &sb2);
		if (!flag->a && ls->name && ls->name[0] == '.')
			ls->print = 0;
		else
		{
			write_info(sb1, ls);
			blocks = blocks + ls->block;
		}
		ls = ls->next;
	}
	return (blocks);
}

void			user_info(t_ls *ls)
{
	struct passwd	*userinfo;
	struct group	*grinfo;

	while (ls)
	{
		if ((userinfo = getpwuid(ls->uid)) == NULL)
		{
			ls = ls->next;
			continue;
		}
		if ((grinfo = getgrgid(ls->gid)) == NULL)
		{
			ls = ls->next;
			continue;
		}
		ls->user_name = ft_strdup(userinfo->pw_name);
		ls->group_name = ft_strdup(grinfo->gr_name);
		ls = ls->next;
	}
}
