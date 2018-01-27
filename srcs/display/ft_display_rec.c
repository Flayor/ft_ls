/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_rec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 16:15:31 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ls_check_rec(char *path, t_arg *arg, int i)
{
	DIR			*dir;
	DIR			*dir2;
	DIR			*countdir;
	char		**name;

	dir2 = opendir(path);
	countdir = opendir(path);
	name = ft_prepare_display(dir2, countdir, arg);
	(countdir) ? closedir(countdir) : 0;
	(dir2) ? closedir(dir2) : 0;
	if ((dir = opendir(path)))
	{
		if (i > 1)
		{
			ft_putchar('\n');
			if (path[0] == '/' && path[1] == '/')
				ft_putstr(path + 1);
			else
				ft_putstr(path);
			ft_putendl(":");
		}
		closedir(dir);
	}
	return (name);
}

void			ft_rec(t_arg *arg, t_ft_dir *ft_dir, t_file *ft_file)
{
	t_ft_dir	*tmp;
	DIR			*dir;

	tmp = ft_dir;
	while (tmp)
	{
		(!(dir = opendir(tmp->folder)) && errno == EACCES) ? \
		ft_err_denied(tmp->folder) : 0;
		tmp = tmp->next;
		(dir) ? closedir(dir) : 1;
	}
	while (ft_dir)
	{
		ls_rec(ft_dir->folder, ft_dir, arg, ft_file);
		ft_dir = ft_dir->next;
	}
	ft_free_t_dir(ft_dir);
}
