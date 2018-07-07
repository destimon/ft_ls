/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:51:00 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/07 14:03:38 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void		dir_output(t_dirs *dir, char *name)
{
	static int	i = 0;

	if (i != 0)
		ft_putstr("\n");
	ft_putstr(name);
	ft_putendl(":");
	i++;
}

void			simple(t_query *qu, t_dirs *dir, _Bool isfiles)
{
	t_file		*file;
	_Bool		check;

	check = (dir->next) ? (TRUE) : (isfiles);
	while (dir)
	{
		if (check)
			dir_output(dir, dir->name);
		file = dir->file;
		while (file)
		{
			if ((ft_strchr(qu->fl, 'a')
			|| ft_strchr(qu->fl, 'f') || file->name[0] != '.'))
			{
				ft_putcoloredif(qu, file->mode, file->name);
				ft_putstr("\n");
			}
			file = file->next;
		}
		if ((ft_strchr(qu->fl, 'R')))
			ft_recursion(qu, dir);
		dir = dir->next;
	}
}

static void		listed(t_query *qu, t_dirs *dir, _Bool isfiles)
{
	t_dirs		*copy;
	t_file		*fl;
	_Bool		check;
	_Bool		i;

	i = FALSE;
	copy = dir;
	check = (copy->next) ? (TRUE) : (isfiles);
	while (copy)
	{
		if (check)
		{
			if (i != 0)
				ft_putstr("\n");
			ft_putstr(copy->name);
			ft_putendl(":");
		}
		fl = copy->file;
		ft_show_listed(qu, fl, 0);
		i = TRUE;
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

void			ft_show(t_query *qu, t_dirs *dir, _Bool isfiles)
{
	t_dirs		*copy;

	ft_sortdirs(qu, dir);
	copy = dir;
	if ((ft_strchr(qu->fl, 'l') || ft_strchr(qu->fl, 'g')))
		listed(qu, copy, isfiles);
	else
		simple(qu, copy, isfiles);
	if ((ft_strchr(qu->fl, 'R')))
		ft_recursion(qu, dir);
}
