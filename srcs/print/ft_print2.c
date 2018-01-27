/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 11:56:27 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_total(t_file *ft_file, t_arg *arg)
{
	t_file		*tmp;
	int			count;

	tmp = ft_file;
	count = ft_count_block(tmp, arg);
	ft_putstr("total ");
	ft_putnbr(count);
	ft_putchar('\n');
}

void			ft_print_major(t_file *ft_file)
{
	ft_putnbr(major(ft_file->st.st_rdev));
	ft_putstr(",\t");
	ft_putnbr(minor(ft_file->st.st_rdev));
}

void			ft_print_major_one(int maj, int min)
{
	ft_putnbr(maj);
	ft_putstr(",\t");
	ft_putnbr(min);
}
