SRCSB = ./srcb/main_bonus.c ./srcb/utils_bonus.c ./srcb/eating_bonus.c
NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Werror -Wextra -lpthread -fsanitize=thread -g
RM = rm -rf
LIBC = ar -rcs

all: ${NAME}

$(NAME): $(SRCSB)
	@gcc $(CFLAGS) $(SRCSB) -o $(NAME)
	@echo "<3 :3 uWu <3 :3"

fclean:
	@${RM} $(NAME)

re: fclean all

.PHONY: all bonus fclean re .c.o


