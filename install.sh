#!/bin/sh
git clone https://github.com/SFML/SFML/ glib/sfml
cd glib/sfml
cmake .
make sfml-graphics
cp -r ../../glib/sfml/extlibs/libs-osx/Frameworks/ ~/Library/.
export LD_LIBRARY_PATH="/Users/kperreau/42/nibbler/glib/sfml/lib"
