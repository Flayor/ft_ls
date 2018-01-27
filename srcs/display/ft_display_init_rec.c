/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_init_rec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 15:05:17 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 22:48:38 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include "ft_ls.h"

static void		ls_rec_print_folder(t_arg *arg, t_dir *tmp)
{
	ft_putchar('\n');
	(arg->color) ? ft_putstr(CYAN) : NULL;
	ft_putstr(tmp->d_name);
	ft_putendl(":");
	(arg->color) ? ft_putstr(RESET) : NULL;
}

static t_stat	ls_rec_join(char *path, char *tmp_path, t_stat st, t_dir *tmp)
{
	if (ft_strcmp(path, "/") != 0)
	{
		tmp_path = ft_strjoin(path, "/");
		tmp_path = ft_strjoinfree(tmp_path, tmp->d_name, 1);
		lstat(tmp_path, &st);
		free(tmp_path);
	}
	else
	{
		tmp_path = ft_strjoin(path, tmp->d_name);
		lstat(tmp_path, &st);
		free(tmp_path);
	}
	return (st);
}

static t_bool	ft_is_open(t_dir *tmp, t_stat st)
{
	if ((tmp->d_type == 4 && tmp->d_name[0] != '.') \
			&& st.st_mode & S_IXUSR && st.st_mode & S_IRUSR)
		return (1);
	else if (tmp->d_name[0] != '.' && !(st.st_mode & S_IRUSR))
		return (3);
	else if (tmp->d_type == 4 && tmp->d_name[0] != '.' \
		&& !(st.st_mode & S_IXUSR && st.st_mode & S_IRUSR))
		return (2);
	return (0);
}

void			ls_rec(char *path, t_ft_dir *f_dir, t_arg *arg, t_file *ft_file)
{
	DIR			*dir;
	char		*tmp_path;
	t_dir		*tmp;
	t_stat		st;

	dir = opendir(path);
	if (!dir)
		return ;
	ls_rec_init(path, arg, ft_file);
	while ((tmp = readdir(dir)))
	{
		st = ls_rec_join(path, tmp_path, st, tmp);
		if (ft_is_open(tmp, st) == 1)
		{
			tmp_path = ft_strjoin(path, "/");
			tmp_path = ft_strjoinfree(tmp_path, tmp->d_name, 1);
			ls_rec(tmp_path, f_dir, arg, ft_file);
			free(tmp_path);
		}
		(ft_is_open(tmp, st) == 2) ? ls_rec_print_folder(arg, tmp) : 0;
		(ft_is_open(tmp, st) == 3) ? ft_err_denied_no_errno(tmp->d_name) : 0;
	}
	closedir(dir);
}
