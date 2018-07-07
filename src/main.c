/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:40:02 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/07 13:02:37 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int				main(int argc, char **argv)
{
	t_query		*qu;
	t_dirs		*dir;
	_Bool		isfiles;

	if (argc >= 1)
	{
		qu = ft_flags(argv, argc);
		ft_order(qu);
		isfiles = ft_justfiles(qu);
		if ((dir = ft_passdirs(qu->fnames)))
		{
			ft_fillfiles(qu, dir);
			ft_show(qu, dir, isfiles);
		}
	}
	return (0);
}
