/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:54:23 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 10:21:24 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void			ft_order(t_query *qu)
{
	int			i;
	int			check;
	int			length;

	length = ft_elems(qu->fnames);
	i = 1;
	check = 1;
	while (check < length)
	{
		while (i < length)
		{
			if (ft_strchr(qu->fl, 'r'))
			{
				if ((ft_strcmp(qu->fnames[i - 1], qu->fnames[i])) < 0)
					ft_swapch(&qu->fnames[i - 1], &qu->fnames[i]);
			}
			else if ((ft_strcmp(qu->fnames[i - 1], qu->fnames[i])) > 0)
				ft_swapch(&qu->fnames[i - 1], &qu->fnames[i]);
			i++;
		}
		i = 1;
		check++;
	}
}

int				ft_file_amount(t_file *start)
{
	int			i;
	t_file		*copy;

	copy = start;
	i = 0;
	while (copy)
	{
		i++;
		copy = copy->next;
	}
	return (i);
}

void			ft_file_swap(t_file *file1, t_file *file2)
{
	t_file		tmp;

	tmp = swap_part(file1);
	file1->name = file2->name;
	file1->path = file2->path;
	file1->type = file2->type;
	file1->mode = file2->mode;
	file1->nlink = file2->nlink;
	file1->uid = file2->uid;
	file1->gid = file2->gid;
	file1->blocks = file2->blocks;
	file1->size = file2->size;
	file1->mtime = file2->mtime;
	file1->st_rdev = file2->st_rdev;
	file2->name = tmp.name;
	file2->path = tmp.path;
	file2->type = tmp.type;
	file2->mode = tmp.mode;
	file2->nlink = tmp.nlink;
	file2->uid = tmp.uid;
	file2->gid = tmp.gid;
	file2->blocks = tmp.blocks;
	file2->size = tmp.size;
	file2->mtime = tmp.mtime;
	file2->st_rdev = tmp.st_rdev;
}

void			ft_timesort(t_query *qu, t_file *file)
{
	t_file		*start;
	int			bub;
	int			i;

	start = file;
	i = 0;
	bub = ft_file_amount(file);
	while (i < bub)
	{
		while (file->next)
		{
			if (ft_strchr(qu->fl, 'r'))
			{
				if (file->mtime.tv_sec >= file->next->mtime.tv_sec)
					ft_file_swap(file, file->next);
			}
			else if (file->mtime.tv_sec <= file->next->mtime.tv_sec)
				ft_file_swap(file, file->next);
			file = file->next;
		}
		file = start;
		i++;
	}
}

void			ft_file_sort(t_query *qu, t_file *file)
{
	int			bub;
	int			i;
	t_file		*start;

	start = file;
	i = 0;
	bub = ft_file_amount(file);
	while (i < bub)
	{
		while (file->next)
		{
			if (ft_strchr(qu->fl, 'r'))
			{
				if ((ft_strcmp(file->name, file->next->name)) < 0)
					ft_file_swap(file, file->next);
			}
			else if ((ft_strcmp(file->name, file->next->name)) > 0)
				ft_file_swap(file, file->next);
			file = file->next;
		}
		file = start;
		i++;
	}
}
