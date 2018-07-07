/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 13:11:06 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 12:36:33 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_file				*alloc_file(t_dirs *dir, struct dirent *sd)
{
	struct stat		stats;
	t_file			*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	file->name = ft_strdup(sd->d_name);
	file->type = sd->d_type;
	file->path = ft_strjoin(dir->path, file->name);
	file->attr = ft_getattr(file->path);
	if ((lstat(file->path, &stats) < 0))
		return (NULL);
	file->mode = stats.st_mode;
	file->nlink = stats.st_nlink;
	file->uid = stats.st_uid;
	file->gid = stats.st_gid;
	file->blocks = stats.st_blocks;
	file->mtime = stats.st_mtimespec;
	file->size = stats.st_size;
	file->st_rdev = stats.st_rdev;
	file->next = NULL;
	return (file);
}

t_file				*alloc_file_once(char *path)
{
	struct stat		stats;
	t_file			*file;

	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	if ((lstat(path, &stats) < 0))
		return (NULL);
	file->name = path;
	file->attr = ft_getattr(path);
	file->path = path;
	file->mode = stats.st_mode;
	file->nlink = stats.st_nlink;
	file->uid = stats.st_uid;
	file->gid = stats.st_gid;
	file->blocks = stats.st_blocks;
	file->mtime = stats.st_mtimespec;
	file->size = stats.st_size;
	file->st_rdev = stats.st_rdev;
	file->next = NULL;
	return (file);
}

t_file				*get_files(t_query *qu, t_dirs *dir)
{
	struct dirent	*sd;
	t_file			*file;

	sd = readdir(dir->dirstruct);
	dir->file = alloc_file(dir, sd);
	file = dir->file;
	while ((sd = readdir(dir->dirstruct)))
	{
		dir->file->next = alloc_file(dir, sd);
		dir->file = dir->file->next;
	}
	closedir(dir->dirstruct);
	if ((ft_strchr(qu->fl, 't')))
		ft_timesort(qu, file);
	else
		ft_file_sort(qu, file);
	return (file);
}

void				ft_fillfiles(t_query *qu, t_dirs *dir)
{
	while (dir)
	{
		dir->file = get_files(qu, dir);
		dir = dir->next;
	}
}
