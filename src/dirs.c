/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:03:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 19:16:15 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs					*dirs_alloc(char *name)
{
	t_dirs				*dirs;
	DIR					*dir;
	char				*slash;
	struct dirent		*sd;
	struct stat			stats;

	if ((dir = opendir(name)))
	{
		if (!(dirs = (t_dirs*)malloc(sizeof(t_dirs))))
			return (NULL);
		slash = ft_strdup("/");
		dirs->name = ft_strdup(name);
		dirs->path = ft_strjoin(name, slash);
		lstat(dirs->path, &stats);
		dirs->mtime = stats.st_mtimespec;
		free(name);
		free(slash);
		dirs->dirstruct = dir;
		dirs->file = NULL;
		dirs->next = NULL;
		return (dirs);
	}
	else
		ft_wrong_dir(strerror(errno), name);
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

t_dirs					*ft_passdirs(t_query *qu, char **fnames)
{
	int 				i;
	t_dirs 				*dir;
	t_dirs 				*start;
	t_dirs 				*nw;
	_Bool 				check;

	i = 0;
	check = 0;
	while (fnames[i])
	{
		if ((nw = dirs_alloc(fnames[i])))
		{
			dir = nw;
			start = dir;
			check = 1;
			break;
		}
		i++;
	}
	if ((check == 0 || ft_elems(fnames) == 0))
		return (NULL);
	if (ft_elems(fnames) > 0 && nw)
	{
		i += 1;
		while (fnames[i])
		{
			nw = dirs_alloc(fnames[i]);
			if (nw)
			{
				check = 1;
				dir->next = nw;
				dir = dir->next;
			}
			i++;
		}
	}
	return (start);
}