/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:24:06 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/18 14:33:16 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void        throw_error(char *err, char opt)
{
    ft_putstr("ft_ls: ");
    ft_putstr(err);
    if (opt)
    {
        ft_putchar(opt);
        ft_putstr("\nusage: ft_ls [-lRart] [file ...]");
    }
    ft_putstr("\n");
    exit(0);
}