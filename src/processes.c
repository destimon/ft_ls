/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:56:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/17 18:41:51 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void				ft_list(char *name)
{
	DIR 			*dir;
	struct dirent 	*sd;

	if (!(dir = opendir(name)))
		exit(0);
	while ((sd = readdir(dir)))
	{
		if (sd->d_name[0] != '.')
		{
			ft_putendl(sd->d_name);
		}
	}
}