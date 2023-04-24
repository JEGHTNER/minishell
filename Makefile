NAME = minishell

CC = CC
CFLAGS = -Wall -Wextra -Werror
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
		lst_utils.c

HEAD = minishell.h
OBJS = $(SRCS:.c=.o)
LIBFT_A = libft/libft.a

.c.o :
	$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}

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
