/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:56:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/18 15:45:15 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int					ft_fetchdir(char *name)
{
	DIR 			*dir;
	struct dirent 	*sd;

	if (!(dir = opendir(name)))
	{
		ft_putstr(name);
		ft_putstr(": ");
		ft_putendl(strerror(errno));
		return (-1);
	}
	while ((sd = readdir(dir)))
	{
		
	}
	closedir(dir);
	return (0);
}

void				ft_list(t_query *qu)
{

	int i = 0;
	int j = 0;
	
	while (qu->fnames[j])
	{
		ft_fetchdir(qu->fnames[j]);
		j++;
	}
}