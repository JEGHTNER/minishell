# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehelee <jehelee@student.42.kr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/07 19:08:51 by jehelee           #+#    #+#              #
#    Updated: 2023/03/04 19:23:59 by jehelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= lib_jehelee.a

CC				= cc
CFLAGS			= -Wall -Werror -Wextra

AR				= ar
ARFLAGS			= -rcs

INCLUDES_DIR	= include
LIBFT_DIR		= src/libft
FT_PRINTF_DIR	= src/ft_printf
GNL_DIR			= src/gnl

LIBFT			= ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c \
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
				ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
				ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c\
				ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \

FT_PRINTF		= ft_printf.c ft_printf_utils_csp.c ft_printf_utils_diu.c ft_printf_utils_hex.c
				
GNL				= get_next_line.c get_next_line_utils.c

all: $(NAME)

$(NAME): libft ft_printf gnl

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ -g
	$(AR) $(ARFLAGS) $(NAME) $@

libft: $(addprefix $(LIBFT_DIR)/, $(LIBFT:.c=.o))
ft_printf: $(addprefix $(FT_PRINTF_DIR)/, $(FT_PRINTF:.c=.o))
gnl: $(addprefix $(GNL_DIR)/, $(GNL:.c=.o))

clean:
	rm -rf $(addprefix $(LIBFT_DIR)/, $(LIBFT:.c=.o))
	rm -rf $(addprefix $(FT_PRINTF_DIR)/, $(FT_PRINTF:.c=.o))
	rm -rf $(addprefix $(GNL_DIR)/, $(GNL:.c=.o))

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re libft ft_printf gnl