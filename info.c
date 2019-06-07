/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:14:49 by thaley            #+#    #+#             */
/*   Updated: 2019/06/07 17:15:53 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		write_info(char *direct, t_flags *flag)
{
	t_access		*access;
	t_ls			*ls;
	DIR				*dir;
	int				blocks;

	ls = NULL;
	access = creat_access(NULL);
	blocks = 0;
	if ((dir = opendir(direct)) == NULL) //TODO: normal error
	{
		ft_putstr("ft_ls: ");
		ft_putstr(direct);
		ft_putstr(": No such file or directory\n");
		exit(1);
	}
	ls = write_name(dir, direct);
	closedir(dir);
	dir = NULL;
	blocks = sort_string(ls, flag, access);
	// print_ls(ls, flag, access, blocks);
	return (0);
}

t_ls		*write_name(DIR *dir, char *direct)
{
	struct dirent	*file;
	t_ls			*ls;
	t_ls			*head;
	char			*tmp;
	char			*temp;
	size_t			d_len;
	int				i;

	i = 0;
	ls = add_list(NULL);
	d_len = ft_strlen(direct);
	tmp = ft_strnew(d_len + 1);
	while (direct[i] != '\0')
	{
		tmp[i] = direct[i];
		i++;
	}
	tmp[i] = '/';
	tmp[++i] = '\0';
	file = NULL;
	head = ls;
	if ((ft_strcmp(direct, ".")) == 0)
	{	
		while ((file = readdir(dir)) != NULL)
		{
			if (ls->name)
			{
				ls->next = add_list(ls);
				ls = ls->next;
			}
		ls->name = ft_strdup(file->d_name);
		ls->print_name = ft_strdup(file->d_name);
		}
	}
	else
	{
		while ((file = readdir(dir)) != NULL)
		{
			temp = ft_strnew(d_len + file->d_namlen + 1);
			if (ls->name)
			{
				ls->next = add_list(ls);
				ls = ls->next;
			}
			temp = ft_strcpy(temp, tmp);
			temp = ft_strcat(temp, file->d_name);
			ls->name = ft_strdup(temp);
			ls->print_name = ft_strdup(file->d_name);
			free(temp);
		}
		free(tmp);
	}
	ls = head;
	return (ls);
}

int		all_info(t_ls *ls)
{
	struct stat		buf;
	int				blocks;

	blocks = 0;
	while (ls)
	{
		stat(ls->name, &buf);
		ls->acess = ft_unitoa(buf.st_mode);
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

int		take_rights(t_ls *ls, t_access *access)
{
	t_access	*head;

	head = access;
	while (ls)
	{
		if (access->type)
		{
			access->next = creat_access(access);
			access = access->next;
		}
		if (ls->acess[0] == '1')
			access->type = ft_strdup("-");
		else
			access->type = ft_strdup("d");
		access->user = take_chmod(ls->acess, 1);
		access->group = take_chmod(ls->acess, 2);
		access->other = take_chmod(ls->acess, 3);
		ls = ls->next;
	}
	access = head;
	return (0);
}

char	*take_chmod(char *access, int num)
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

void	user_info(t_ls *ls)
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
