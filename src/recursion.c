/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 14:56:59 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 19:28:08 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void		ft_dorecursion(t_query *qu, char **fpaths)
{

}

void            ft_recursion(t_query *qu, t_dirs *dir)
{
	t_dirs		*tmp;
	t_file		*ftmp;
	t_dirs		*newdir;
	t_file		*tmpstart;

	ftmp = dir->file;
	tmp = dir;
	while (tmp)
	{
		while (ftmp)
		{
			if ((ftmp->type == DT_DIR) && ftmp->name[0] != '.')
			{
				printf("\n%s:\n", ftmp->path);
				if ((newdir = dirs_alloc(ftmp->path)))
				{
					ft_fillfiles(qu, newdir);
					tmpstart = newdir->file;
					ft_show_listed(qu, tmpstart, 0);
					ft_recursion(qu, newdir);
				}
			}
			ftmp = ftmp->next;
		}
		tmp = tmp->next;
	}
}

