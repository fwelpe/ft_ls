/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:14:49 by thaley            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/12 17:56:50 by thaley           ###   ########.fr       */
=======
/*   Updated: 2019/06/12 17:03:57 by cdenys-a         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

<<<<<<< HEAD
=======
t_ls			*parse_direct(char *direct, t_flags *flag)
{
	t_ls			*ls;
	DIR				*dir;

	ls = NULL;
	if (!(dir = opendir(direct)))
	{
		return (0);
	}
	ls = parse_direct_aux(dir, direct);
	closedir(dir);
	dir = NULL;
	return (ls);
}

t_ls			*parse_direct_aux(DIR *dir, char *direct)
{
	struct dirent	*file;
	t_ls			*ls;
	t_ls			*head;
	char			*dir_path;
	size_t			d_len;

	ls = add_list(NULL);
	dir_path = take_path(direct);
	file = NULL;
	head = ls;
	while ((file = readdir(dir)) != NULL)
	{
		if (ls->name)
		{
			ls->next = add_list(ls);
			ls = ls->next;
		}
		ls->path = ft_strnew(ft_strlen(direct) + file->d_namlen + 1);
		ls->path = ft_strcpy(ls->path, dir_path);
		ls->path = ft_strcat(ls->path, file->d_name);
		ls->name = ft_strdup(file->d_name);
		DT_REG == file->d_type ? ls->type = 8 : 0;
		DT_DIR == file->d_type ? ls->type = 4 : 0;
		DT_LNK == file->d_type ? ls->type = 10 : 0;
		ls->print = 1;
	}
	free(dir_path);
	ls = head;
	return (ls);
}

>>>>>>> master
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
