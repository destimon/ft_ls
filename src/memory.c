/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 12:31:04 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/04 19:34:52 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void			ft_cleandirs(t_dirs *dir)
{
	t_dirs		*copy;

	copy = dir;
	while (copy)
	{
		closedir(copy->dirstruct);
		copy = copy->next;
	}
}
