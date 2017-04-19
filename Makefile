# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2017/04/16 19:35:17 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
all: engine sfml

engine:
	make -C engine/

sfml:
	make -C mylib/sfml/

re: fclean all

clean:
	@make -C engine/ clean
	@make -C mylib/sfml/ clean

fclean:
	@make -C engine/ fclean
	@make -C mylib/sfml/ fclean