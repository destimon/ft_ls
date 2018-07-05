/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 17:02:50 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 17:14:38 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int 			padding_min(t_file *file)
{
	t_file		*tmp;
	int 		len;
	int 		padd;

	padd = 0;
	len = 0;
	tmp = file;
	while (tmp)
	{
		len = ft_numlen(MINOR(tmp->st_rdev));
		if (len > padd)
			padd = len;
		tmp = tmp->next;
	}
	return (padd);
}

int 			padding_maj(t_file *file)
{
	t_file		*tmp;
	int 		len;
	int 		padd;

	padd = 0;
	len = 0;
	tmp = file;
	while (tmp)
	{
		len = ft_numlen(MAJOR(tmp->st_rdev));
		if (len > padd)
			padd = len;
		tmp = tmp->next;
	}
	return (padd);
}

