/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 15:15:05 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/21 15:23:33 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void        ft_show_simple(t_dirs *dir, t_query *qu)
{
	while (dir->file)
	{
		if (ft_strchr(qu->fl, 'a') || dir->file->name[0] != '.')
			ft_putendl(dir->file->name);
		dir->file = dir->file->next;
	}
}