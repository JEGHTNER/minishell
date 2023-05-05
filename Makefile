# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 18:38:09 by joon-lee          #+#    #+#              #
#    Updated: 2023/05/05 17:28:06 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -fsanitize=address
SRCS =  main.c \
		signal_manage.c \
		manage_line_main.c \
		manage_chunk.c \
		manage_quotation.c \
		manage_quotation_utils.c \
		manage_redir.c \
		manage_env.c \
		manage_env_utils.c \
		manage_pipe.c \
		tree_ops.c \
		lst_ops.c \
		lst_utils.c \
		convert_to_token.c \
		syntex_check.c \
		convert_tree.c \
		pipe_func.c \
		tree_func.c \
		tree_utils.c \
		built_in_func.c \
		built_in_func2.c \
		built_in_utils.c \
		built_in_utils2.c \
		test/test_ops.c \
		utils.c \
		utils2.c \
		free_func.c \
		here_doc.c \
		ft_split_export.c \
		

OBJS = $(SRCS:.c=.o)
LIBFT_A = libft/libft.a

# OBJS_FLAGS_IN_HOME = -I/opt/homebrew/opt/readline/include
# COMP_FLAGS_IN_HOME = -lreadline -L/opt/homebrew/opt/readline/lib

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} -g

$(NAME) : $(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -lreadline $(OBJS) $(LIBFT_A) -o $(NAME) -g

all : $(NAME)

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
