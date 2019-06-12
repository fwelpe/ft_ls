/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:14:49 by thaley            #+#    #+#             */
/*   Updated: 2019/06/12 17:03:57 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

int				all_info(t_ls *ls)
{
	struct stat		sb1;
	struct stat		sb2;
	long long int	blocks;

	blocks = 0;
	while (ls)
	{
		lstat(ls->path, &sb1);
		stat(ls->path, &sb2);
		take_rights(ls, sb1);
		ls->block = sb1.st_blocks;
		ls->link = sb1.st_nlink;
		ls->size = sb1.st_size;
		ls->unix_time = sb1.st_mtime;
		ls->m_time = ft_strsub(ctime(&sb1.st_mtime), 4, 12);
		ls->uid = sb2.st_uid;
		ls->gid = sb2.st_gid;
		blocks = blocks + ls->block;
		ls = ls->next;
	}
	return (blocks);
}

int				take_rights(t_ls *ls, struct stat buf)
{
	ls->access.chmod_access = ft_unitoa(buf.st_mode);
	if (S_ISREG(buf.st_mode))
		ls->access.type = "-";
	if (S_ISDIR(buf.st_mode))
		ls->access.type = "d";
	if (S_ISLNK(buf.st_mode))
		ls->access.type = "l";
	ls->access.user = take_chmod(ls->access.chmod_access, 1);
	ls->access.group = take_chmod(ls->access.chmod_access, 2);
	ls->access.other = take_chmod(ls->access.chmod_access, 3);
	ls = ls->next;
	return (0);
}

char			*take_chmod(char *access, int num)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (access[i])
		i++;
	if (num == 1)
		i = i - 3;
	else if (num == 2)
		i = i - 2;
	else
		i = i - 1;
	access[i] == '0' ? new = "---" : 0;
	access[i] == '1' ? new = "--x" : 0;
	access[i] == '2' ? new = "-w-" : 0;
	access[i] == '3' ? new = "-wx" : 0;
	access[i] == '4' ? new = "r--" : 0;
	access[i] == '5' ? new = "r-x" : 0;
	access[i] == '6' ? new = "rw-" : 0;
	access[i] == '7' ? new = "rwx" : 0;
	return (new);
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
