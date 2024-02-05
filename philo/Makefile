# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migarci2 <migarci2@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 13:24:14 by migarci2          #+#    #+#              #
#    Updated: 2024/01/31 13:24:15 by migarci2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
INC = -I./inc
CFLAGS = -g -Wall -Wextra -Werror -pthread $(INC)

SRC = main.c src/init.c src/management.c src/simulation.c src/util.c src/actions.c src/thread.c
OBJ = $(SRC:%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME) 4 410 200 200

.PHONY: all clean fclean re