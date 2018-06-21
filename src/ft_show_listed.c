/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_listed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:45:02 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/21 19:22:49 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void        ft_permissions(struct stat stats)
{
	ft_putstr( (S_ISDIR(stats.st_mode)) ? "d" : "-");
    ft_putstr( (stats.st_mode & S_IRUSR) ? "r" : "-");
    ft_putstr( (stats.st_mode & S_IWUSR) ? "w" : "-");
    ft_putstr( (stats.st_mode & S_IXUSR) ? "x" : "-");
    ft_putstr( (stats.st_mode & S_IRGRP) ? "r" : "-");
    ft_putstr( (stats.st_mode & S_IWGRP) ? "w" : "-");
    ft_putstr( (stats.st_mode & S_IXGRP) ? "x" : "-");
    ft_putstr( (stats.st_mode & S_IROTH) ? "r" : "-");
    ft_putstr( (stats.st_mode & S_IWOTH) ? "w" : "-");
    ft_putstr( (stats.st_mode & S_IXOTH) ? "x" : "-");
	ft_putstr("  ");
	ft_putnbr(stats.st_nlink);
}

static void			ft_pwdgroup(struct stat stats)
{
	struct group 	*grp;
	struct passwd 	*pwd;

	pwd = getpwuid(stats.st_uid);
	ft_putstr(pwd->pw_name);
	ft_putstr("  ");
	grp = getgrgid(stats.st_gid);
	ft_putstr(grp->gr_name);
	ft_putstr("  ");
	ft_putnbr(stats.st_size);
}

static void 		ft_modifydate(struct stat stats)
{
	char 			*date;
	char 			*cutdate;
	int 			i;
	int 			j;
	int 			check;

	check = 0;
	i = 0;
	date = ctime(&stats.st_mtimespec.tv_sec);
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
	ft_putstr("  ");
}

static void 		ft_total(t_file *file)
{
	int 			total;

	total = 0;
	while (file)
	{
		total += file->stats.st_blocks;
		file = file->next;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void 		        ft_show_listed(t_dirs *dir, t_query *qu)
{
	t_file 			*fl;
	int 			big;
	int 			size_len;
	
	size_len = ft_biggest_name(dir->file);
	fl = dir->file;
	ft_total(fl);
	while (dir->file)
	{
		if (ft_strchr(qu->fl, 'a') || dir->file->name[0] != '.')
		{
			ft_permissions(dir->file->stats);
			ft_putstr("  ");
			ft_pwdgroup(dir->file->stats);
			ft_modifydate(dir->file->stats);
			ft_putstr(dir->file->name);
			ft_putstr("\n");
		}
		dir->file = dir->file->next;
	}
}
