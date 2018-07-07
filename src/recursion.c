/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:56:59 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/06 19:11:17 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

#define F_S(x, y) ft_simpleshow(x, y)

static void		ft_cleanrec(t_dirs *newdir)
{
	t_file		*ftmp;

	while (newdir)
	{
		ftmp = newdir->file;
		while (ftmp)
		{
			if (ftmp->path)
				free(ftmp->path);
			if (ftmp->name)
				free(ftmp->name);
			free(ftmp);
			free(ftmp->attr);
			ftmp = ftmp->next;
		}
		free(newdir->name);
		free(newdir->path);
		free(newdir);
		newdir = newdir->next;
	}
}

static void		ft_simpleshow(t_query *qu, t_file *file)
{
	while (file)
	{
		if ((ft_strchr(qu->fl, 'a')
		|| ft_strchr(qu->fl, 'f') || file->name[0] != '.'))
		{
			ft_putcoloredif(qu, file->mode, file->name);
			ft_putendl("");
		}
		file = file->next;
	}
}

static char		*ft_print(char *path)
{
	char		*path2;

	ft_putendl("");
	ft_putstr(path);
	ft_putendl(":");
	path2 = ft_strdup(path);
	return (path2);
}

static void		ft_rec2(t_query *qu, t_dirs *n)
{
	ft_fillfiles(qu, n);
	((ft_strchr(qu->fl, 'l') || ft_strchr(qu->fl, 'g'))) ?
	ft_show_listed(qu, n->file, 0) : F_S(qu, n->file);
	ft_recursion(qu, n);
	ft_cleanrec(n);
}

void			ft_recursion(t_query *qu, t_dirs *dir)
{
	t_dirs		*n;
	t_dirs		*start;
	t_file		*tmpf;
	char		*path;

	start = dir;
	while (start)
	{
		tmpf = start->file;
		while (tmpf)
		{
			if ((tmpf->type == DT_DIR) && tmpf->name[0] != '.')
			{
				path = ft_print(tmpf->path);
				if ((n = dirs_alloc(path)))
					ft_rec2(qu, n);
			}
			tmpf = tmpf->next;
		}
		start = start->next;
	}
}
