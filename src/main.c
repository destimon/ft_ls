/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:40:02 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 20:21:29 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*
** write
** ◦ opendir
** ◦ readdir
** ◦ closedir
** ◦ stat
** ◦ lstat
** ◦ getpwuid
** ◦ getgrgid
** ◦ listxattr
** ◦ getxattr
** ◦ time
** ◦ ctime
** ◦ readlink
** ◦ malloc
** ◦ free
** ◦ perror
** ◦ strerror
** ◦ exit
*/

/*
** Don't forget to delete comment on
** Makefile CFLAGS compilation
*/

/*
**	Okay, now we have recursion..
**	.. with alot of leaks... ... ..
**	Leaks in alloc_dir func
*/

int				main(int argc, char **argv)
{
	t_query		*qu;
	t_dirs		*dir;
	_Bool		isFiles;

	if (argc >= 1)
	{
		qu = ft_flags(argv, argc);
		ft_order(qu);
		isFiles = ft_justfiles(qu); /* Need to replace ERRORS and Single files */
		if ((dir = ft_passdirs(qu, qu->fnames)))
		{
			ft_fillfiles(qu, dir);
			ft_show(qu, dir, isFiles);
		}
	}
	system("leaks --quiet ft_ls");
	return (0);
}
