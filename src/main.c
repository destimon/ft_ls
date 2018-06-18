/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:02:51 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/18 17:23:56 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int			main(int argc, char **argv)
{
	t_query *qu;
	t_dirs 	*dir;

	if (argc >= 1)
	{
		qu = ft_flags(argv, argc);
		dir = ft_list(qu);
		ft_output(dir);
	}
	return (0);
}