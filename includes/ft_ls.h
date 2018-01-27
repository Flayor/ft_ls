/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 07:20:44 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 23:29:57 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_LS_H
# define __FT_LS_H
# include <sys/types.h>
# include <stdio.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <errno.h>
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[1;36m"
# define BGCYAN		"\x1b[30;46m"
# define PINK		"\x1b[35m"
# define YELLOW		"\x1b[33m"
# define BGYELLOW	"\x1b[30;43m"
# define BGRED		"\x1b[30;41m"
# define RESET		"\x1b[0m"
# define TRUE 1
# define FALSE 0

typedef struct stat	t_stat;
typedef struct passwd	t_paswd;
typedef struct group	t_group;
typedef struct dirent	t_dir;
typedef int				t_bool;

typedef struct			s_ft_ls
{
	char				*arg;
	struct s_ft_ls		*next;
}						t_ft_ls;
typedef struct			s_ft_dir
{
	char				*folder;
	struct s_ft_dir		*next;
}						t_ft_dir;
typedef struct			s_file
{
	char				*name;
	char				*link;
	char				*tmp_name;
	t_stat				st;
	char				*date_create;
	char				*date_access;
	char				*date_modif;
	char				acl;
	struct s_file		*next;
}						t_file;
typedef struct			s_arg
{
	t_bool				l;
	t_bool				rec;
	t_bool				r;
	t_bool				a;
	t_bool				one;
	t_bool				t;
	t_bool				g;
	t_bool				f;
	t_bool				s;
	t_bool				o;
	t_bool				u;
	t_bool				big_u;
	t_bool				color;
	t_bool				error;
	t_bool				ignore;
}						t_arg;
void					ls_core(t_ft_dir *ft_dir, t_arg *arg, size_t len);
t_arg					*ft_init_arg(t_arg *ft_arg);
t_arg					*ft_set_arg(t_arg *ft_arg);
char					*ft_full_path(char *name, t_ft_dir *dir);
void					ft_error(char *arg);
void					ft_folder_error_exit(char *folder);
void					ft_folder_error(char *folder);
void					ft_err_denied(char *folder);
void					ft_err_denied_no_errno(char *folder);
void					ft_error_folder_not_exist(t_ft_dir *ft_dir, t_arg *arg);
void					ft_free_t_file(t_file *ft_file);
void					ft_free_t_dir(t_ft_dir *ft_dir);
void					ft_sort(char **str);
void					ft_rsort(char **str);
int						ft_count_list(t_file *ft_file);
t_file					*merge_sort(t_file *ft_file, int psize,\
							t_file *new, int qsize);
t_file					*merge(t_file *ft_file, int size, int sort);
void					ls_simple(char **name, t_arg *arg,\
							t_file *ft_file, t_ft_dir *ft_dir);
void					ft_display_l_a(char **name, t_arg *arg, \
							t_file *ft_file, t_ft_dir *ft_dir);
char					**ls_check_rec(char *path, t_arg *arg, int i);
void					ft_rec(t_arg *arg, t_ft_dir *ft_dir, t_file *ft_file);
void					ls_rec_init(char *path, t_arg *arg, t_file *ft_file);
void					ls_one_file(t_ft_dir *ft_dir, t_arg *arg);
int						ft_count_block(t_file *ft_file, t_arg *arg);
char					**ft_prepare_display(DIR *dir, \
							DIR *countdir, t_arg *arg);
t_file					*ft_init(char **name, t_ft_dir *dir,\
							t_arg *arg, t_file *ft_file);
t_file					*ft_init_rec(char **name, char *path, \
							t_arg *arg, t_file *ft_file);
void					ft_display(DIR *dir, DIR *countdir, \
							t_arg *arg, t_ft_dir *ft_dir);
char					*ft_set_date(long timestamp, char *date);
void					ls_rec(char *path, t_ft_dir *ft_dir, \
							t_arg *arg, t_file *ft_file);
t_file					*ft_init_list(t_file *lst, char *str, \
							t_ft_dir *ft_dir, t_arg *arg);
char					ft_get_acl(char *name);
char					*print_link(char *path);
char					*ft_color_name(char *name, t_stat st);
t_file					*ft_init_list_rec(t_file *lst, char *name, char \
							*path, t_arg *arg);
char					*ft_full_path_rec(char *path, char *name);
void					ft_ls_read_right(mode_t mode, char acl);
t_arg					*ft_arg(char **argv);
t_ft_dir				*ft_folder(int argc, char **argv, t_arg *ft_arg, \
							t_ft_dir *ft_folder);
t_arg					*ft_ls_add_arg(t_arg *ft_arg, char *arg);
size_t					ft_count_folder(t_ft_dir *ft_dir);
void					ft_print(t_file *ft_file, t_arg *arg, int *space);
void					ft_print_total(t_file *ft_file, t_arg *arg);
void					ft_print_major(t_file *ft_file);
void					ft_print_major_one(int maj, int min);
void					ft_print_name(char *name, int space);
void					ft_print_one(t_stat st, char *fld, t_arg *arg, int *sp);
char					*ft_color(mode_t mode);
int						*ft_init_space(t_file *ft_file);
int						*ft_init_space_one(t_stat st);
void					ft_print_space(int i, int j);
void					ft_write_space(int space);
#endif
