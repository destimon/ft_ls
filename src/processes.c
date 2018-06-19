/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:56:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/19 18:49:37 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs 				*ft_fetchdir(char *name)
{
	t_dirs 			*dire;
	DIR 			*directory;
	t_dirs 			*tmp;
	
	if (!(directory = opendir(name)))
		return (throw_direrr(name, strerror(errno)));
	dire = dirs_alloc(directory, name);
	tmp = dire;
	while (tmp->file)
	{
		if (tmp->file->type == DT_DIR && tmp->file->name[0] != '.')
		{

			// Make normal Recursion
			//
			// Also need to make path instead name file
			// Things like strjoin may be useful
			// Should add variable "path" in struct

		}
		tmp->file = tmp->file->next;
	}
	return (dire);
}

t_dirs				*ft_list(t_query *qu)
{
	t_dirs			*one;
	t_dirs 			*start;
	int 			i;

	i = 0;
	while (qu->fnames[i])
	{
		if ((one = ft_fetchdir(qu->fnames[i])))
			break;
		i++;
	}
	start = one;
	i += 1;
	while (qu->fnames[i])
	{
		one->next = ft_fetchdir(qu->fnames[i]);
		one = one->next;
		i++;
	}
	return (start);
}

void				ft_output(t_query *qu, t_dirs *dir)
{
	while (dir)
	{
		while (dir->file)
		{
			printf("%s\n", dir->file->name);
			dir->file = dir->file->next;
		}
		dir = dir->next;
	}
}