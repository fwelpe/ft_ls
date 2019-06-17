/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 17:17:03 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/06/17 19:30:26 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

	while (l)
	{
		tmp = l->next;
		ls_free_l(l);
		l = tmp;
	}
}
