#!/bin/sh
git clone https://github.com/SFML/SFML/ glib/sfml
cd glib/sfml
cmake .
make