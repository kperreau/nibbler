#!/bin/sh
C_PATH=$PWD
if [ -e "$C_PATH/glib/sfml" ]
then
	echo "\033[32;1mSFML : [Already Done !]\033[0m"
else
	echo "\033[33;1m[SFML: Downloading]"
	git clone https://github.com/SFML/SFML/ glib/sfml
	echo "\033[33m[SFML: install]\c"
	cd glib/sfml
	cmake .
	make sfml-graphics
	cp -r $C_PATH/glib/sfml/extlibs/libs-osx/Frameworks/ ~/Library/.
	echo "\r\033[32;1m[SFML: install Complete]"
	cd $C_PATH
	echo "\033[32;1m[SFML: Done]\033[0m"
fi

if [ -e "$C_PATH/glib/sdl" ]
then
	echo "\033[32;1mSDL : [Already Done !]\033[0m"
else
	echo "\033[33;1m[SDL: Downloading]"
	curl -o SDL.tar.gz https://www.libsdl.org/release/SDL2-2.0.5.tar.gz
	tar -zxvf SDL.tar.gz
	rm SDL.tar.gz
	mv SDL2-2.0.5 glib/sdl
	cd glib/sdl
	echo "\033[33m[SDL: install]\c\n"
	./configure --prefix=$C_PATH/glib/sdl
	make
	make install-lib
	echo "\r\033[32;1m[SDL: install Complete]"
	cd $C_PATH
	echo "\033[32;1m[SDL: Done]\033[0m"
fi

echo "\033[33;1mType:\033[0m export LD_LIBRARY_PATH=\"$C_PATH/glib/sfml/lib:$C_PATH/glib/sdl/lib\""
echo "\033[33;1mType:\033[0m export DYLD_LIBRARY_PATH=\"$C_PATH/glib/sfml/lib:$C_PATH/glib/sdl/lib\""
export LD_LIBRARY_PATH="$C_PATH/glib/sfml/lib:$C_PATH/glib/sdl/lib"
export DYLD_LIBRARY_PATH="$C_PATH/glib/sfml/lib:$C_PATH/glib/sdl/lib"
