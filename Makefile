# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 18:42:27 by jehelee           #+#    #+#              #
#    Updated: 2023/04/05 19:41:37 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell


LIB_DIR		= ./lib/
INC			=./inc/
SRCS_DIR	= ./src/
SRCS = main.c
OBJ = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wextra -Werror -Wall -g

#rules
	
all : ${NAME}

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

${NAME} : ${OBJ}
	$(CC) $(CFLAGS) -o $(NAME) ${OBJ}

clean	:
	rm -rf $(OBJ)

fclean	: 
	rm -rf $(OBJ)
	rm -rf	$(NAME)

re		: fclean all

# bonus: 
# 	make WITH_BONUS=1 all

.PHONY: all libs clean fclean re bonus