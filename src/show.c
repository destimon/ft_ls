/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:51:00 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 18:46:45 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void     simple(t_query *qu, t_dirs *dir, _Bool isFiles)
{
	t_file      *file;
	_Bool       check;

	(dir->next) ? (check = 1) : (check = isFiles);
	while (dir)
	{
		if (check)
		{
			ft_putstr("\n");
			ft_putstr(dir->name);
			ft_putendl(":");
		}
		file = dir->file;
		while (file)
		{
			if ((ft_strchr(qu->fl, 'a') || file->name[0] != '.'))
			{
				ft_putcoloredif(qu, file->mode, file->name);
				ft_putendl("");
			}
			file = file->next;
		}
		if ((ft_strchr(qu->fl, 'R')))
			ft_recursion(qu, dir);
		dir = dir->next;
	}
}

static void     listed(t_query *qu, t_dirs *dir, _Bool isFiles)
{
	t_dirs      *copy;
	t_file      *fl;
	_Bool       check;

	copy = dir;
	(copy->next) ? (check = 1) : (check = isFiles);
	while (copy)
	{
		if (check)
		{
			ft_putstr("\n");
			ft_putstr(copy->name);
			ft_putendl(":");
		}
		fl = copy->file;
		ft_show_listed(qu, fl, 0);
		copy = copy->next;
	}
}

static void		ft_sortdirs(t_query *qu, t_dirs *dir)
{
	t_dirs		*tmp;

	tmp = dir;
	ft_dirs_order(qu, tmp);
	if (ft_strchr(qu->fl, 't'))
		ft_dirs_timesort(qu, tmp);
}

void            ft_show(t_query *qu, t_dirs *dir, _Bool isFiles)
{
	t_dirs      *copy;
	t_file      *file;

	ft_sortdirs(qu, dir);
	copy = dir;
	if ((ft_strchr(qu->fl, 'l')))
		listed(qu, copy, isFiles);
	else
		simple(qu, copy, isFiles);
	if ((ft_strchr(qu->fl, 'R')))
		ft_recursion(qu, dir);
}