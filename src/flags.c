/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:22:34 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/17 17:38:15 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void 		ft_options(char *opt)
{
	//printf("%s - flags\n", opt);
}

void		ft_names(char *fname)
{
	//printf("%s - name\n", fname);
}

void		ft_flags(char **av, int ac)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
			ft_options(av[i]);
		else
			ft_names(av[i]);
		i++;
	}
	if (av[1])
		ft_list(av[1]);
	else
		ft_list(".");
}