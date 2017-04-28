#!/bin/sh
git clone https://github.com/SFML/SFML/ /tmp/npuzzle_glib/sfml
cd /tmp/npuzzle_glib/sfml
cmake .
make sfml-graphics
cp -r /tmp/npuzzle_glib/glib/sfml/extlibs/libs-osx/Frameworks/ ~/Library/.
mkdir /tmp/npuzzle_glib
mkdir /tmp/npuzzle_glib/sfml
cp glib/sfml/lib/* /tmp/npuzzle_glib/sfml
export LD_LIBRARY_PATH="/tmp/npuzzle_glib/sfml"
