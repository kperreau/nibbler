#!/bin/sh
if [ -e "$PWD/glib/sfml" ]
then
	echo "\033[32;1mSFML : [Already Done !]\033[0m"
else
	echo "\033[33;1m[SFML: Downloading]"
	git clone https://github.com/SFML/SFML/ glib/sfml
	echo "\033[33m[SFML: install]\c"
	cd glib/sfml
	curl https://gitlab.peach-bun.com/pinion/SFML/commit/3383b4a472f0bd16a8161fb8760cd3e6333f1782.patch \
	  | patch -p1
	cmake .
	make
	echo "\r\033[32;1m[SFML: install Complete]"
	cd $PWD
	echo "\033[32;1m[SFML: Done]\033[0m"
fi
echo "\033[33;1mType:\033[0m LD_LIBRARY_PATH=\"$PWD/glib/sfml/lib\""
