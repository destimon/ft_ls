/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 12:30:46 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/21 14:26:46 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int				ft_file_amount(t_file *start)
{
	int 		i;
	t_file 		*copy;
	
	copy = start;
	i = 0;
	while (copy)
	{
		i++;
		copy = copy->next;
	}
	return (i);
}

void            ft_file_swap(t_file *file1, t_file *file2)
{
    t_file      tmp;

	if (file1 && file2)
	{
		tmp.name = file1->name;
		tmp.type = file1->type;
		tmp.stats = file1->stats;
		file1->name = file2->name;
		file1->type = file2->type;
		file1->stats = file2->stats;
		file2->name = tmp.name;
		file2->type = tmp.type;
		file2->stats = tmp.stats;
	}
}

void            ft_file_sort(t_query *qu, t_file *file)
{
	int 		bub;
	int 		i;
	t_file 		*start;

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
			else
				if ((ft_strcmp(file->name, file->next->name)) > 0)
					ft_file_swap(file, file->next);
			file = file->next;
		}
		file = start;
		i++;
	}
}
