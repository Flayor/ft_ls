/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <bnoufel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 08:15:22 by bnoufel           #+#    #+#             */
/*   Updated: 2018/01/19 21:18:23 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_sort(char **str)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	while (str[i])
	{
		j = i;
		index = i;
		while (str[j])
		{
			if (ft_strcmp(str[index], str[j]) > 0)
				index = j;
			j++;
		}
		tmp = str[index];
		str[index] = str[i];
		str[i] = tmp;
		i++;
	}
}

void		ft_rsort(char **str)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	while (str[i])
	{
		j = i;
		index = i;
		while (str[j])
		{
			if (ft_strcmp(str[index], str[j]) < 0)
				index = j;
			j++;
		}
		tmp = str[index];
		str[index] = str[i];
		str[i] = tmp;
		i++;
	}
}
