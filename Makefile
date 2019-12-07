# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/07 00:56:57 by aait-ihi          #+#    #+#              #
#    Updated: 2019/12/07 01:02:52 by aait-ihi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CFLAGS = -Wall -Werror -Wextra -g

SRCS = main.c helper.c event.c

LIBFT = libft/libft.a

CC = gcc

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	@make -C libft
	@$(CC) -g $(CFLAGS) $(OBJ) $(LIBFT) -ltermcap -o $(NAME)
	@echo "\033[32m$(NAME) created\n\033[0m"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all
