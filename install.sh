#!/bin/sh
git clone https://github.com/SFML/SFML/ glib/sfml
cd glib/sfml
cmake .
make sfml-graphics
cp -r ../../glib/sfml/extlibs/libs-osx/Frameworks/ ~/Library/.
