/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_rights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:24:05 by thaley            #+#    #+#             */
/*   Updated: 2019/06/19 16:07:24 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				take_rights(t_ls *ls, struct stat buf)
{
	if (ls && ls->name)
	{
		ls->access.chmod_access = ft_unitoa(buf.st_mode);
		if (S_ISREG(buf.st_mode))
			ls->access.type = "-";
		if (S_ISDIR(buf.st_mode))
			ls->access.type = "d";
		if (S_ISLNK(buf.st_mode))
			ls->access.type = "l";
		ls->access.user = take_chmod(ls->access.chmod_access,
		1, ls->access.type);
		ls->access.group = take_chmod(ls->access.chmod_access,
		2, ls->access.type);
		ls->access.other = take_chmod(ls->access.chmod_access,
		3, ls->access.type);
	}
	return (0);
}

void			file_permission(char *access, int num, char **new, int i)
{
	if (access[i] == '0')
	{
		if (num == 1)
			access[2] == '4' || access[2] == '5' || access[2] == '6'
			|| access[2] == '7' ? (*new)[2] = 'S' : 0;
		if (num == 2)
			access[2] == '2' || access[2] == '3' || access[2] == '6'
			|| access[2] == '7' ? (*new)[2] = 'S' : 0;
		if (num == 3)
			access[2] == '1' || access[2] == '3' || access[2] == '5'
			|| access[2] == '7' ? (*new)[2] = 'T' : 0;
	}
	else if (access[i] != '0')
	{
		if (num == 1)
			(access[2] == '4' || access[2] == '5' ||
			access[2] == '6' || access[2] == '7') ? (*new)[2] = 's' : 0;
		if (num == 2)
			(access[2] == '2' || access[2] == '3' || access[2] == '6'
			|| access[2] == '7') ? (*new)[2] = 's' : 0;
		if (num == 3)
			(access[2] == '1' || access[2] == '3' || access[2] == '5'
			|| access[2] == '7') ? (*new)[2] = 't' : 0;
	}
}

void			dir_permission(char *access, int num, char **new, int i)
{
	if (access[i] != '0')
	{
		if (num == 1)
			access[1] == '4' || access[1] == '5'
			|| access[1] == '6' ? (*new)[2] = 's' : 0;
		if (num == 2)
			access[1] == '2' || access[1] == '3'
			|| access[1] == '6' ? (*new)[2] = 's' : 0;
		if (num == 3)
			access[1] == '1' || access[1] == '3'
			|| access[1] == '5' ? (*new)[2] = 't' : 0;
	}
	else if (access[i] == '0')
	{
		if (num == 1)
			access[1] == '4' || access[1] == '5' || access[1] == '6'
			|| access[1] == '7' ? (*new)[2] = 'S' : 0;
		if (num == 2)
			access[1] == '2' || access[1] == '3' || access[1] == '6'
			|| access[1] == '7' ? (*new)[2] = 'S' : 0;
		if (num == 3)
			access[1] == '1' || access[1] == '3' || access[1] == '5'
			|| access[1] == '7' ? (*new)[2] = 'T' : 0;
	}
}

char			*take_chmod(char *access, int num, char *type)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (access[i])
		i++;
	num == 1 ? i = i - 3 : 0;
	num == 2 ? i = i - 2 : 0;
	num == 3 ? i = i - 1 : 0;
	access[i] == '0' ? new = ft_strdup("---") : 0;
	access[i] == '1' ? new = ft_strdup("--x") : 0;
	access[i] == '2' ? new = ft_strdup("-w-") : 0;
	access[i] == '3' ? new = ft_strdup("-wx") : 0;
	access[i] == '4' ? new = ft_strdup("r--") : 0;
	access[i] == '5' ? new = ft_strdup("r-x") : 0;
	access[i] == '6' ? new = ft_strdup("rw-") : 0;
	access[i] == '7' ? new = ft_strdup("rwx") : 0;
	if (!ft_strcmp(type, "-"))
		file_permission(access, num, &new, i);
	if (!ft_strcmp(type, "d"))
		dir_permission(access, num, &new, i);
	return (new);
}
