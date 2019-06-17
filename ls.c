/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 12:51:21 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/06/17 19:50:08 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls	*take_name_path_type(t_ls *ls, char *av, struct stat buf1)
{
	if (ls->name)
	{
		ls->next = add_list(ls);
		ls = ls->next;
	}
	ls->path = av;
	ls->name = av;
	S_ISLNK(buf1.st_mode) ? ls->type = 10 : 0;
	S_ISDIR(buf1.st_mode) ? ls->type = 4 : 0;
	S_ISREG(buf1.st_mode) ? ls->type = 8 : 0;
	ls->print = (ls->type == 8 || ls->type == 10) ? 1 : 0;
	return (ls);
}

void	ls_custom(char **av, int i, t_flags *flag)
{
	struct stat buf1;
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
			ls = take_name_path_type(ls, av[i], buf1);
		i++;
	}
	all_info(head, flag);
	head = sort_list(head, flag);
	print_ls(head, flag, -1, 0);
	while (head)
	{
		if (head->type == 4)
			ls_dir(head->name, flag, flag->onedir ? 0 : 1);
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
	if (flag->recursive)
		while (ls)
		{
			if (ls->type == DT_DIR && ls->print && ft_strcmp(ls->name, ".") &&
			ft_strcmp(ls->name, ".."))
				ls_dir(ls->path, flag, 1);
			ls = ls->next;
		}
	ls_free(head);
}
