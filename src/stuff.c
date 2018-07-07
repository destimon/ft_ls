/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 12:42:19 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/06 19:16:09 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

_Bool			ft_justfiles(t_query *qu)
{
	struct stat	stats;
	t_file		*file;
	int			i;

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
	return ((i > 1) ? TRUE : FALSE);
}

void			ft_linkpath(mode_t mode, char *path)
{
	char		buf[PATH_MAX];

	if (S_ISLNK(mode))
	{
		while ((readlink(path, buf, PATH_MAX)))
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
	tmp.attr = file1->attr;
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

/*
** Sorry, i was really half-bored to Define colors...
*/

void			ft_putcoloredif(t_query *qu, mode_t mode, char *name)
{
	if (ft_strchr(qu->fl, 'G'))
	{
		if (S_ISDIR(mode))
		{
			ft_putstr("\x1b[36m\e[1m");
			if ((mode & S_IROTH) && (mode & S_IWOTH) && (mode & S_IXOTH))
				ft_putstr("\x1b[0m\e[30m\e[42m");
		}
		else if (S_ISREG(mode))
		{
			(mode & S_IXUSR || mode & S_IXGRP || mode & S_IXOTH)
			? ft_putstr(ANSI_COLOR_RED) : ft_putstr(ANSI_COLOR_RESET);
		}
		else if (S_ISLNK(mode))
			ft_putstr(ANSI_COLOR_MAGENTA);
		else if (S_ISFIFO(mode))
			ft_putstr(ANSI_COLOR_YELLOW);
		else if (S_ISSOCK(mode))
			ft_putstr(ANSI_COLOR_GREEN);
		else if (S_ISCHR(mode))
			ft_putstr("\e[43m\x1b[34m");
		else if (S_ISBLK(mode))
			ft_putstr("\033[1m\033[32m");
	}
	ft_outname(name);
}
