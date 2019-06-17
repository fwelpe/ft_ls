/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thaley <thaley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:07:53 by thaley            #+#    #+#             */
/*   Updated: 2019/06/17 15:03:28 by thaley           ###   ########.fr       */
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
	char			*chmod_access;
	char			*user;
	char			*group;
	char			*other;
	char			*type;
}					t_access;


typedef struct		s_ls
{
	char			*path;
	char			*name;
	char			*m_time;
	char			*month;
	char			*day;
	char			*time;
	long int		unix_time;
	char			*user_name;
	char			*group_name;
	int				type;
	char			*size;
	char			*link;
	int				uid;
	int				gid;
	int				count;
	long long int	block;
	void			*data;
	t_access		access;
	int				print;
	struct s_ls		*next;
}					t_ls;

typedef struct		s_flags
{
	int				l;
	int				a;
	int				r;
	int				R;
	int				t;
	int				outside_flist;
}					t_flags;

int					parse_validate_flags(t_flags *flag, char *arg);
void				ls(char **arg, t_flags *flag, int i);
t_ls				*parse_direct(char *direct);
t_ls				*parse_direct_aux(DIR *dir, char *direct);
int					all_info(t_ls *ls, t_flags *flag);
int					take_rights(t_ls *ls, struct stat buf);
char				*take_chmod(char *access, int num);
void				user_info(t_ls *ls);
t_flags				*create_flag();
t_ls				*add_list(t_ls *head);
t_ls				*sort_list(t_ls *ls, t_flags *flag);
t_ls				*rm_dotf(t_ls *ls);
void				ascii_sort(t_ls **ls, int order);
void				time_sort(t_ls **ls, int order);
int					take_week(char *sort_time);
int					take_month(char *sort_time);
char				*ft_unitoa(unsigned short n);
int					print_ls(t_ls *ls, t_flags *flag, int blocks, char *d);
char				*take_path(char *direct);
void				ls_dir(char *name, t_flags *flag, int name_n_indent);
void				argv_sort(int argc, char **argv, int i, int order);
void				ls_custom(char **av, int i, t_flags *flag);

#endif