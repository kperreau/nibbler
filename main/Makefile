# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2017/05/14 19:20:17 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Nibbler

# Dir vars

SRCDIR = ./src

INCLUDESDIR = ./includes

# Files vars

MAIN = main.cpp

CFILES = Engine.class.cpp Snake.class.cpp Map.class.cpp

SRC = $(patsubst %, $(SRCDIR)/%, $(CFILES))

OBJ = $(SRC:.cpp=.o) $(MAIN:.cpp=.o)

HFILES = Engine.class.hpp Snake.class.hpp IGlib.class.hpp Map.class.hpp \
	IAlib.class.hpp Nibbler.hpp

HEADERS = $(patsubst %, $(INCLUDESDIR)/%, $(HFILES))

# COMPILATION

# ERRORFLAGS = -Wall -Werror -Wextra -march=native -Ofast
ERRORFLAGS = --std=c++11 -march=native -O2

INCLUDEFLAGS = -I $(INCLUDESDIR)/

FLAGS = $(ERRORFLAGS) $(INCLUDEFLAGS)

CC = clang++
# CC = g++

# Git vars

TOGIT =	$(SRC) \
		$(HEADERS) \
		$(MAIN) \
		Makefile \
		auteur \

# Rules

all: $(NAME)

$(NAME): $(OBJ)
			$(CC) $(FLAGS) $(OBJ) -ldl -o $(NAME)

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

%.o: %.cpp
	$(CC) -o $@ -c $< $(FLAGS)

git:
	git add $(TOGIT)
	git commit -m 'auto update'
	git push
