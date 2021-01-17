# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aerragha <aerragha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 16:22:19 by aerragha          #+#    #+#              #
#    Updated: 2021/01/16 19:02:35 by aerragha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ft_ping

SRC = main.c src/helper.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo 'SUCCESS!'

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(NAMA)

re : fclean all