/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 16:33:09 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/18 17:31:02 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs			*dirs_alloc(DIR *directory)
{
	t_dirs		*dirs;

	if (!(dirs = (t_dirs*)malloc(sizeof(dirs))))
		return ((t_dirs*)ERR);
	dirs->odir = directory;
	dirs->next = NULL;
	return (dirs);
}

void			dirs_free(t_dirs *dirs)
{
	int 		i;

	i = 0;
	if (dirs)
	{
		if (dirs->odir)
			ft_memdel((void**)dirs->odir);
		while (dirs->subs[i])
		{
			ft_memdel((void**)dirs->subs[i]);
			i++;
		}
		ft_memdel((void**)dirs);
	}
}