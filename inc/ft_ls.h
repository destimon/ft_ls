/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:41:17 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/07 12:29:19 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/syslimits.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/xattr.h>
# include <fcntl.h>
# include <string.h>
# include <termios.h>
# include <sys/acl.h>

# define FL_SIZE 10

/*
** lartRGf@o (10)
*/

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))

# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_YELLOW	"\x1b[33m"
# define ANSI_COLOR_BLUE		"\x1b[34m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define ANSI_COLOR_CYAN		"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

typedef struct		s_query
{
	char			fl[FL_SIZE];
	char			**fnames;
}					t_query;

typedef struct		s_file
{
	char			*name;
	char			*path;
	unsigned char	type;
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	gid_t			gid;
	quad_t			blocks;
	off_t			size;
	dev_t			st_rdev;
	struct timespec	mtime;
	char			*attr;
	struct s_file	*next;
}					t_file;

typedef struct		s_dirs
{
	DIR				*dirstruct;
	char			*name;
	char			*path;
	struct timespec	mtime;
	t_file			*file;
	struct s_dirs	*next;
}					t_dirs;

/*
** QUERY.
*/
t_query				*ft_qalloc();
void				ft_qfree(t_query *qu);

/*
** FLAGS.
*/
t_query				*ft_flags(char **av, int ac);

/*
** DIRS.
*/
t_dirs				*dirs_alloc(char *name);
void				dirs_free(t_dirs *dirs);
t_dirs				*ft_passdirs(char **fnames);

/*
** FILES.
*/
void				ft_fillfiles(t_query *qu, t_dirs *dir);
t_file				*alloc_file(t_dirs *dir, struct dirent *sd);
t_file				*alloc_file_once(char *path);

/*
** SORT.
*/
void				ft_order(t_query *qu);
void				ft_file_sort(t_query *qu, t_file *file);
void				ft_timesort(t_query *qu, t_file *file);

/*
** SORT 2.
*/
void				ft_swap_dirs(t_dirs *dir1, t_dirs *dir2);
void				ft_dirs_order(t_query *qu, t_dirs *dir);
void				ft_dirs_timesort(t_query *qu, t_dirs *dir);

/*
** SHOW.
*/
void				ft_show(t_query *qu, t_dirs *dir, _Bool isfiles);
void				ft_show_listed(t_query *qu, t_file *file, _Bool isfile);
void				simple(t_query *qu, t_dirs *dir, _Bool isfiles);
void				ft_permissions(char *path, mode_t st_mode);
void				ft_modifydate(struct timespec mtime);
void				ft_pwdgroup(t_query *qu, t_file *file, int spuid,
					int spgid);

/*
** ERRORS.
*/
void				ft_wrong_option(char opt);
void				ft_wrong_dir(char *strerr, char *name);

/*
** MEMORY.
*/
void				ft_cleandirs(t_dirs *dir);

/*
** RECURSION.
*/
void				ft_recursion(t_query *qu, t_dirs *dir);

/*
** STUFF.
*/
void				ft_linkpath(mode_t mode, char *path);
t_file				swap_part(t_file *file1);
void				dev_hints(t_file *file, int min, int maj);
_Bool				ft_justfiles(t_query *qu);
void				ft_putcoloredif(t_query *qu, mode_t mode, char *name);

/*
** PADDING.
*/
void				ft_printpadd(int len);
int					padding_links(t_file *file);
int					padding_size(t_file *file);
int					padding_uid(t_file *file);
int					padding_grp(t_file *file);
void				swap_part2(t_file **file1, t_file tmp);

/*
** PADDING 2.
*/
int					padding_min(t_file *file);
int					padding_maj(t_file *file);

/*
** ETC.
*/
int					ft_attrib(char *path);
char				*ft_getattr(char *path);
void				ft_outname(char *str);
void				ft_show_listed2(t_file *tmp, t_query *qu, int spaces[],
								_Bool isfile);

#endif
