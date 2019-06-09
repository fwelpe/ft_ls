/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:14:49 by thaley            #+#    #+#             */
/*   Updated: 2019/06/09 16:45:47 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				write_info(char *direct, t_flags *flag)
{
	t_ls			*ls;
	DIR				*dir;
	int				blocks;

	ls = NULL;
	blocks = 0;
	if ((dir = opendir(direct)) == NULL)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(direct);
		ft_putstr(": No such file or directory\n");
		exit(1);
	}
	ls = write_name(dir, direct);
	closedir(dir);
	dir = NULL;
	blocks = sort_string(ls, flag);
	return (0);
}

t_ls			*write_name(DIR *dir, char *direct)
{
	struct dirent	*file;
	t_ls			*ls;
	t_ls			*head;
	char			*dir_path;
	size_t			d_len;

	ls = add_list(NULL);
	dir_path = ft_strnew((ft_strlen(direct)) + 1);
	dir_path = ft_strcpy(dir_path, direct);
	dir_path = ft_strcat(dir_path, "/");
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
	}
	free(dir_path);
	ls = head;
	return (ls);
}

int				all_info(t_ls *ls)
{
	struct stat		buf;
	int				blocks;

	blocks = 0;
	while (ls)
	{
		lstat(ls->name, &buf);
		take_rights(ls, buf);
		ls->block = buf.st_blocks;
		ls->link = buf.st_nlink;
		ls->size = buf.st_size;
		ls->m_time = ft_strsub(ctime(&buf.st_mtime), 4, 12);
		ls->uid = buf.st_uid;
		blocks = blocks + ls->block;
		ls = ls->next;
	}
	return (blocks);
}

int				take_rights(t_ls *ls, struct stat buf)
{
	ls->access.chmod_access = ft_unitoa(buf.st_mode);
	if (S_ISREG(buf.st_mode))
		ls->access.type = ft_strdup("-");
	if (S_ISDIR(buf.st_mode))
		ls->access.type = ft_strdup("d");
	if (S_ISLNK(buf.st_mode))
		ls->access.type = ft_strdup("l");
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
	access[i] == '0' ? new = ft_strdup("---") : 0;
	access[i] == '1' ? new = ft_strdup("--x") : 0;
	access[i] == '2' ? new = ft_strdup("-w-") : 0;
	access[i] == '3' ? new = ft_strdup("-wx") : 0;
	access[i] == '4' ? new = ft_strdup("r--") : 0;
	access[i] == '5' ? new = ft_strdup("r-x") : 0;
	access[i] == '6' ? new = ft_strdup("rw-") : 0;
	access[i] == '7' ? new = ft_strdup("rwx") : 0;
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
		if ((grinfo = getgrgid(userinfo->pw_gid)) == NULL)
		{
			 ls = ls->next;
			 continue;
		}
		ls->user_name = ft_strdup(userinfo->pw_name);
		ls->group_name = ft_strdup(grinfo->gr_name);
		ls = ls->next;
	}
}
