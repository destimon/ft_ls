/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_listed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 17:52:41 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/05 18:17:15 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void 		ft_modifydate(struct timespec mtime)
{
	char 			*date;
	char 			*cutdate;
	int 			i;
	int 			j;
	int 			check;

	check = 0;
	i = 0;
	date = ctime(&mtime.tv_sec);
	while (date[i] != ' ')
		i++;
	j = i;
	while (date[j])
	{
		if (date[j + 1] == ':')
			check++;
		if (check == 1)
			break;
		j++;
	}
	cutdate = ft_strsub(date, i + 1, j);
	ft_putstr(cutdate);
	free(cutdate);
	ft_putstr("  ");
}

static void			ft_total(t_query *qu, t_file *file)
{
	t_file			*tmp;
	int				total;
	_Bool 			check;

	check = 0;
	total = 0;
	tmp = file;
	while (tmp)
	{
		if (tmp->name[0] != '.' || ft_strchr(qu->fl, 'a'))
		{
			if (tmp->name[0] != '.' || ft_strchr(qu->fl, 'a'))
				check = 1;
			total += tmp->blocks;
		}
		tmp = tmp->next;
	}
	if (check == 1)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putendl("");
	}
}

static void        	ft_permissions(char *name, mode_t st_mode)
{
	char 			perm[11];
	
	perm[0] = (S_ISDIR(st_mode)) ? 'd' : '-';
	perm[0] = (S_ISLNK(st_mode)) ? 'l' : perm[0];
	perm[0] = (S_ISSOCK(st_mode)) ? 's' : perm[0];
	perm[0] = (S_ISCHR(st_mode)) ? 'c' : perm[0];
	perm[0] = (S_ISFIFO(st_mode)) ? 'p' : perm[0];
	perm[0] = (S_ISBLK(st_mode)) ? 'b' : perm[0];
	perm[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	perm[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	perm[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	perm[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	perm[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	perm[7] = (st_mode & S_IROTH) ? 'r' : '-';
	perm[8] =  (st_mode & S_IWOTH) ? 'w' : '-';
	perm[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	perm[9] = (st_mode &  S_ISVTX) ? 't' : perm[9];
	perm[9] = (perm[0] != 'd' && perm[9] == 't') ? 'T' : perm[9];
	ft_putstr(perm);
}

static void			ft_pwdgroup(uid_t uid, gid_t gid, int spuid, int spgid)
{
	struct group 	*grp;
	struct passwd 	*pwd;

	pwd = getpwuid(uid);
	ft_printpadd(spuid - ft_strlen(pwd->pw_name)+ 1);
	ft_putstr(pwd->pw_name);
	grp = getgrgid(gid);
	ft_printpadd(spgid - ft_strlen(grp->gr_name) + 2);
	ft_putstr(grp->gr_name);
}

void            ft_show_listed(t_query *qu, t_file *file, _Bool isFile)
{
	t_file 		*tmp;
	int 		spaces[6];
	
	spaces[0] = padding_links(file);
	spaces[1] = padding_uid(file);
	spaces[2] = padding_grp(file);
	spaces[3] = padding_size(file);
	spaces[4] = padding_min(file);
	spaces[5] = padding_maj(file);
	tmp = file;
	if (isFile == 0)
		ft_total(qu, tmp);
	while (tmp)
	{
		if (ft_strchr(qu->fl, 'a') || tmp->name[0] != '.' || isFile == 1)
		{
			ft_permissions(tmp->path, tmp->mode);
			ft_printpadd(spaces[0] - ft_numlen(tmp->nlink) + 2);
			ft_putnbr(tmp->nlink);
			ft_pwdgroup(tmp->uid, tmp->gid, spaces[1], spaces[2]);
			ft_printpadd(spaces[3] - ft_numlen(tmp->size) + 2);
			if ((S_ISCHR(tmp->mode) || S_ISBLK(tmp->mode)))
				dev_hints(tmp, spaces[4], spaces[5]);
			else
				ft_putnbr(tmp->size);
			ft_putstr(" ");
			ft_modifydate(tmp->mtime);
			ft_putcoloredif(qu, tmp->mode, tmp->name);
			ft_linkpath(tmp->mode, tmp->path);
			ft_putendl("");
		}
		tmp = tmp->next;
	}
}