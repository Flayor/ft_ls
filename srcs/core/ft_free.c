/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 12:47:11 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_free_t_file(t_file *ft_file)
{
	free(ft_file->name);
	free(ft_file->link);
	free(ft_file->date_create);
	free(ft_file->date_modif);
	free(ft_file->date_access);
	free(ft_file);
}

void			ft_free_t_dir(t_ft_dir *ft_dir)
{
	t_ft_dir	*tmp;

	while (ft_dir)
	{
		tmp = ft_dir;
		free(ft_dir->folder);
		free(tmp);
		ft_dir = ft_dir->next;
	}
}
