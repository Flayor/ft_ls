/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_rec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 15:01:49 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 21:49:14 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_rec_long_a(t_file *ft_file, t_arg *arg, int *space)
{
	t_file		*begin;

	ft_print_total(ft_file, arg);
	while (ft_file)
	{
		begin = ft_file;
		ft_print(ft_file, arg, space);
		ft_file = ft_file->next;
		ft_free_t_file(begin);
	}
}

static void		ls_rec_long(t_file *ft_file, t_arg *arg, int *space)
{
	t_file		*begin;

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
}

static void		ls_rec_l_a(t_file *ft_file, t_arg *arg, int *space)
{
	if (arg->a || arg->f)
		ls_rec_long_a(ft_file, arg, space);
	else
		ls_rec_long(ft_file, arg, space);
}

static void		ls_rec_simple(t_file *ft_file, t_arg *arg, int *space)
{
	t_file		*begin;

	(arg->s) ? ft_print_total(ft_file, arg) : 0;
	while (ft_file)
	{
		begin = ft_file;
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
		ft_file = ft_file->next;
		ft_free_t_file(begin);
	}
}

void			ls_rec_init(char *path, t_arg *arg, t_file *ft_file)
{
	char		**name;
	int			*space;
	static int	i;

	name = ls_check_rec(path, arg, i);
	ft_file = ft_init_rec(name, path, arg, ft_file);
	(arg->t) ? merge(ft_file, ft_count_list(ft_file), arg->r) : 0;
	space = ft_init_space(ft_file);
	if ((arg->l && !arg->one) || arg->o)
		ls_rec_l_a(ft_file, arg, space);
	else
		ls_rec_simple(ft_file, arg, space);
	i++;
	free(name);
	free(space);
}
