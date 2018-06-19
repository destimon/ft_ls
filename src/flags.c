/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:22:34 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/19 13:26:01 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int				ft_cmpflags(t_query *qu, char flag)
{
	int 		i;

	i = 0;
	while (i < FL_SIZE)
	{
		if (qu->fl[i] == flag)
			return (0);
		i++;
	}
	i = 0;
	while (i < FL_SIZE)
	{
		if (qu->fl[i] == '\0')
		{
			qu->fl[i] = flag;
			return (1);
		}
		i++;
	}
	return (0);
}

void 			ft_options(t_query *qu, char *opt)
{
	int 		i;

	i = 1;
	while (opt[i])
	{
		if (opt[i] == 'l' || opt[i] == 'R' || opt[i] == 'a' ||
			opt[i] == 'r' || opt[i] == 't')
			ft_cmpflags(qu, opt[i]);
		else
			throw_error("illegal option -- ", opt[i]);
		i++;
	}
}

void			ft_names(t_query *qu, char **fnames, int size)
{
	int 		i;

	i = 0;
	qu->fnames = (char**)malloc((sizeof(char*) * size + 1));
	while (i < size)
	{
		qu->fnames[i] = ft_strdup(fnames[i]);
		i++;
	}
	qu->fnames[size] = NULL;
}

t_query			*ft_flags(char **av, int ac)
{
	int			i;
	t_query		*qu;
	
	qu = ft_qalloc();
	i = 1;
	while (av[i])
	{
		if (av[i][0] != '-')
			break;
		ft_options(qu, av[i]);
		i++;
	}
	if (ac - i == 0)
	{
		av[i] = ft_strdup(".");
		ac++;
	}
	ft_names(qu, &av[i], ac - i);
	return (qu);
}