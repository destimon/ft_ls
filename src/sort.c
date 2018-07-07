/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:54:23 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/06 19:14:48 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void			ft_order(t_query *qu)
{
	int			i;
	int			check;
	int			length;

	if (ft_strchr(qu->fl, 'f'))
		return ;
	length = ft_elems(qu->fnames);
	i = 1;
	check = 1;
	while (check <= length)
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
	file1->attr = file2->attr;
	swap_part2(&file2, tmp);
}

void			ft_timesort(t_query *qu, t_file *file)
{
	t_file		*start;
	int			bub;
	int			i;

	i = 0;
	if (ft_strchr(qu->fl, 'f'))
		return ;
	start = file;
	bub = ft_file_amount(file);
	while (i <= bub)
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

	if (ft_strchr(qu->fl, 'f'))
		return ;
	i = 0;
	start = file;
	bub = ft_file_amount(file);
	while (i <= bub)
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
