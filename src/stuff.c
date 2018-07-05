/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 12:42:19 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 19:48:20 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

_Bool			ft_justfiles(t_query *qu)
{
	t_file		*file;
	struct stat	stats;
	int 		i;

	i = 0;
	while (qu->fnames[i])
	{
		if (lstat(qu->fnames[i], &stats) >= 0)
		{
			if (!(S_ISDIR(stats.st_mode)) && ft_strchr(qu->fl, 'l'))
			{
				file = alloc_file_once(qu->fnames[i]);
				ft_show_listed(qu, file, 1);
				free(file);
			}
			else if (!(S_ISDIR(stats.st_mode)))
			{
				ft_putcoloredif(qu, stats.st_mode, qu->fnames[i]);
				ft_putendl("");
			}
		}
		i++;
	}
	if (i > 1)
		return (1);
	return (0);
}

void			ft_linkpath(mode_t mode, char *path)
{
	char		buf[PATH_MAX];
	int			ret;

	if (S_ISLNK(mode))
	{
		while ((ret = readlink(path, buf, PATH_MAX)))
		{
			ft_putstr(" -> ");
			ft_putstr(buf);
			return ;
		}
	}
}

t_file			swap_part(t_file *file1)
{
	t_file		tmp;

	tmp.name = file1->name;
	tmp.path = file1->path;
	tmp.type = file1->type;
	tmp.mode = file1->mode;
	tmp.nlink = file1->nlink;
	tmp.uid = file1->uid;
	tmp.gid = file1->gid;
	tmp.blocks = file1->blocks;
	tmp.size = file1->size;
	tmp.mtime = file1->mtime;
	tmp.st_rdev = file1->st_rdev;
	return (tmp);
}

void			dev_hints(t_file *file, int min, int maj)
{
	t_file		*tmp;

	tmp = file;
	ft_printpadd(min - ft_numlen(MAJOR(tmp->st_rdev)) + 2);
	ft_putnbr(MAJOR(file->st_rdev));
	ft_putstr(", ");
	ft_printpadd(maj - ft_numlen(MINOR(tmp->st_rdev)) + 2);
	ft_putnbr(MINOR(file->st_rdev));
	ft_putstr("  ");
}

void			ft_putcoloredif(t_query *qu, mode_t mode, char *name)
{
	if (ft_strchr(qu->fl, 'G'))
	{
		if (S_ISDIR(mode))
			ft_putstr(ANSI_COLOR_CYAN);
		else if (S_ISREG(mode))
		{
			if (mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH)
				ft_putstr(ANSI_COLOR_RED);
			else
				ft_putstr(ANSI_COLOR_RESET);
		}
		else if (S_ISLNK(mode))
			ft_putstr(ANSI_COLOR_MAGENTA);
		else if (S_ISFIFO(mode))
			ft_putstr(ANSI_COLOR_YELLOW);
		else if (S_ISSOCK(mode))
			ft_putstr(ANSI_COLOR_GREEN);
		else if (S_ISCHR(mode))
			ft_putstr(ANSI_COLOR_BLUE);
	}
	ft_putstr(name);
	ft_putstr(ANSI_COLOR_RESET);
}