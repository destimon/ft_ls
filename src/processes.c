/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:56:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/18 18:41:52 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs 				*ft_fetchdir(char *name)
{
	DIR 			*dir;
	struct dirent 	*sd;
	t_dirs 			*mydir;
	
	if (!(dir = opendir(name)))
		return ((t_dirs*)throw_direrr(name, strerror(errno)));
	mydir = dirs_alloc(dir, name);
	// while ((sd = readdir(dir)))
	// {
	// 	mydir-> = sd;
	// }
	//closedir(dir);
	return (mydir);
}

t_dirs				*ft_list(t_query *qu)
{
	int 			i;
	t_dirs 			*mydir;
	t_dirs 			*nextdir;
	t_dirs 			*start;

	i = 0;
	mydir = ft_fetchdir(qu->fnames[i++]);
	if (mydir)
		start = mydir;
	if (mydir)
	{
		while (qu->fnames[i])
		{
			if ((nextdir = ft_fetchdir(qu->fnames[i])))
			{
				mydir->next = nextdir;
				mydir = nextdir;
			}
			i++;
		}
		return (start);
	}
	return (NULL);
}

void				ft_output(t_dirs *dir)
{
	struct dirent	*sd;
	
	while (dir)
	{
		ft_putstr(dir->name);
		ft_putendl(":");
		while ((sd = readdir(dir->odir)))
		{
			if (sd->d_name[0] != '.')
			{
				ft_putstr(sd->d_name);
				ft_putstr("\t");
			}
		}
		ft_putstr("\n");
		if (dir->next)
			ft_putstr("\n");
		dir = dir->next;
	}
}