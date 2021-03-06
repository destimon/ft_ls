/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 14:46:45 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/06 10:02:38 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static int		ft_dirs_amount(t_dirs *start)
{
	int			i;
	t_dirs		*copy;

	copy = start;
	i = 0;
	while (copy)
	{
		i++;
		copy = copy->next;
	}
	return (i);
}

void			ft_swap_dirs(t_dirs *dir1, t_dirs *dir2)
{
	t_dirs		tmp;

	tmp.dirstruct = dir1->dirstruct;
	tmp.file = dir1->file;
	tmp.path = dir1->path;
	dir1->dirstruct = dir2->dirstruct;
	dir1->file = dir2->file;
	dir1->path = dir2->path;
	dir2->dirstruct = tmp.dirstruct;
	dir2->file = tmp.file;
	dir2->path = tmp.path;
}

void			ft_dirs_order(t_query *qu, t_dirs *dir)
{
	int			check;
	int			length;
	t_dirs		*start;

	if (!ft_strchr(qu->fl, 'f'))
		return ;
	start = dir;
	check = 0;
	length = ft_dirs_amount(dir);
	while (check <= length)
	{
		while (dir->next)
		{
			if (ft_strchr(qu->fl, 'r'))
			{
				if ((ft_strcmp(dir->name, dir->next->name)) < 0)
					ft_swap_dirs(dir, dir->next);
			}
			else if ((ft_strcmp(dir->name, dir->next->name)) > 0)
				ft_swap_dirs(dir, dir->next);
			dir = dir->next;
		}
		dir = start;
		check++;
	}
}

void			ft_dirs_timesort(t_query *qu, t_dirs *dir)
{
	t_dirs		*start;
	int			bub;
	int			i;

	if (!ft_strchr(qu->fl, 'f'))
		return ;
	start = dir;
	i = 0;
	bub = ft_dirs_amount(dir);
	while (i <= bub)
	{
		while (dir->next)
		{
			if (ft_strchr(qu->fl, 'r'))
			{
				if (dir->mtime.tv_sec >= dir->next->mtime.tv_sec)
					ft_swap_dirs(dir, dir->next);
			}
			else if (dir->mtime.tv_sec <= dir->next->mtime.tv_sec)
				ft_swap_dirs(dir, dir->next);
			dir = dir->next;
		}
		dir = start;
		i++;
	}
}

void			swap_part2(t_file **file1, t_file tmp)
{
	t_file		*fl;

	fl = *file1;
	fl->name = tmp.name;
	fl->path = tmp.path;
	fl->type = tmp.type;
	fl->mode = tmp.mode;
	fl->nlink = tmp.nlink;
	fl->uid = tmp.uid;
	fl->gid = tmp.gid;
	fl->blocks = tmp.blocks;
	fl->size = tmp.size;
	fl->mtime = tmp.mtime;
	fl->st_rdev = tmp.st_rdev;
	fl->attr = tmp.attr;
}
