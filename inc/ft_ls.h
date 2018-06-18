/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:02:43 by dcherend          #+#    #+#             */
/*   Updated: 2018/06/18 15:26:50 by dcherend         ###   ########.fr       */
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

typedef struct 		s_query
{
	char 			fl[6];
	char 			**fnames;
}					t_query;


// utils
void        		throw_error(char *err, char opt);

// flags
t_query				*ft_flags(char **av, int ac);
void 				ft_list(t_query *qu);


// query
t_query				*ft_qalloc();
void				ft_qfree(t_query *qu);

#endif