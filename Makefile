# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/17 15:19:05 by dcherend          #+#    #+#              #
#    Updated: 2018/06/19 13:49:09 by dcherend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= ft_ls

LIB_DIR 		= ./lib/libft/
LIB_HDR_DIR 	= ./lib/libft/include/
OBJ_DIR 		= ./obj/
SRC_DIR 		= ./src/
HDR_DIR 		= ./include/

CC 				= gcc
CFLAGS 			= -Wall -Werror -Wextra -I$(HDR_DIR) -I$(LIB_HDR_DIR)

SRC 			= main.c processes.c query.c flags.c utils.c dirs.c modify.c
OBJ 			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB_BIN 		= $(LIB_DIR)libft.a
LIB_FLAGS 		= -lft -L$(LIB_DIR)
LIB 			= $(MAKE) -C $(LIB_DIR)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(OBJ) $(LIB_FLAGS) -o $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ # $(CFLAGS)

$(LIB):
	make -C $(LIB_DIR)

clean:
	/bin/rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)
fclean: clean
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(NAME)
	make fclean -C $(LIB_DIR)
re: fclean all

love:
	@echo "Not war."
