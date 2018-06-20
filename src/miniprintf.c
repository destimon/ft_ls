/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:41:40 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/20 18:42:04 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int        ft_biggest_name(t_file *file)
{
	char    *name;
	int     len;
	int 	len2;
	
	len = 0;
	while (file)
	{
		len2 = ft_strlen(ft_itoa(file->stats.st_size));
		if (len < len2)
			len = len2;
		file = file->next;
	}
	return (len);
}

void        print_align(int len)
{
	int 	i;

	i = 0;
	while (i < len)
	{
		ft_putchar(' ');
		i++;
	}
}