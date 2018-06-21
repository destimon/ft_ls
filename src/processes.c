/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:56:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/21 18:30:35 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs 				*ft_fetchdir(char *flags, char *name)
{
	t_dirs 			*dire;
	DIR 			*directory;
	
	if (!(directory = opendir(name)))
		return (throw_direrr(name, strerror(errno)));
	dire = dirs_alloc(directory, name);
	return (dire);
}

t_dirs				*ft_list(t_query *qu)
{
	t_dirs			*one;
	t_dirs 			*start;
	t_dirs 			*tmp;
	int 			i;

	i = 0;
	while (qu->fnames[i])
	{
		if ((one = ft_fetchdir(qu->fl, qu->fnames[i])))
			break;
		i++;
	}
	if (ft_elems(qu->fnames) == 1 && !one)
		exit(0);
	start = one;
	i += 1;
	while (qu->fnames[i])
	{
		if ((tmp = ft_fetchdir(qu->fl, qu->fnames[i])))
		{
			one->next = tmp;
			one = one->next;
		}
		i++;
	}
	ft_file_sort(qu, start->file);
	return (start);
}

t_dirs 				*ft_subdirs(char *path)
{
	t_dirs 			*dir;

	dir = ft_fetchdir(NULL, path);
}

void				ft_output(t_query *qu, t_dirs *dir)
{
	int 			check;
	t_dirs			*subdir;
	t_file			*copy;

	(dir->next) ? (check = 1) : (check = 0);
	while (dir)
	{
		if (check == 1)
			printf("%s:\n", dir->name);
		if (ft_strchr(qu->fl, 'l'))
			ft_show_listed(dir, qu);
		else
			ft_show_simple(dir, qu);
		if (dir->next)
			ft_putendl("");
		dir = dir->next;
	}
}