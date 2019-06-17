/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 12:51:21 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/06/17 17:51:42 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_custom(char **av, int i, t_flags *flag)
{
	struct stat buf1;
	struct stat buf2;
	t_ls		*ls;
	t_ls		*head;

	ls = add_list(NULL);
	head = ls;
	while (av[i])
	{
		if (stat(av[i], &buf1) == -1)
		{
			ft_putstr_fd("ft_ls: ", 2);
			perror(av[i]);
		}
		else
		{
			if (ls->name)
			{
				ls->next = add_list(ls);
				ls = ls->next;
			}
			lstat(av[i], &buf2);
			ls->path = av[i];
			ls->name = av[i];
			S_ISLNK(buf1.st_mode) ? ls->type = 10 : 0;
			S_ISDIR(buf1.st_mode) ? ls->type = 4 : 0;
			S_ISREG(buf1.st_mode) ? ls->type = 8 : 0;
			ls->print = (ls->type == 8 || ls->type == 10) ? 1 : 0;
		}
		i++;
	}
	all_info(head, flag);
	head = sort_list(head, flag);
	print_ls(head, flag, -1, 0);
	while(head)
	{
		if (head->type == 4)
			ls_dir(head->name, flag, 1);
		head = head->next;
	}
}

void	ls_dir(char *name, t_flags *flag, int name_n_indent)
{
	t_ls		*ls;
	t_ls		*head;
	int			blocks;

	ls = parse_direct(name);
	blocks = all_info(ls, flag);
	ls = sort_list(ls, flag);
	print_ls(ls, flag, blocks, name_n_indent ? name : 0);
	head = ls;
	if (flag->R)
		while (ls)
		{
			if (ls->type == DT_DIR && ls->print && ft_strcmp(ls->name, ".") &&
			ft_strcmp(ls->name, ".."))
				ls_dir(ls->path, flag, 1);
			ls = ls->next;
		}
	ls_free(head);
}
