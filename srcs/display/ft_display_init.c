/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 16:13:52 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**ft_prepare_display(DIR *dir, DIR *countdir, t_arg *arg)
{
	t_dir		*file;
	size_t		len;
	size_t		len2;
	char		**str;

	len = 0;
	len2 = 0;
	while ((file = readdir(countdir)))
		len2++;
	if (!(str = (char **)malloc(sizeof(char *) * (len2 + 1))))
		return (NULL);
	while ((file = readdir(dir)))
	{
		str[len] = ft_strdup(file->d_name);
		len++;
	}
	str[len] = 0;
	(arg->r && !arg->f) ? ft_rsort(str) : ft_sort(str);
	return (str);
}

t_file			*ft_init(char **name, t_ft_dir *dir, t_arg *arg, t_file *file)
{
	int			len;

	len = 0;
	while (name[len])
		len++;
	while (len >= 0)
	{
		file = ft_init_list(file, name[len], dir, arg);
		len--;
	}
	return (file);
}

t_file			*ft_init_rec(char **name, char *path, t_arg *arg, t_file *file)
{
	int			len;

	len = 0;
	while (name[len])
		len++;
	while (len >= 0)
	{
		file = ft_init_list_rec(file, name[len], path, arg);
		len--;
	}
	return (file);
}

void			ft_display(DIR *dir, DIR *cntdir, t_arg *arg, t_ft_dir *ft_dir)
{
	t_file		*ft_file;
	char		**name;
	size_t		len;

	len = 0;
	if (!(ft_file = (t_file *)malloc(sizeof(t_file))))
		return ;
	if (arg->rec)
	{
		ft_rec(arg, ft_dir, ft_file);
		free(ft_file);
		return ;
	}
	name = ft_prepare_display(dir, cntdir, arg);
	while (name[len])
		len++;
	if ((!arg->rec && arg->l) || arg->o || arg->g)
		ft_display_l_a(name, arg, ft_file, ft_dir);
	else
		ls_simple(name, arg, ft_file, ft_dir);
	free(ft_file);
	free(name);
}

char			*ft_set_date(long timestamp, char *date)
{
	time_t		now;
	char		*newdate;
	char		*tmp;

	now = time(NULL);
	if (timestamp <= (now - 15721200) || timestamp >= (now + 1))
	{
		tmp = ft_strsub(ctime(&timestamp), 20, 21);
		tmp = ft_strjoinfree(" ", tmp, 2);
		newdate = ft_strsub(ctime(&timestamp), 4, 7);
		tmp = ft_strjoinfree(newdate, tmp, 2);
		free(newdate);
		newdate = ft_strtrim(tmp);
		free(tmp);
		tmp = newdate;
		free(tmp);
	}
	else
		newdate = date;
	return (newdate);
}
