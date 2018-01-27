/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 14:53:45 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 20:54:06 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_one_file_link(t_arg *arg, t_dir *file)
{
	if (!arg->a)
	{
		if (file->d_name[0] != '.')
			ft_putendl(file->d_name);
	}
	else
		ft_putendl(file->d_name);
}

static void		ls_one_file2(t_arg *arg, t_ft_dir *dir, t_stat st, int *space)
{
	if (arg->l || arg->g || arg->o)
		ft_print_one(st, dir->folder, arg, space);
	else
	{
		(arg->s) ? ft_print_space(st.st_blocks, space[0]) : NULL;
		(arg->s) ? ft_putnbr(st.st_blocks) : NULL;
		(arg->s) ? ft_putstr(" ") : NULL;
		ft_putendl(dir->folder);
	}
}

void			ls_one_file(t_ft_dir *ft_dir, t_arg *arg)
{
	t_stat		st;
	DIR			*dir;
	t_dir		*file;
	int			*space;

	dir = opendir(ft_dir->folder);
	(dir) ? closedir(dir) : 1;
	lstat(ft_dir->folder, &st);
	if (S_ISDIR(st.st_mode) && !(st.st_mode & S_IXUSR && st.st_mode & S_IRUSR))
		return ;
	if (S_ISLNK(st.st_mode) && !arg->l)
	{
		if (!(dir = opendir(ft_dir->folder)))
			return ;
		while ((file = readdir(dir)))
			ls_one_file_link(arg, file);
		closedir(dir);
		return ;
	}
	else if (!S_ISDIR(st.st_mode))
	{
		space = ft_init_space_one(st);
		ls_one_file2(arg, ft_dir, st, space);
		free(space);
	}
}

int				ft_count_block(t_file *ft_file, t_arg *arg)
{
	int			blocks;

	blocks = 0;
	if (!arg->a && !arg->f)
	{
		while (ft_file)
		{
			if (ft_file->tmp_name[0] != '.')
				blocks += ft_file->st.st_blocks;
			ft_file = ft_file->next;
		}
	}
	else
	{
		while (ft_file)
		{
			blocks += ft_file->st.st_blocks;
			ft_file = ft_file->next;
		}
	}
	return (blocks);
}
