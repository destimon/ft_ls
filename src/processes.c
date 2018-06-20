/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:56:54 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/20 18:21:06 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_dirs 				*ft_fetchdir(char *flags, char *name)
{
	t_dirs 			*dire;
	DIR 			*directory;
	
	if (!(directory = opendir(name)))
		return (throw_direrr(name, strerror(errno)));
	dire = dirs_alloc(directory, name);
	return (dire);
}

t_dirs				*ft_list(t_query *qu)
{
	t_dirs			*one;
	t_dirs 			*start;
	int 			i;

	i = 0;
	while (qu->fnames[i])
	{
		if ((one = ft_fetchdir(qu->fl, qu->fnames[i])))
			break;
		i++;
	}
	start = one;
	i += 1;
	while (qu->fnames[i])
	{
		one->next = ft_fetchdir(qu->fl, qu->fnames[i]);
		one = one->next;
		i++;
	}
	return (start);
}

void				ft_output(t_query *qu, t_dirs *dir)
{
	t_dirs 			*huy;
	
	while (dir)
	{
//		if (ft_strlen(qu->fl) == 0)
//			printf("fuck you\n");
		if (ft_strchr(qu->fl, 'l'))
			ft_show_listed(dir, qu);
		dir = dir->next;
	}
}