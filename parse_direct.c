/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_direct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:25:17 by thaley            #+#    #+#             */
/*   Updated: 2019/06/13 15:12:41 by thaley           ###   ########.fr       */
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
		return (0);			//TODO: вывод ошибки
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
