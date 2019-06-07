/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:10:27 by thaley            #+#    #+#             */
/*   Updated: 2019/06/06 16:49:21 by thaley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** проверка есть ли флаг, возвращает argv следующий после флага
*/

int		take_flag(t_flag *flag, char **argv)
{
	int		i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (argv[i][0] && argv[i][0] == '-' && argv[i][1] && argv[i][1] != '-')
			flag = write_flag(flag, argv[i]);
		else
			break;
		i++;
	}
	return (i);
}

/*
** Запись флага в структуру || вывод ошибки при неправильном флаге выход из программы
*/

t_flag	*write_flag(t_flag *flag, char *argv)
{
	while (*++argv)
	{
		*argv == 'l' ? flag->l = 1 : flag->illegal++;
		*argv == 'a' ? flag->a = 1 : flag->illegal++;
		*argv == 't' ? flag->t = 1 : flag->illegal++;
		*argv == 'r' ? flag->r = 1 : flag->illegal++;
		*argv == 'R' ? flag->R = 1 : flag->illegal++;
		//TODO: написать нормально сообщение об ошибке
		if (flag->illegal == 5)
		{
			printf("%c -- illegal option.\n", *argv);
			exit(1);
		}
		else
			flag->illegal = 0;
	}
	return (flag);
}

void	*take_info(t_dir_data *data, t_flag *flag)
{
	
}
