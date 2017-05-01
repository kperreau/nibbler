#!/bin/sh
if [ -e "$PWD/glib/sfml" ]
then
	echo "\033[32;1mSFML : [Already Done !]\033[0m"
else
	echo "\033[33;1m[SFML: Downloading]"
	git clone https://github.com/SFML/SFML/ glib/sfml
	echo "\033[33m[SFML: install]\c"
	cd glib/sfml
	cmake .
	make sfml-graphics
	cp -r $PWD/glib/sfml/extlibs/libs-osx/Frameworks/ ~/Library/.
	echo "\r\033[32;1m[SFML: install Complete]"
	cd $PWD
	echo "\033[32;1m[SFML: Done]\033[0m"
fi
export LD_LIBRARY_PATH="$PWD/glib/sfml/lib"
echo "\033[33;1mType:\033[0m export LD_LIBRARY_PATH=\"$PWD/glib/sfml/lib\""
