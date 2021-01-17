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

PATH_SRC = src/

PATH_OBJ = obj/

SRC = main.c\
	  helper.c

ALL_OBJ = $(addprefix $(PATH_OBJ), $(SRC:.c=.o))

INCDIR = includes/

HEADERS = $(addprefix $(INCDIR), ft_ping.h)

INC = -I $(INCDIR)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all : $(PATH_OBJ) $(NAME)

$(PATH_OBJ):
	@mkdir -p $@

$(NAME) : $(ALL_OBJ)
	$(CC) $(ALL_OBJ) -o $(NAME)

$(PATH_OBJ)%.o : $(PATH_SRC)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INC) $< -o $@
	
clean :
	@rm -rf $(PATH_OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all