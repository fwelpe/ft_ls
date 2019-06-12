/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:14:49 by thaley            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/12 18:37:35 by cdenys-a         ###   ########.fr       */
=======
/*   Updated: 2019/06/12 18:35:06 by thaley           ###   ########.fr       */
>>>>>>> c2eaa9c8d049194af6841f1633c46e5dedc7290a
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			*take_path(char *direct)
{
	char	*new;
	int		check;

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
	ls->month = ft_strsub(ls->m_time, 4, 3);
	ls->day = ft_strsub(ls->m_time, 8, 2);
	ls->time = ft_strsub(ls->m_time, 11, 5);
	ls->year = ft_strsub(ls->m_time, 20, 4);
}

void			write_info(struct stat sb1, struct stat sb2, t_ls *ls)
{
	take_rights(ls, sb1);
	ls->block = sb1.st_blocks;
	ls->link = sb1.st_nlink;
	ls->size = sb1.st_size;
	ls->unix_time = sb1.st_mtime;
	ls->m_time = ft_strdup(ctime(&sb1.st_mtime));
	split_time(ls);
	ls->uid = sb2.st_uid;
	ls->gid = sb2.st_gid;
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
		if (!flag->a && ls->name[0] == '.')
			ls->print = 0;
		else
		{
			write_info(sb1, sb2, ls);
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
