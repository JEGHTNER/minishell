# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joon-lee <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 18:38:09 by joon-lee          #+#    #+#              #
#    Updated: 2023/04/26 18:38:10 by joon-lee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = minishell

CC = CC
# CFLAGS = -fsanitize=address
# -Wall -Wextra -Werror
SRCS = main.c \
		signal_manage.c \
		convert_to_token.c \
		manage_chunk.c \
		syntex_check.c \
		convert_tree.c \
		manage_line_main.c \
		test/test_ops.c \
		manage_pipe.c \
		tree_ops.c \
		manage_quotation.c \
		utils.c \
		lst_ops.c \
		manage_redir.c \
		lst_utils.c \
		manage_env.c \
		manage_env_utils.c \
		utils2.c

OBJS = $(SRCS:.c=.o)
LIBFT_A = libft/libft.a

# OBJS_FLAGS_IN_HOME = -I/opt/homebrew/opt/readline/include
# COMP_FLAGS_IN_HOME = -lreadline -L/opt/homebrew/opt/readline/lib

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME) : $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT_A) -o $(NAME)

all : $(NAME)

bonus : $(BONUS)

clean :
	$(MAKE) -C libft clean
	rm -rf $(OBJS)

fclean :
	$(MAKE) -C libft fclean
	rm -rf $(OBJS) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all re clean fclean
