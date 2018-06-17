/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:45:16 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/17 17:11:44 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_query			*ft_qalloc()
{
	t_query 	*qu;

	if (!(qu = (t_query*)malloc(sizeof(t_query))))
		return (NULL);
}

void			ft_qfree(t_query *qu)
{
	if (!qu)
		return ;
	ft_memdel(qu);
}