/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:03:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/06 15:56:56 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static	void			ft_direrr(char *name)
{
	free(name);
	ft_wrong_dir(strerror(errno), name);
}

t_dirs					*dirs_alloc(char *name)
{
	t_dirs				*dirs;
	DIR					*dir;
	char				*slash;
	struct stat			stats;

	if ((dir = opendir(name)))
	{
		if (!(dirs = (t_dirs*)malloc(sizeof(t_dirs))))
			return (NULL);
		slash = ft_strdup("/");
		dirs->name = ft_strdup(name);
		dirs->path = ft_strjoin(name, slash);
		free(name);
		free(slash);
		lstat(dirs->path, &stats);
		dirs->mtime = stats.st_mtimespec;
		dirs->dirstruct = dir;
		dirs->file = NULL;
		dirs->next = NULL;
		return (dirs);
	}
	else
		ft_direrr(name);
	return (NULL);
}

void					dirs_free(t_dirs *dirs)
{
	if (dirs)
	{
		while (dirs->file)
		{
			ft_memdel((void**)dirs->file);
			dirs->file = dirs->file->next;
		}
		ft_memdel((void**)dirs);
	}
}

static void				ft_passdirs2(t_dirs **dir, t_dirs **nw, char **fnames)
{
	int					i;
	t_dirs				*dir2;
	t_dirs				*nw2;

	nw2 = *nw;
	dir2 = *dir;
	i = 0;
	while (fnames[i])
	{
		nw2 = dirs_alloc(fnames[i]);
		if (nw2)
		{
			dir2->next = nw2;
			dir2 = dir2->next;
		}
		i++;
	}
}

t_dirs					*ft_passdirs(char **fnames)
{
	int					i;
	t_dirs				*dir;
	t_dirs				*start;
	t_dirs				*nw;

	i = 0;
	while (fnames[i])
	{
		if ((nw = dirs_alloc(fnames[i])))
		{
			dir = nw;
			start = dir;
			break ;
		}
		i++;
	}
	if (ft_elems(fnames) > 0 && nw && (i += 1))
	{
		ft_passdirs2(&dir, &nw, &fnames[i]);
		return (start);
	}
	return (NULL);
}
