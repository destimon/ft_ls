/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 13:04:40 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/21 13:11:35 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static int				ft_dir_amount(t_dirs *start)
{
	int 		i;
	t_dirs 		*copy;
	
	copy = start;
	i = 0;
	while (copy)
	{
		i++;
		copy = copy->next;
	}
	return (i);
}

static void            ft_dir_swap(t_dirs *dir1, t_dirs *dir2)
{
    t_dirs      tmp;

	if (dir1 && dir2)
	{
		tmp.name = dir1->name;
        tmp.file = dir1->file;
		dir1->name = dir1->name;
		dir1->file = dir1->file;
		dir2->name = tmp.name;
		dir2->file = tmp.file;
	}
}

void            ft_dirs_sort(t_query *qu, t_dirs *dir)
{
	int 		bub;
	int 		i;
	t_dirs 		*start;

	start = dir;
	i = 0;
	bub = ft_dir_amount(dir);
	while (i < bub)
	{
		while (dir->next)
		{
			if (ft_strchr(qu->fl, 'r'))
			{
				if ((ft_strcmp(dir->name, dir->next->name)) < 0)
					ft_dir_swap(dir, dir->next);
			}
			else
				if ((ft_strcmp(dir->name, dir->next->name)) > 0)
					ft_dir_swap(dir, dir->next);
			dir = dir->next;
		}
		dir = start;
		i++;
	}
}
