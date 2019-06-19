/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 14:07:53 by thaley            #+#    #+#             */
/*   Updated: 2019/06/19 17:43:57 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <pwd.h>

typedef struct		s_access
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
	int				recursive;
	int				t;
	int				outside_flist;
	int				indt_custom;
	int				onedir;
	int				one_opt;
	int				first;
}					t_flags;

int					parse_validate_flags(t_flags *flag, char **av);
void				ls(char **arg, t_flags *flag, int i);
t_ls				*parse_direct(char *direct);
t_ls				*parse_direct_aux(DIR *dir, char *direct,
					struct dirent *file, t_ls *ls);
int					all_info(t_ls *ls, t_flags *flag);
int					take_rights(t_ls *ls, struct stat buf);
char				*take_chmod(char *access, int num, char *type);
void				user_info(t_ls *ls);
t_flags				create_flag();
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
void				ls_free_l(t_ls *l);
void				ls_free(t_ls *l);
int					is_onlyonedir(int ac, char **av, int i);
void				illegal_opt_err(char opt);
void				permission_denied_err(char *name);
int					opening_check(char *name);
void				perroring(char *msg);
void				print_ls_l(t_ls *ls, int blocks, t_flags *f);

#endif
