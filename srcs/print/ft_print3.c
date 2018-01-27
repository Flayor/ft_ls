/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 11:58:02 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_finish_print_one(t_stat st, int *sp, t_arg *arg, char *fld)
{
	char		*date;

	if (arg->u)
		date = ft_set_date(st.st_atime, ft_strsub(ctime(&st.st_atime), 4, 12));
	else if (arg->big_u && !arg->u)
		date = ft_set_date(st.st_ctime, ft_strsub(ctime(&st.st_ctime), 4, 12));
	else
		date = ft_set_date(st.st_mtime, ft_strsub(ctime(&st.st_mtime), 4, 12));
	ft_putstr("  ");
	ft_print_space(st.st_size, sp[2]);
	(major(st.st_rdev) == 0) ? ft_putnbr(st.st_size) : \
			ft_print_major_one(major(st.st_rdev), minor(st.st_rdev));
	ft_putchar(' ');
	ft_putstr(date);
	ft_putchar(' ');
	(S_ISLNK(st.st_mode)) ? ft_putstr(fld) : ft_putendl(fld);
	(S_ISLNK(st.st_mode)) ? ft_putendl(print_link(fld)) : ft_putchar('\0');
	free(date);
}

static void		ft_print_right_one(t_arg *arg, t_stat st, int *sp, char *name)
{
	(arg->s) ? ft_print_space(st.st_blocks, sp[0]) : NULL;
	(arg->s) ? ft_putnbr(st.st_blocks) : NULL;
	(arg->s) ? ft_putstr(" ") : NULL;
	ft_ls_read_right(st.st_mode, ft_get_acl(name));
	ft_print_space(st.st_nlink, sp[1]);
	ft_putnbr(st.st_nlink);
	ft_putchar(' ');
}

void			ft_print_one(t_stat st, char *folder, t_arg *arg, int *space)
{
	t_paswd		*pw;
	t_group		*gr;
	char		*tmpgr;
	char		*tmppw;

	tmpgr = ft_itoa(st.st_gid);
	tmppw = ft_itoa(st.st_uid);
	ft_print_right_one(arg, st, space, folder);
	if ((pw = getpwuid(st.st_uid)))
		(!arg->g) ? ft_print_name(pw->pw_name, space[3]) : NULL;
	else
		(!arg->g) ? ft_print_name(tmppw, space[3]) : NULL;
	ft_putstr("  ");
	if ((gr = getgrgid(st.st_gid)))
		(!arg->o) ? ft_print_name(gr->gr_name, space[4]) : NULL;
	else
		(!arg->o) ? ft_print_name(tmpgr, space[4]) : NULL;
	free(tmpgr);
	free(tmppw);
	ft_finish_print_one(st, space, arg, folder);
}

void			ft_print_name(char *name, int space)
{
	int			i;

	i = (int)ft_strlen(name);
	ft_putstr(name);
	if (space - i > 0)
		ft_write_space(space - i);
}
