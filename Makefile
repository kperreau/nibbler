# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2017/05/04 19:43:17 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
all: core audio sfml sdl glfw

core:
	make -C main/

audio:
	make -C mylib/audio/

sfml:
	make -C mylib/sfml/

sdl:
	make -C mylib/sdl/

glfw:
	make -C mylib/glfw/

re: fclean all

clean:
	make -C main/ clean
	make -C mylib/audio/ clean
	make -C mylib/sfml/ clean
	make -C mylib/sdl/ clean
	make -C mylib/glfw/ clean

fclean:
	make -C main/ fclean
	make -C mylib/audio/ fclean
	make -C mylib/sfml/ fclean
	make -C mylib/sdl/ fclean
	make -C mylib/glfw/ fclean
