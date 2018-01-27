/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 08:47:26 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_write_space(int space)
{
	int			i;
	char		buff[space];

	i = 0;
	while (i < space)
	{
		buff[i] = ' ';
		i++;
	}
	write(1, buff, i);
}

static int		*ft_count_space(t_file *ft_file, int *space)
{
	t_paswd		*pw;
	t_group		*gr;

	if (space[0] < (int)ft_file->st.st_blocks)
		space[0] = (int)ft_file->st.st_blocks;
	if (space[1] < (int)ft_file->st.st_nlink)
		space[1] = (int)ft_file->st.st_nlink;
	if (space[2] < (int)ft_file->st.st_size)
		space[2] = (int)ft_file->st.st_size;
	if ((pw = getpwuid(ft_file->st.st_uid)))
		if (space[3] < (int)ft_strlen(pw->pw_name))
			space[3] = (int)ft_strlen(pw->pw_name);
	if ((gr = getgrgid(ft_file->st.st_gid)))
		if (space[4] < (int)ft_strlen(gr->gr_name))
			space[4] = (int)ft_strlen(gr->gr_name);
	return (space);
}

int				*ft_init_space(t_file *ft_file)
{
	int			*space;

	if (!(space = (int*)malloc(sizeof(int) * 6)))
		return (NULL);
	space[0] = 0;
	space[1] = 0;
	space[2] = 0;
	space[3] = 0;
	space[4] = 0;
	space[5] = 0;
	while (ft_file)
	{
		ft_count_space(ft_file, space);
		ft_file = ft_file->next;
	}
	return (space);
}

int				*ft_init_space_one(t_stat st)
{
	int			*space;
	t_paswd		*pw;
	t_group		*gr;

	if (!(space = (int*)malloc(sizeof(int) * 6)))
		return (NULL);
	space[0] = 0;
	space[1] = 0;
	space[2] = 0;
	space[3] = 0;
	space[4] = 0;
	space[5] = 0;
	if (space[0] < (int)st.st_blocks)
		space[0] = (int)st.st_blocks;
	if (space[1] < (int)st.st_nlink)
		space[1] = (int)st.st_nlink;
	if (space[2] < (int)st.st_size)
		space[2] = (int)st.st_size;
	if ((pw = getpwuid(st.st_uid)))
		if (space[3] < (int)ft_strlen(pw->pw_name))
			space[3] = (int)ft_strlen(pw->pw_name);
	if ((gr = getgrgid(st.st_gid)))
		if (space[4] < (int)ft_strlen(gr->gr_name))
			space[4] = (int)ft_strlen(gr->gr_name);
	return (space);
}

void			ft_print_space(int i, int j)
{
	int			diffi;
	int			diffj;

	diffi = 0;
	diffj = 0;
	while (i > 9)
	{
		diffi++;
		i /= 10;
	}
	while (j > 9)
	{
		diffj++;
		j /= 10;
	}
	if (diffj - diffi > 0)
		ft_write_space(diffj - diffi);
}
