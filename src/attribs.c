/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 10:21:17 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/07 09:47:38 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "../inc/ft_ls.h"

#define BUFSIZE 1024

int					ft_attrib(char *path)
{
	acl_entry_t		entr;
	acl_t			acl;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entr) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	else if (((listxattr(path, NULL, BUFSIZE, XATTR_NOFOLLOW))) > 0)
	{
		acl_free(acl);
		return (1);
	}
	if (acl != NULL)
	{
		acl_free(acl);
		return (2);
	}
	acl_free(acl);
	return (0);
}

char				*ft_getattr(char *path)
{
	char			buf[BUFSIZE];
	char			*str;

	if (((listxattr(path, buf, BUFSIZE, XATTR_SHOWCOMPRESSION))) > 0)
	{
		str = ft_strdup(buf);
		return (str);
	}
	return (NULL);
}

void				ft_outname(char *str)
{
	ft_putstr(str);
	ft_putstr(ANSI_COLOR_RESET);
}

void				ft_show_listed2(t_file *tmp, t_query *qu, int spaces[5],
					_Bool isfile)
{
	while (tmp)
	{
		if (ft_strchr(qu->fl, 'a') || ft_strchr(qu->fl, 'f')
			|| tmp->name[0] != '.' || isfile == 1)
		{
			ft_permissions(tmp->path, tmp->mode);
			ft_printpadd(spaces[0] - ft_numlen(tmp->nlink) + 1);
			ft_putnbr(tmp->nlink);
			ft_pwdgroup(qu, tmp, spaces[1], spaces[2]);
			ft_printpadd(spaces[3] - ft_numlen(tmp->size) + 3);
			if ((S_ISCHR(tmp->mode) || S_ISBLK(tmp->mode)))
				dev_hints(tmp, spaces[4], spaces[5]);
			else
				ft_putnbr((int)tmp->size);
			ft_putstr(" ");
			ft_modifydate(tmp->mtime);
			ft_putcoloredif(qu, tmp->mode, tmp->name);
			ft_linkpath(tmp->mode, tmp->path);
			ft_putendl("");
			if (ft_strchr(qu->fl, '@') && tmp->attr)
				ft_tabputs(tmp->attr, 1);
		}
		tmp = tmp->next;
	}
}
