/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 10:41:53 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_ls_set_arg2(t_arg *ft_arg, char *arg)
{
	if (ft_strcmp(arg, "1") == 0)
		ft_arg->one = TRUE;
	else if (ft_strcmp(arg, "s") == 0)
		ft_arg->s = TRUE;
	else if (ft_strcmp(arg, "g") == 0)
		ft_arg->g = TRUE;
	else if (ft_strcmp(arg, "o") == 0)
		ft_arg->o = TRUE;
	else if (ft_strcmp(arg, "--") == 0)
		ft_arg->ignore = TRUE;
	else if (ft_strcmp(arg, "f") == 0)
		ft_arg->f = TRUE;
	else
		ft_arg->error = TRUE;
}

static t_arg	*ft_ls_set_arg(t_arg *ft_arg, char *arg)
{
	if (ft_strcmp(arg, "r") == 0)
		ft_arg->r = TRUE;
	else if (ft_strcmp(arg, "l") == 0)
		ft_arg->l = TRUE;
	else if (ft_strcmp(arg, "R") == 0)
		ft_arg->rec = TRUE;
	else if (ft_strcmp(arg, "t") == 0)
		ft_arg->t = TRUE;
	else if (ft_strcmp(arg, "a") == 0)
		ft_arg->a = TRUE;
	else if (ft_strcmp(arg, "G") == 0)
		ft_arg->color = TRUE;
	else if (ft_strcmp(arg, "U") == 0)
		ft_arg->big_u = TRUE;
	else if (ft_strcmp(arg, "u") == 0)
		ft_arg->u = TRUE;
	else
		ft_ls_set_arg2(ft_arg, arg);
	return (ft_arg);
}

t_arg			*ft_ls_add_arg(t_arg *ft_arg, char *arg)
{
	if (!ft_arg)
	{
		if (!(ft_arg = (t_arg *)malloc(sizeof(t_arg))))
			return (NULL);
		ft_arg = ft_set_arg(ft_arg);
	}
	ft_arg = ft_ls_set_arg(ft_arg, arg);
	(ft_arg->error == TRUE) ? ft_error(arg) : 1;
	free(arg);
	return (ft_arg);
}

size_t			ft_count_folder(t_ft_dir *ft_dir)
{
	size_t		i;
	t_ft_dir	*dir;

	dir = ft_dir;
	i = 0;
	while (dir)
	{
		i++;
		dir = dir->next;
	}
	return (i);
}
