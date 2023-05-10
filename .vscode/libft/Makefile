NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c \
	ft_isprint.c \
	ft_putchar_fd.c \
	ft_striteri.c \
	ft_strnstr.c \
	ft_bzero.c \
	ft_itoa.c \
	ft_putendl_fd.c \
	ft_strjoin.c \
	ft_strrchr.c \
	ft_calloc.c \
	ft_memchr.c \
	ft_putnbr_fd.c \
	ft_strlcat.c \
	ft_strtrim.c \
	ft_isalnum.c \
	ft_memcmp.c \
	ft_putstr_fd.c \
	ft_strlcpy.c \
	ft_substr.c \
	ft_isalpha.c \
	ft_memcpy.c \
	ft_split.c \
	ft_strlen.c \
	ft_tolower.c \
	ft_isascii.c \
	ft_memmove.c \
	ft_strchr.c \
	ft_strmapi.c \
	ft_toupper.c \
	ft_isdigit.c \
	ft_memset.c \
	ft_strdup.c \
	ft_strncmp.c \
	ft_printf.c	\
	change_char.c \
	change_hexadecimal.c \
	change_integar.c	\
	change_pointer_add.c \
	change_string.c	\
	change_unsigned_int.c \
	get_next_line.c \
	get_next_line_utils.c
BONUS_SRCS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c  \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c
HEAD = libft.h
OBJS = $(SRCS:.c=.o) 
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef BONUS
	OBJ = $(OBJS) $(BONUS_OBJS)
else
	OBJ = $(OBJS)
endif

%.o :	%.c
	$(CC) -c $(CFLAGS) $< -o $@ -I $(HEAD) -g

$(NAME) :	$(OBJ)
	ar rc  $@ $^

all :	$(NAME)

bonus :	$(BONUS_OBJS)
	make all BONUS=1

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean:		clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean bonus fclean re