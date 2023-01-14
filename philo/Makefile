SRCS = ./src/main.c ./src/utils.c ./src/eating.c
NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -lpthread -g
RM = rm -rf
LIBC = ar -rcs

all: ${NAME}

$(NAME): $(SRCS)
	@gcc $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "<3 :3 uWu <3 :3"

clean:
	@${RM} ./src/*.o

fclean: clean
	@${RM} $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re .c.o


