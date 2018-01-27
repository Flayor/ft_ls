/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 08:08:13 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_error(char *arg)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putendl_fd(arg, 2);
	ft_putendl_fd("usage: ft_ls [-GRUafglorstu1] [file ...]", 2);
	exit(1);
}

void		ft_folder_error_exit(char *folder)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(folder, 2);
	ft_putendl_fd("fts_open: No such file or directory", 2);
	exit(-1);
}

void		ft_folder_error(char *folder)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(folder, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void		ft_err_denied(char *folder)
{
	char	**str;
	int		i;

	i = 0;
	ft_putstr_fd("ft_ls: ", 2);
	str = ft_strsplit(folder, '/');
	if (str)
		ft_putstr_fd(str[ft_sstrlen(str) - 1], 2);
	else
		ft_putstr_fd(folder, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void		ft_err_denied_no_errno(char *folder)
{
	char	**str;
	int		i;

	i = 0;
	ft_putstr_fd("ft_ls: ", 2);
	str = ft_strsplit(folder, '/');
	if (str)
		ft_putstr_fd(str[ft_sstrlen(str) - 1], 2);
	else
		ft_putstr_fd(folder, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("Permission denied", 2);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
