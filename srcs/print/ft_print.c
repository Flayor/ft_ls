/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 09:34:32 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:15 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_right(t_file *ft_file, t_arg *arg, int *space)
{
	(arg->s) ? ft_print_space(ft_file->st.st_blocks, space[0]) : NULL;
	(arg->s) ? ft_putnbr(ft_file->st.st_blocks) : NULL;
	(arg->s) ? ft_putstr(" ") : NULL;
	ft_ls_read_right(ft_file->st.st_mode, ft_file->acl);
	ft_print_space(ft_file->st.st_nlink, space[1]);
	ft_putnbr(ft_file->st.st_nlink);
	ft_putchar(' ');
}

static void		ft_finish_print(t_file *ft_file, int *space, t_arg *arg)
{
	char		*date;

	if (arg->u)
		date = ft_set_date(ft_file->st.st_atime, ft_file->date_access);
	else if (arg->big_u && !arg->u)
		date = ft_set_date(ft_file->st.st_ctime, ft_file->date_create);
	else
		date = ft_set_date(ft_file->st.st_mtime, ft_file->date_modif);
	ft_putstr("  ");
	ft_print_space(ft_file->st.st_size, space[2]);
	(major(ft_file->st.st_rdev) == 0) ? ft_putnbr(ft_file->st.st_size) : \
			ft_print_major(ft_file);
	ft_putchar(' ');
	ft_putstr(date);
	ft_putchar(' ');
	(ft_file->link) ? ft_putstr(ft_file->name) : ft_putendl(ft_file->name);
	ft_putendl(ft_file->link);
}

void			ft_print(t_file *ft_file, t_arg *arg, int *space)
{
	t_paswd		*pw;
	t_group		*gr;
	char		*tmpgr;
	char		*tmppw;

	tmpgr = ft_itoa(ft_file->st.st_gid);
	tmppw = ft_itoa(ft_file->st.st_uid);
	ft_print_right(ft_file, arg, space);
	if ((pw = getpwuid(ft_file->st.st_uid)))
		(!arg->g) ? ft_print_name(pw->pw_name, space[3]) : NULL;
	else
		(!arg->g) ? ft_print_name(tmppw, space[3]) : NULL;
	ft_putstr("  ");
	if ((gr = getgrgid(ft_file->st.st_gid)))
		(!arg->o) ? ft_print_name(gr->gr_name, space[4]) : NULL;
	else
		(!arg->o) ? ft_print_name(tmpgr, space[4]) : NULL;
	ft_finish_print(ft_file, space, arg);
	free(tmpgr);
	free(tmppw);
}
