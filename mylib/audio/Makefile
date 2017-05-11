# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kperreau <kperreau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/05 14:10:51 by kperreau          #+#    #+#              #
#    Updated: 2017/04/20 19:51:47 by kperreau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libaudio.dylib

SRCDIR = ./

CFILES = Alib.class.cpp

SRC = $(patsubst %, $(SRCDIR)%, $(CFILES))

OBJ = $(SRC:.cpp=.o)

INCLUDEDIR = .

HEADERS = Alib.class.hpp ../../main/includes/IAlib.class.hpp

# COMPILATION
ERRORFLAGS = # -Wall -Werror -Wextra

INCLUDEFLAGS = -I $(INCLUDEDIR) -I ../../glib/sfml/include/

LIBFLAGS = -L../../glib/sfml/lib/ -lsfml-system -lsfml-audio \

FLAGS = $(ERRORFLAGS) $(INCLUDEFLAGS) -std=c++11 -O2

# CC = g++
CC = clang++

# Colors vars
DEF_C = '\033[0m'
OK_C = '\033[32m'
ERR_C = '\033[31m'
WRN_C = '\033[33m'
INF_C = '\033[35m'

OK = $(OK_C)[OK]$(DEF_C)
ERR = $(ERR_C)[Error]$(DEF_C)
WAR = $(WRN_C)[Warning]$(DEF_C)
INF = $(INF_C)[Info]$(DEF_C)

# RULES

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -shared $(OBJ) $(FLAGS) $(LIBFLAGS) -o $(NAME)

re: fclean all

%.o: %.cpp
		$(CC) -fPIC $(FLAGS) -o $@ -c $<

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)
