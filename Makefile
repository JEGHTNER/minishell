# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 18:42:27 by jehelee           #+#    #+#              #
#    Updated: 2023/04/06 21:28:31 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell


LIB_DIR		= ./lib/
INC			=./inc/
SRCS_DIR	= ./src/
SRCS = test.c
OBJ = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wextra -Werror -Wall -g
LFLAGS = -L./inc/lib -l_jehelee

#rules
	
all : libs ${NAME}

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS) -I INC

${NAME} : ${OBJ}
	$(CC) $(CFLAGS) -o $(NAME) ${OBJ} $(LFLAGS) -I INC

clean	:
	rm -rf $(OBJ)

fclean	: 
	rm -rf $(OBJ)
	rm -rf	$(NAME)

re		: fclean all

# bonus: 
# 	make WITH_BONUS=1 all

.PHONY: all libs clean fclean re bonus