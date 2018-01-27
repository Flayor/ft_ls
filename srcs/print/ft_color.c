/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 07:19:57 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_is_rw(mode_t mode)
{
	if ((mode & S_IRUSR) && (mode & S_IWUSR) &&
		(mode & S_IRGRP) && (mode & S_IWGRP) &&
		(mode & S_IROTH) && (mode & S_IWOTH))
		return (1);
	return (0);
}

static int		ft_danger(mode_t mode)
{
	if ((mode & S_IRUSR) && (mode & S_IWUSR) &&
		(mode & S_IXUSR) && (mode & S_IRGRP) &&
		(mode & S_IWGRP) && (mode & S_IXGRP) &&
		(mode & S_IROTH) && (mode & S_IWOTH) &&
		(mode & S_IXOTH))
		return (1);
	return (0);
}

static char		*ft_color2(mode_t mode, char *color)
{
	if (S_ISLNK(mode))
		color = PINK;
	else if (S_ISFIFO(mode))
		color = MAGENTA;
	else if (S_ISBLK(mode))
		color = GREEN;
	else if (S_ISSOCK(mode))
		color = YELLOW;
	else if (S_ISCHR(mode))
		color = BGCYAN;
	return (color);
}

char			*ft_color(mode_t mode)
{
	char		*color;

	color = RESET;
	if (S_ISDIR(mode))
	{
		if (ft_is_rw(mode) || ft_danger(mode))
			color = BGYELLOW;
		else
			color = CYAN;
	}
	else if (S_ISREG(mode))
	{
		if (mode & S_ISUID || mode & S_ISGID)
			color = BGRED;
		else if (mode & S_IXOTH || mode & S_IXUSR || mode & S_IXGRP)
			color = RED;
		else
			color = RESET;
	}
	else
		color = ft_color2(mode, color);
	return (color);
}
