NAME = libft.a
CC = cc
CFLAGS = -Werror -Wall -Wextra -g
SRCS = $(wildcard **/*.c)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)

	@ar rcs $(NAME) $(OBJS)

%.o:%.c
	@$(CC) $(CFLAGS) -I. -c $< -o $@
 
clean:
	@find . -name '*.o' -delete

fclean: clean
	@rm -f $(NAME)

re: fclean all