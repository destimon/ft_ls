/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:02:43 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/19 19:01:06 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# define FL_SIZE 	5

# define ERR		-1

typedef struct 		s_query
{
	char 			fl[6];
	char 			**fnames;
}					t_query;

typedef struct 		s_file
{
	char 			*name;
	unsigned char 	type;
	struct s_file 	*next;
}					t_file;

typedef struct 		s_dirs
{
	char 			*name;
	char 			*path;
	t_file 			*file;	
	struct s_dirs 	*next;
}					t_dirs;

// utils
void        		throw_error(char *err, char opt);
void				*throw_direrr(char *name, char *err);

// flags
t_query				*ft_flags(char **av, int ac);
t_dirs 				*ft_list(t_query *qu);
void				ft_output(t_query *qu, t_dirs *dir);

// query
t_query				*ft_qalloc();
void				ft_qfree(t_query *qu);

// dirs
t_dirs				*dirs_alloc(DIR *directory, char *name);
void				dirs_free(t_dirs *dirs);

// modify
void 	           ft_order(t_query *qu);

#endif