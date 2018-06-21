/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:27:19 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/21 13:16:27 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

// just can move func to libft
void		ft_order(t_query *qu)
{
	int     i;
	int     check;
	int     length;

	length = ft_elems(qu->fnames);
	i = 1;
	check = 1;
	while (check < length)
	{
		while (i < length)
		{
			if (ft_strchr(qu->fl, 'r'))
			{
				if ((ft_strcmp(qu->fnames[i - 1], qu->fnames[i])) < 0)
					ft_swapch(&qu->fnames[i - 1], &qu->fnames[i]);
			}
			else
				if ((ft_strcmp(qu->fnames[i - 1], qu->fnames[i])) > 0)
					ft_swapch(&qu->fnames[i - 1], &qu->fnames[i]);
				i++;
		}
		i = 1;
		check++;
	}
}