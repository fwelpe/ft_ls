/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:35:21 by thaley            #+#    #+#             */
/*   Updated: 2019/06/06 15:29:28 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*crt_info(void)
{
	t_info	*new;

	if (!(new = (t_info *)malloc(sizeof(t_info))))
		exit(1);
	ft_bzero(new, sizeof(t_info));
	return (new);
}

t_dir_data	*crt_dir(t_dir_data *head)
{
	t_dir_data	*new;
	t_dir_data	*tmp;

	tmp = head;
	new = (t_dir_data *)malloc(sizeof(t_dir_data));
	ft_bzero(new, sizeof(t_dir_data));
	new->info = crt_info();
	if (tmp == NULL)
	{
		head = new;
		return (new);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}
