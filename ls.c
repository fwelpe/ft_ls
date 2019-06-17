/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 12:51:21 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/06/17 16:39:25 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		calc_i_start(char **av)
{
	int	i;

	i = 1;
	while (av[i][0] == '-')
		i++;
	return (i);
}

void	nofile_err(char *filename)
{
	ft_putstr("ft_ls: ");
	ft_putstr(filename);
	ft_putendl(": No such file or directory");
}

void	report_nonexist(t_ls *ls, char **av)
{
	int		i;
	t_ls	*ls_head;
	int		report;

	i = calc_i_start(av);
	ls_head = ls;
	while (av[i])
	{
		ls = ls_head;
		report = 1;
		while (ls)
		{
			if (!ft_strcmp(ls->name, av[i]) || av[i][0] == '/')
				report = 0;
			ls = ls->next;
		}
		if (report)
			nofile_err(av[i]);
		i++;
	}
}

void	ls_argv_filter(t_ls **ls, char **av)
{
	t_ls	*ls_iter;
	int		i_start;
	int		i;

	i_start = calc_i_start(av);
	ascii_sort(ls, 1);
	ls_iter = *ls;
	while (ls_iter)
	{
		ls_iter->print = 0;
		i = i_start;
		while (av[i])
		{
			if (!ft_strcmp(ls_iter->name, av[i]))
				ls_iter->print = 1;
			i++;
		}
		ls_iter = ls_iter->next;
	}
}

void	print_customdirs(char **av, t_flags *flag)
{
	int	i;

	i = calc_i_start(av);
	while (av[i])
	{
		if (av[i][0] == '/')
			ls_dir(av[i], flag, 1);
		i++;
	}
}

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

void	ls_free_l(t_ls *l)
{
	free(l->path);
	free(l->name);
	free(l->m_time);
	free(l->month);
	free(l->day);
	free(l->time);
	free(l->user_name);
	free(l->group_name);
	free(l->size);
	free(l->link);
	free(l->data);
	if (l->access.chmod_access)
		free(l->access.chmod_access);
	free(l);
}

void	ls_free(t_ls *l)
{
	t_ls	*tmp;
	
	while(l)
	{
		tmp = l->next;
		ls_free_l(l);
		l = tmp;
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
	/* if (av)
		print_customdirs(av, flag); */
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
