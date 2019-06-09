/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:07:53 by thaley            #+#    #+#             */
/*   Updated: 2019/06/09 13:58:32 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <unistd.h> //write | readlink
# include <dirent.h> //opendir | readdir | closedir
# include <sys/types.h> // structs
# include <sys/dir.h> //struct dirent
# include <sys/stat.h> //stat | lstat
# include <grp.h> //getgrgid
# include <uuid/uuid.h> //getgrgid | getpwuid
# include <sys/xattr.h> //listxattr | getxattr
# include <time.h> //time | ctime
# include <stdlib.h> //malloc | free | exit
# include <stdio.h> //perror | strerror
# include <pwd.h> 
typedef struct 		s_access
{
	char			*user;
	char			*group;
	char			*other;
	char			*type;
	struct s_access	*next;
}					t_access;


typedef struct		s_ls
{
	char			*path;
	char			*name;
	char			*m_time;
	long int		unix_time;
	char			*user_name;
	char			*group_name;
	char			*acess;
	int				size;
	int				link;
	int				uid;
	int				count;
	long long int	block;
	void			*data;
	t_access		access;
	struct s_ls		*next;
}					t_ls;

typedef struct		s_flags
{
	int				l;
	int				a;
	int				r;
	int				R;
	int				t;
}					t_flags;

int					take_dir(char *argv, t_flags *flag);
int					take_flags(char *argv, t_flags *flag);
int					find_validate_flags(t_flags *flag, char *arg);

int					write_info(char *direct, t_flags *flag);
t_ls				*write_name(DIR *dir, char *direct);
int					all_info(t_ls *ls);
int					take_rights(t_ls *ls, t_access *access);
char				*take_chmod(char *access, int num);
void				user_info(t_ls *ls);

t_flags				*create_flag();
t_ls				*add_list(t_ls *head);
t_access			*creat_access(t_access *head);

int					sort_string(t_ls *ls, t_flags *flag, t_access *access);
t_ls				*rm_dotf(t_ls *ls);
int					ascii_sort(t_ls *ls, int order);
int					time_sort(t_ls *ls, int order);

int					take_week(char *sort_time);
int					take_month(char *sort_time);

char				*ft_unitoa(unsigned short n);

int					print_ls(t_ls *ls, t_flags *flag, t_access *access, int blocks);

#endif