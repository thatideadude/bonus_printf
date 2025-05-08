NAME=libftprintf.a

SRCS=	ft_printf.c print_char.c print_str.c \
		print_ptr.c print_int.c print_handlers.c print_hex.c

OBJS=$(SRCS:.c=.o)

CFLAGS=-Wall -Werror -Wextra -g -fno-sanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: all

.c.o:
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
