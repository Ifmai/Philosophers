SRCS = ./src/main.c ./src/utils.c ./src/eating.c
NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -lpthread
RM = rm -rf
LIBC = ar -rcs

all: ${NAME}

$(NAME): $(SRCS)
	@gcc $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "<3 :3 uWu <3 :3"

fclean:
	@${RM} $(NAME)

re: fclean all

.PHONY: all bonus fclean re 


