/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 09:18:08 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls_core(t_ft_dir *ft_dir, t_arg *arg, size_t len)
{
	DIR			*dir;
	DIR			*countdir;
	static int	i;
	t_stat		st;

	(!arg) ? arg = ft_init_arg(arg) : 0;
	while (ft_dir)
	{
		lstat(ft_dir->folder, &st);
		if (S_ISDIR(st.st_mode) && \
		!(st.st_mode & S_IXUSR && st.st_mode & S_IRUSR))
			return ;
		if (!S_ISLNK(st.st_mode))
		{
			dir = opendir(ft_dir->folder);
			countdir = opendir(ft_dir->folder);
			(len > 1 && dir && i++ > 0) ? ft_putchar('\n') : 0;
			(len > 1 && dir) ? ft_putstr(ft_dir->folder) : 0;
			(len > 1 && dir) ? ft_putendl(":") : 0;
			(dir) ? ft_display(dir, countdir, arg, ft_dir) : 1;
			(dir) ? closedir(dir) : 1;
			(dir) ? closedir(countdir) : 1;
		}
		ft_dir = ft_dir->next;
	}
}

t_arg			*ft_init_arg(t_arg *ft_arg)
{
	if (!(ft_arg = (t_arg *)malloc(sizeof(t_arg))))
		return (NULL);
	return (ft_set_arg(ft_arg));
}

t_arg			*ft_set_arg(t_arg *ft_arg)
{
	ft_arg->l = FALSE;
	ft_arg->r = FALSE;
	ft_arg->rec = FALSE;
	ft_arg->t = FALSE;
	ft_arg->one = FALSE;
	ft_arg->a = FALSE;
	ft_arg->g = FALSE;
	ft_arg->f = FALSE;
	ft_arg->o = FALSE;
	ft_arg->s = FALSE;
	ft_arg->u = FALSE;
	ft_arg->big_u = FALSE;
	ft_arg->color = FALSE;
	ft_arg->error = FALSE;
	ft_arg->ignore = FALSE;
	return (ft_arg);
}

char			*ft_full_path(char *name, t_ft_dir *dir)
{
	char		*dest;
	char		*tmp;

	dest = NULL;
	if (!(tmp = ft_strjoin(dir->folder, "/")))
		return (NULL);
	if (!(dest = ft_strjoinfree(tmp, name, 1)))
		return (NULL);
	return (dest);
}

int				ft_count_list(t_file *ft_file)
{
	int			i;
	t_file		*lst;

	i = 0;
	lst = ft_file;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
