/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 11:35:33 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*create_lst(char *name, t_ft_dir *dir, t_arg *arg, t_file *tmp)
{
	t_stat		st;
	char		*fpath;

	fpath = ft_full_path(name, dir);
	lstat(fpath, &st);
	tmp->name = (arg->color) ? ft_color_name(name, st) : name;
	tmp->link = (S_ISLNK(st.st_mode)) ? \
	print_link(fpath) : '\0';
	tmp->tmp_name = name;
	tmp->st = st;
	tmp->date_create = ft_strsub(ctime(&st.st_birthtime), 4, 12);
	tmp->date_access = ft_strsub(ctime(&st.st_atime), 4, 12);
	tmp->date_modif = ft_strsub(ctime(&st.st_mtime), 4, 12);
	tmp->acl = ft_get_acl(fpath);
	tmp->next = NULL;
	free(fpath);
	return (tmp);
}

t_file			*ft_init_list(t_file *lst, char *str, t_ft_dir *dir, t_arg *arg)
{
	t_file		*tmp;

	if (!str)
		return (NULL);
	if (!(tmp = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	tmp = create_lst(str, dir, arg, tmp);
	tmp->next = lst;
	return (tmp);
}

char			ft_get_acl(char *name)
{
	int			xattr;
	acl_t		acl;
	acl_entry_t	entry;
	char		str;

	acl = NULL;
	xattr = 0;
	xattr = listxattr(name, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_link_np(name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		str = '@';
	else if (acl != NULL)
		str = '+';
	else
		str = ' ';
	acl_free(acl);
	return (str);
}

char			*print_link(char *path)
{
	char		*dest;
	char		*value;
	size_t		len;

	len = 256;
	value = ft_strnew(len);
	readlink(path, value, len);
	dest = ft_strjoin(" -> ", value);
	free(value);
	return (dest);
}

char			*ft_color_name(char *name, t_stat st)
{
	char		*dest;
	char		*tmp;

	tmp = ft_strjoin(ft_color(st.st_mode), name);
	dest = ft_strjoin(tmp, RESET);
	free(tmp);
	return (dest);
}
