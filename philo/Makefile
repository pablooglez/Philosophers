# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/06 11:24:42 by pablogon          #+#    #+#              #
#    Updated: 2024/09/24 21:51:56 by pablogon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= philo

CFLAGS:= -g -Wall -Werror -Wextra \
		#-g -fsanitize=address,undefined \
		#-Wunreachable-code -Ofast 


SRC_DIR = src
INC_DIR = include

HEADERS := -I$(INC_DIR)

SRCS	:= src/init.c \
		src/main.c \
		src/parse.c \
		src/threads.c \
		src/utils.c \
		src/utils2.c \

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
	@echo "Compiling Philo..."

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft