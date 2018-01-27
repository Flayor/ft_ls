/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 15:20:28 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		file_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	return ('-');
}

static t_file	*create_lst_rec(char *name, char *path, t_arg *arg, t_file *tmp)
{
	t_stat		st;
	char		*tmp2;
	char		*fpath;
	char		*fpathr;

	fpathr = ft_full_path_rec(path, name);
	tmp2 = ft_strjoin(path, "/");
	fpath = ft_strjoinfree(tmp2, name, 1);
	lstat(fpathr, &st);
	tmp->name = (arg->color) ? ft_color_name(name, st) : name;
	tmp->link = (S_ISLNK(st.st_mode)) ? \
	print_link(fpathr) : '\0';
	tmp->tmp_name = name;
	tmp->st = st;
	tmp->date_create = ft_strsub(ctime(&st.st_birthtime), 4, 12);
	tmp->date_access = ft_strsub(ctime(&st.st_atime), 4, 12);
	tmp->date_modif = ft_strsub(ctime(&st.st_mtime), 4, 12);
	tmp->acl = ft_get_acl(fpath);
	tmp->next = NULL;
	free(fpath);
	free(fpathr);
	return (tmp);
}

t_file			*ft_init_list_rec(t_file *lst, char *name, char *p, t_arg *arg)
{
	t_file		*tmp;

	if (!name)
		return (NULL);
	if (!(tmp = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	tmp = create_lst_rec(name, p, arg, tmp);
	tmp->next = lst;
	return (tmp);
}

char			*ft_full_path_rec(char *path, char *name)
{
	char		*dest;
	char		*tmp;

	dest = NULL;
	if (!(tmp = ft_strjoin(path, "/")))
		return (NULL);
	if (!(dest = ft_strjoinfree(tmp, name, 1)))
		return (NULL);
	return (dest);
}

void			ft_ls_read_right(mode_t mode, char acl)
{
	char		right[12];

	right[0] = file_type(mode);
	right[1] = (mode & S_IRUSR) ? 'r' : '-';
	right[2] = (mode & S_IWUSR) ? 'w' : '-';
	right[3] = (mode & S_IXUSR) ? 'x' : '-';
	right[4] = (mode & S_IRGRP) ? 'r' : '-';
	right[5] = (mode & S_IWGRP) ? 'w' : '-';
	right[6] = (mode & S_IXGRP) ? 'x' : '-';
	right[7] = (mode & S_IROTH) ? 'r' : '-';
	right[8] = (mode & S_IWOTH) ? 'w' : '-';
	right[9] = (mode & S_IXOTH) ? 'x' : '-';
	if (mode & S_ISVTX)
		right[9] = (right[9] == '-' ? 'T' : 't');
	if (mode & S_ISUID)
		right[3] = (right[3] == '-' ? 'S' : 's');
	if (mode & S_ISGID)
		right[6] = (right[6] == '-' ? 'S' : 's');
	right[10] = acl;
	right[11] = ' ';
	write(1, right, 12);
}
