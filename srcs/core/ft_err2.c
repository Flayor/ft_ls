/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 14:37:08 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 19:10:15 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_check_error(t_ft_dir *ft_dir)
{
	t_ft_dir	*tmp;
	DIR			*dir;
	t_stat		st;

	tmp = ft_dir;
	dir = NULL;
	while (tmp)
	{
		lstat(tmp->folder, &st);
		if (S_ISDIR(st.st_mode))
		{
			if (!(dir = opendir(tmp->folder)) && errno)
				ft_folder_error(tmp->folder);
		}
		tmp = tmp->next;
	}
	(dir) ? closedir(dir) : 1;
}

void			ft_error_folder_not_exist(t_ft_dir *ft_dir, t_arg *arg)
{
	t_ft_dir	*tmp;
	DIR			*dir;
	t_stat		st;

	if (!arg)
		arg = ft_init_arg(arg);
	tmp = ft_dir;
	(!arg->rec) ? ft_check_error(tmp) : 0;
	while (tmp)
	{
		lstat(tmp->folder, &st);
		if (!(dir = opendir(tmp->folder)) && errno == ENOENT)
			ft_folder_error(tmp->folder);
		else
			ls_one_file(tmp, arg);
		(dir) ? closedir(dir) : 0;
		tmp = tmp->next;
	}
}
