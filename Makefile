# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2017/04/20 20:15:04 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
all: core sfml

core:
	make -C main/

sfml:
	make -C mylib/sfml/

re: fclean all

clean:
	make -C main/ clean
	make -C mylib/sfml/ clean

fclean:
	make -C main/ fclean
	make -C mylib/sfml/ fclean
