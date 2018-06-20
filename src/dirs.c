/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:33:09 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/20 18:09:33 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_file 					*file_alloc(struct dirent *sd, char *path)
{
	t_file 				*file;
	
	if (!(file = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	file->name = sd->d_name;
	file->type = sd->d_type;
	if ((stat(ft_strjoin(path, sd->d_name), &file->stats) < 0))
		throw_error(strerror(errno), 'm');
	file->next = NULL;
	return (file);
}

t_dirs					*dirs_alloc(DIR *directory, char *name)
{
	t_dirs				*dirs;
	t_file 				*copy;
	t_file 				*file;
	struct dirent 		*sd;

	if (!(dirs = (t_dirs*)malloc(sizeof(t_dirs))))
		return ((t_dirs*)ERR);
	dirs->name = name;
	dirs->path = ft_strjoin(name, "/");
	copy = file_alloc(readdir(directory), dirs->path);
	file = copy;
	while ((sd = readdir(directory)))
	{
		copy->next = file_alloc(sd, dirs->path);
		copy = copy->next;
	}
	closedir(directory);
	dirs->file = file;
	dirs->next = NULL;
	return (dirs);
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