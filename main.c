/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:04:23 by thaley            #+#    #+#             */
/*   Updated: 2019/06/06 16:24:30 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	t_dir_data	*dir_data;
	t_dir_data	*head;
	t_flag		*flag;
	int			i;

	dir_data = crt_dir(NULL);
	flag = (t_flag *)malloc(sizeof(t_flag));

	/*
	** обнуляю все компоненты в структурах
	*/

	ft_bzero(flag, (sizeof(t_flag)));
	head = dir_data;
	// ft_bzero(dir_data->info, sizeof(t_info));

	//TODO: проверить в школе как работает ls с аргументами "--", "---", "--a", "---a"
	
	/*
	** поиск флага, вывод ошибки при неправильном флаге
	*/

	//TODO: убедиться что если пкогосле флага нет аргументов argv возвращает null
	i = take_flag(flag, argv);
	if (argv[i] == NULL)
		dir_data->info->dir = ft_strdup(".");
	else
		flag->dir_count = argc - i;
	while (argv[i])\
	{
		dir_data->info->dir = ft_strdup(argv[i]);
		i++;
		if (argv[i])
		{
			dir_data->next = crt_dir(dir_data);
			dir_data = dir_data->next;
		}
	}
	take_info(head, flag);
	return (0);
}
