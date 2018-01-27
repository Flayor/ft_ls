/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:17:36 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	ft_stop_arg(char **argv)
{
	size_t		i;
	t_stat		st;

	i = 1;
	while (argv[i])
	{
		lstat(argv[i], &st);
		if (argv[i][0] == '-' && ft_strlen(argv[i]) == 1)
			break ;
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0' \
		&& argv[i + 1] && argv[i + 1][0] == '-')
		{
			i++;
			break ;
		}
		if (argv[i][0] != '-')
			break ;
		i++;
	}
	return (i);
}

static char		*ft_split_arg(char arg)
{
	char		*str;

	if (!(str = (char *)malloc(sizeof(char))))
		return (NULL);
	str[0] = arg;
	return (str);
}

static void		ft_ls_add_dir(t_ft_dir **ft_ls_dir, char *arg)
{
	t_ft_dir	*ft_dir;

	if (!(ft_dir = (t_ft_dir *)malloc(sizeof(t_ft_dir))))
		return ;
	ft_dir->folder = ft_strdup(arg);
	ft_dir->next = *ft_ls_dir;
	free(arg);
	*ft_ls_dir = ft_dir;
}

t_arg			*ft_arg(char **argv)
{
	size_t		i;
	size_t		j;
	t_arg		*arg;

	arg = NULL;
	i = 1;
	while (argv[i])
	{
		j = 1;
		if (argv[i][0] == '\0')
			ft_folder_error_exit(argv[i]);
		if (ft_strlen(argv[i]) == 1)
			break ;
		if (argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == '\0')
		{
			arg = ft_ls_add_arg(arg, ft_strdup(argv[i]));
			break ;
		}
		if (argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
			while (argv[i][j++])
				arg = ft_ls_add_arg(arg, ft_split_arg(argv[i][j - 1]));
		i++;
	}
	return (arg);
}

t_ft_dir		*ft_folder(int argc, char **argv, t_arg *arg, t_ft_dir *ft_dir)
{
	size_t		i;
	size_t		j;
	char		**str;

	i = ft_stop_arg(argv);
	j = 0;
	(!arg) ? arg = ft_init_arg(arg) : 0;
	if (argv[1])
	{
		if (!(str = (char **)malloc(sizeof(char *) * (argc + 1))))
			return (NULL);
		while (argv[i++])
			str[j++] = ft_strdup(argv[i - 1]);
		str[j] = 0;
		(arg->r && !arg->f) ? ft_sort(str) : ft_rsort(str);
		i = 0;
		if (argv[ft_stop_arg(argv)])
			while (str[i++])
				ft_ls_add_dir(&ft_dir, str[i - 1]);
		free(str);
	}
	(!ft_dir) ? ft_ls_add_dir(&ft_dir, ft_strdup(".")) : 0;
	return (ft_dir);
}
