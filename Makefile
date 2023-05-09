# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 18:38:09 by joon-lee          #+#    #+#              #
#    Updated: 2023/05/09 20:27:12 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -fsanitize=address
INC_DIR = ./
SRCS = main.c \
		signal_manage.c \
		test/test_ops.c
PARSE_DIR = parse/
EXECUTE_DIR = execute/
SRCS_PARSE = manage_line_main.c \
			manage_chunk.c \
			manage_quotation.c \
			manage_quotation_utils.c \
			manage_redir.c \
			manage_env.c \
			manage_env_utils.c \
			manage_pipe.c \
			tree_ops.c \
			tree_ops_utils.c \
			lst_ops.c \
			lst_utils.c \
			convert_to_token.c \
			syntex_check.c \
			convert_tree.c \
			utils.c \
			utils2.c \
			free_func.c

SRCS_EXECUTE = pipe_func.c \
				tree_func.c \
				tree_utils.c \
				tree_utils_scmd_parent.c \
				tree_utils_scmd_child.c \
				tree_utils_redir.c \
				tree_utils_builtin.c \
				built_in_func.c \
				built_in_func2.c \
				built_in_utils.c \
				built_in_utils2.c \
				built_in_utils_cd.c \
				here_doc.c \
				ft_split_export.c

OBJS = $(addprefix $(PARSE_DIR), $(SRCS_PARSE:.c=.o)) \
		$(addprefix $(EXECUTE_DIR), $(SRCS_EXECUTE:.c=.o)) \
		$(SRCS:.c=.o)
LIBFT_A = libft/libft.a

OBJS_FLAGS_IN_CLUSTER = -I/Users/joon-lee/.brew/opt/readline/include/readline
COMP_FLAGS_IN_CLUSTER = -lreadline -L/Users/joon-lee/.brew/opt/readline/lib

%.o : %.c
	$(CC) $(CFLAGS) $(OBJS_FLAGS_IN_CLUSTER) -c $< -o ${<:.c=.o} -g -I $(INC_DIR)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(COMP_FLAGS_IN_CLUSTER) $(OBJS) $(LIBFT_A) -o $(NAME) -g -I $(INC_DIR)

all : $(NAME)

clean :
	make -C libft clean
	rm -rf $(OBJS)

fclean :
	make -C libft fclean
	rm -rf $(OBJS) $(NAME)

re :
	make fclean
	make all

.PHONY: all re clean fclean
