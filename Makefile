# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 11:24:42 by pablogon          #+#    #+#              #
#    Updated: 2024/09/06 14:32:29 by pablogon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= Philosophers

CFLAGS:= -g -Wall -Werror -Wextra \
		-g -fsanitize=address,undefined \
		-Wunreachable-code -Ofast \

SRC_DIR = src
INC_DIR = include

HEADERS := -I$(INC_DIR)

SRCS	:= philo.c \

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
	@echo "Compiling Philosophers..."

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft