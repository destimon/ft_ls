/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 17:17:17 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/04 18:38:50 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void				ft_printpadd(int len)
{
	int				i;

	i = 0;
	while (i < len)
	{
		write(1, " ", 1);
		i++;
	}
}

int					padding_size(t_file *file)
{
	t_file			*tmp;
	int				padd;
	int				len;

	len = 0;
	padd = 0;
	tmp = file;
	while (tmp)
	{
		len = ft_numlen(tmp->size);
		if (len > padd)
			padd = len;
		tmp = tmp->next;
	}
	return (padd);
}

int					padding_uid(t_file *file)
{
	struct passwd	*pwd;
	t_file			*tmp;
	int				padd;
	int				len;

	len = 0;
	padd = 0;
	tmp = file;
	while (tmp)
	{
		pwd = getpwuid(tmp->uid);
		len = ft_strlen(pwd->pw_name);
		if (len > padd)
			padd = len;
		tmp = tmp->next;
	}
	return (padd);
}

int					padding_grp(t_file *file)
{
	struct group	*grp;
	t_file			*tmp;
	int				padd;
	int				len;

	len = 0;
	padd = 0;
	tmp = file;
	while (tmp)
	{
		grp = getgrgid(tmp->gid);
		len = ft_strlen(grp->gr_name);
		if (len > padd)
			padd = len;
		tmp = tmp->next;
	}
	return (padd);
}

int					padding_links(t_file *file)
{
	t_file			*tmp;
	int				padd;
	int				len;

	len = 0;
	padd = 0;
	tmp = file;
	while (tmp)
	{
		len = ft_numlen(tmp->nlink);
		if (len > padd)
			padd = len;
		tmp = tmp->next;
	}
	return (padd);
}
