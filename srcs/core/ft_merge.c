/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flayor <flayor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:37:47 by flayor            #+#    #+#             */
/*   Updated: 2018/01/21 19:10:04 by flayor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*ft_return_q(int qsize, t_file *q)
{
	while (qsize-- >= 1 && q)
		q = q->next;
	return (q);
}

static void		ft_swap(t_file *q, t_file *p)
{
	t_file		*tmp;

	tmp = q->next;
	q->next = tmp->next;
	tmp->next = p->next;
	p->next = tmp;
}

t_file			*merge_sort(t_file *p, int psize, t_file *q, int qsize)
{
	int			i;
	int			size;

	size = (ft_count_list(p) - 1);
	i = -1;
	while (i++ < size && p)
	{
		if (q->next && p->next && p->next->st.st_mtime < q->next->st.st_mtime)
		{
			ft_swap(q, p);
			if (qsize == 1)
				break ;
			qsize--;
		}
		else
		{
			if (psize == 1 && q)
				return (ft_return_q(qsize, q));
			psize--;
		}
		p = p->next;
	}
	return (q);
}

t_file			*merge_rsort(t_file *p, int psize, t_file *q, int qsize)
{
	int			i;
	int			size;

	size = (ft_count_list(p) - 1);
	i = -1;
	while (i++ < size && p)
	{
		if (q->next && p->next && p->next->st.st_mtime > q->next->st.st_mtime)
		{
			ft_swap(q, p);
			if (qsize == 1)
				break ;
			qsize--;
		}
		else
		{
			if (psize == 1 && q)
				return (ft_return_q(qsize, q));
			psize--;
		}
		p = p->next;
	}
	return (q);
}

t_file			*merge(t_file *p, int n, int sort)
{
	int			qsize;
	int			psize;
	t_file		*q;

	qsize = (n / 2);
	psize = (n - qsize);
	if (psize >= 2)
	{
		q = merge(p, psize, sort);
		if (qsize >= 2)
			merge(q, qsize, sort);
	}
	else
		q = p->next;
	if (sort)
		q = merge_rsort(p, psize, q, qsize);
	else
		q = merge_sort(p, psize, q, qsize);
	return (q);
}
