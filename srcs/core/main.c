/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 07:21:12 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_core_no_rec(t_ft_dir *ft_dir, t_arg *arg, size_t len)
{
	ft_error_folder_not_exist(ft_dir, arg);
	ls_core(ft_dir, arg, len);
}

int				main(int argc, char **argv)
{
	size_t		len;
	t_arg		*arg;
	t_ft_dir	*ft_dir;
	t_file		*ft_file;

	arg = ft_arg(argv);
	ft_dir = NULL;
	ft_dir = ft_folder(argc, argv, arg, ft_dir);
	len = ft_count_folder(ft_dir);
	(!arg) ? arg = ft_init_arg(arg) : 0;
	if (arg->rec)
	{
		if (!(ft_file = (t_file *)malloc(sizeof(t_file))))
			return (1);
		ft_error_folder_not_exist(ft_dir, arg);
		ft_rec(arg, ft_dir, ft_file);
		ft_free_t_file(ft_file);
	}
	else
		ls_core_no_rec(ft_dir, arg, len);
	ft_free_t_dir(ft_dir);
	free(arg);
	return (0);
}
