/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:59:28 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_simple_if(t_file *ft_file, t_arg *arg, int *space)
{
	if (ft_file->tmp_name[0] != '.' && !arg->a)
	{
		(arg->s) ? ft_print_space(ft_file->st.st_blocks, space[0]) : NULL;
		(arg->s) ? ft_putnbr(ft_file->st.st_blocks) : 0;
		(arg->s) ? ft_putstr(" ") : NULL;
		ft_putendl(ft_file->name);
	}
	else if (arg->a)
	{
		(arg->s) ? ft_print_space(ft_file->st.st_blocks, space[0]) : NULL;
		(arg->s) ? ft_putnbr(ft_file->st.st_blocks) : 0;
		(arg->s) ? ft_putstr(" ") : NULL;
		ft_putendl(ft_file->name);
	}
}

static void	ls_long(char **name, t_arg *arg, t_file *ft_file, t_ft_dir *dir)
{
	t_file	*begin;
	int		*space;
	t_stat	st;

	lstat(dir->folder, &st);
	ft_file = ft_init(name, dir, arg, ft_file);
	space = ft_init_space(ft_file);
	if (arg->t)
		merge(ft_file, ft_count_list(ft_file), arg->r);
	if (S_ISLNK(st.st_mode))
		return ;
	if (ft_file->next->next != NULL && ft_file->next->next->tmp_name[1] != '.')
		ft_print_total(ft_file, arg);
	else if (ft_file->next->next != NULL && \
	ft_file->next->next->tmp_name[0] != '.')
		ft_print_total(ft_file, arg);
	while (ft_file)
	{
		begin = ft_file;
		if (ft_file->tmp_name[0] != '.')
			ft_print(ft_file, arg, space);
		ft_file = ft_file->next;
		ft_free_t_file(begin);
	}
	free(space);
}

static void	ls_long_a(char **name, t_arg *arg, t_file *ft_file, t_ft_dir *dir)
{
	t_file	*begin;
	int		*space;

	ft_file = ft_init(name, dir, arg, ft_file);
	(arg->t) ? merge(ft_file, ft_count_list(ft_file), arg->r) : 0;
	space = ft_init_space(ft_file);
	ft_print_total(ft_file, arg);
	while (ft_file)
	{
		begin = ft_file;
		ft_print(ft_file, arg, space);
		ft_file = ft_file->next;
		ft_free_t_file(begin);
	}
	free(space);
}

void		ls_simple(char **name, t_arg *arg, t_file *ft_file, t_ft_dir *dir)
{
	int		*space;
	t_file	*begin;

	ft_file = ft_init(name, dir, arg, ft_file);
	(arg->t) ? merge(ft_file, ft_count_list(ft_file), arg->r) : 0;
	space = ft_init_space(ft_file);
	(arg->s) ? ft_print_total(ft_file, arg) : 0;
	while (ft_file)
	{
		begin = ft_file;
		ls_simple_if(ft_file, arg, space);
		ft_file = ft_file->next;
		ft_free_t_file(begin);
	}
	free(space);
}

void		ft_display_l_a(char **name, t_arg *arg, t_file *file, t_ft_dir *dir)
{
	if (arg->a || arg->f)
		ls_long_a(name, arg, file, dir);
	else
		ls_long(name, arg, file, dir);
}
