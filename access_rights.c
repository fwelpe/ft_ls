/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_rights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:24:05 by thaley            #+#    #+#             */
/*   Updated: 2019/06/12 17:24:38 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
