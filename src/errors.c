/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:43:38 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 13:08:09 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		ft_wrong_option(char opt)
{
	if (opt)
	{
		ft_putstr("ft_ls: ");
		ft_putstr("illegal option -- ");
		ft_putchar(opt);
		ft_putstr("\nusage: ft_ls [-@afGgloRrt] [file ...]");
		ft_putstr("\n");
		exit(0);
	}
}

void		ft_wrong_dir(char *strerr, char *name)
{
	if (name)
	{
		if (ft_strcmp(strerr, "Not a directory") != 0)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(name);
			ft_putstr(": ");
			ft_putendl(strerr);
		}
	}
}
