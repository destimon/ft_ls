# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/17 15:19:05 by dcherend          #+#    #+#              #
#    Updated: 2018/07/07 13:25:36 by dcherend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= ft_ls

LIBFT 			= $(LIBFT_DIR)libft.a
LIBFT_DIR 		= $(LIB_DIR)libft/
LIBFT_INC 		= $(LIBFT_DIR)$(INC_DIR)
LIBFT_FLAGS 	= -lft -L $(LIBFT_DIR)
LIBFT_DIR 		= ./lib/libft/
LIBFT_HDR_DIR 	= ./lib/libft/
OBJ_DIR 		= ./obj/
SRC_DIR 		= ./src/
HDR_DIR 		= ./include/

CC 				= gcc
CFLAGS 			= -Wall -Werror -Wextra -I$(HDR_DIR) -I$(LIBFT_HDR_DIR)

SRC 			= main.c query.c flags.c errors.c sort.c sort2.c dirs.c \
					show.c files.c recursion.c show_listed.c stuff.c \
					padding.c padding2.c attribs.c
OBJ 			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB_BIN 		= $(LIBFT_DIR)libft.a
LIB_FLAGS 		= -lft -L$(LIBFT_DIR)
LIB 			= $(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(HEADERS_FLAGS) $(CC_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
