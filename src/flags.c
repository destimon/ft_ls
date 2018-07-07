/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:41:52 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/07 09:44:20 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static int		ft_cmpflags(t_query *qu, char flag)
{
	int			i;

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

static void		ft_options(t_query *qu, char *opt)
{
	int			i;

	i = 1;
	while (opt[i])
	{
		if (opt[i] == 'l' || opt[i] == 'R' || opt[i] == 'a' ||
			opt[i] == 'r' || opt[i] == 't' || opt[i] == 'G' ||
			opt[i] == 'f' || opt[i] == 'g' || opt[i] == 'o' ||
			opt[i] == '@')
			ft_cmpflags(qu, opt[i]);
		else
			ft_wrong_option(opt[i]);
		i++;
	}
}

static void		ft_names(t_query *qu, char **fnames, int size)
{
	int			i;

	i = 0;
	if (ft_elems(fnames) > 0)
	{
		qu->fnames = (char**)malloc((sizeof(char*) * size + 1));
		while (i < size)
		{
			qu->fnames[i] = ft_strdup(fnames[i]);
			i++;
		}
		qu->fnames[size] = NULL;
	}
	else
	{
		qu->fnames = (char**)malloc((sizeof(char*) * 1 + 1));
		qu->fnames[0] = ft_strdup(".");
		qu->fnames[1] = NULL;
	}
}

t_query			*ft_flags(char **av, int ac)
{
	t_query		*qu;
	int			i;

	qu = ft_qalloc();
	i = 1;
	while (av[i])
	{
		if (av[i][0] != '-' || !av[i][1])
			break ;
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
