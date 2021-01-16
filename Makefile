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


all: 
	echo "clean, make, build"
	
build:
	gcc main.c src/helper.c -o ft_ping2

run: 
	./ft_ping2

clean:
	rm ft_ping2