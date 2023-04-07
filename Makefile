# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 18:42:27 by jehelee           #+#    #+#              #
#    Updated: 2023/04/07 20:31:59 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell


LIB_DIR		= ./inc/lib/
INC			=./inc/
SRCS_DIR	= ./src/
SRCS = test.c
OBJ = $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

CC = cc
CFLAGS = -Wextra -Werror -Wall -g
LFLAGS = -L./inc/lib -l_jehelee

#rules
	
all : libs ${NAME}

libs:
	make -C $(LIB_DIR)

%.o : %.c
	$(CC)  -g -c  -I INC $(LFLAGS) -o $@ $^ 

${NAME} : ${OBJ}
	$(CC) -g -o $(NAME) ${OBJ} -I ${INC} -L$(LIB_DIR) -l_jehelee

clean	:
	make -C $(LIB_DIR) clean
	rm -rf $(OBJ)

fclean	: 
	make -C $(LIB_DIR) fclean
	rm -rf $(OBJ)
	rm -rf	$(NAME)

re		: fclean all

# bonus: 
# 	make WITH_BONUS=1 all

.PHONY: all libs clean fclean re bonus