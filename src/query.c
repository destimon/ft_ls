/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:45:16 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/18 14:10:37 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_query			*ft_qalloc()
{
	t_query 	*qu;

	if (!(qu = (t_query*)malloc(sizeof(t_query))))
		return (NULL);
	ft_bzero(qu->fl, FL_SIZE);
	return (qu);
}

void			ft_qfree(t_query *qu)
{
	if (!qu)
		return ;
	ft_memdel((void**)qu);
}