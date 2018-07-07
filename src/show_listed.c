/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_listed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 17:52:41 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/07 09:50:25 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void					ft_modifydate(struct timespec mtime)
{
	char				*date;
	char				*cutdate;
	int					i;
	int					j;
	int					check;

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
			break ;
		j++;
	}
	cutdate = ft_strsub(date, (unsigned int)i + 1, (unsigned int)j);
	ft_putstr(cutdate);
	free(cutdate);
	ft_putstr(" ");
}

static void				ft_total(t_query *qu, t_file *file)
{
	t_file				*tmp;
	int					total;
	_Bool				check;

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

void					ft_permissions(char *path, mode_t st_mode)
{
	char				perm[12];

	perm[0] = (S_ISDIR(st_mode)) ? (char)'d' : (char)'-';
	perm[0] = (S_ISLNK(st_mode)) ? (char)'l' : perm[0];
	perm[0] = (S_ISSOCK(st_mode)) ? (char)'s' : perm[0];
	perm[0] = (S_ISCHR(st_mode)) ? (char)'c' : perm[0];
	perm[0] = (S_ISFIFO(st_mode)) ? (char)'p' : perm[0];
	perm[0] = (S_ISBLK(st_mode)) ? (char)'b' : perm[0];
	perm[1] = (st_mode & S_IRUSR) ? (char)'r' : (char)'-';
	perm[2] = (st_mode & S_IWUSR) ? (char)'w' : (char)'-';
	perm[3] = (st_mode & S_IXUSR) ? (char)'x' : (char)'-';
	perm[4] = (st_mode & S_IRGRP) ? (char)'r' : (char)'-';
	perm[5] = (st_mode & S_IWGRP) ? (char)'w' : (char)'-';
	perm[6] = (st_mode & S_IXGRP) ? (char)'x' : (char)'-';
	perm[7] = (st_mode & S_IROTH) ? (char)'r' : (char)'-';
	perm[8] = (st_mode & S_IWOTH) ? (char)'w' : (char)'-';
	perm[9] = (st_mode & S_IXOTH) ? (char)'x' : (char)'-';
	perm[9] = (st_mode & S_ISVTX) ? (char)'t' : perm[9];
	perm[9] = (perm[0] != 'd' && perm[9] == (char)'t') ? (char)'T' : perm[9];
	perm[10] = (ft_attrib(path) == 1) ? (char)'@' : (char)' ';
	perm[10] = (ft_attrib(path) == 2) ? (char)'+' : perm[10];
	ft_putstr(perm);
}

void					ft_pwdgroup(t_query *qu, t_file *file, int spuid,
						int spgid)
{
	struct passwd		*pwd;
	struct group		*grp;

	if (!ft_strchr(qu->fl, 'g'))
	{
		pwd = getpwuid(file->uid);
		ft_printpadd(spuid - (int)ft_strlen(pwd->pw_name) + 1);
		ft_putstr(pwd->pw_name);
	}
	if (!ft_strchr(qu->fl, 'o'))
	{
		grp = getgrgid(file->gid);
		ft_printpadd(spgid - (int)ft_strlen(grp->gr_name) + 2);
		ft_putstr(grp->gr_name);
	}
}

void					ft_show_listed(t_query *qu, t_file *file,
						_Bool isfile)
{
	t_file				*tmp;
	int					spaces[6];

	spaces[0] = padding_links(file);
	spaces[1] = padding_uid(file);
	spaces[2] = padding_grp(file);
	spaces[3] = padding_size(file);
	spaces[4] = padding_min(file);
	spaces[5] = padding_maj(file);
	tmp = file;
	if (isfile == 0)
		ft_total(qu, tmp);
	ft_show_listed2(tmp, qu, spaces, isfile);
}
