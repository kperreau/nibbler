#!/bin/sh
mkdir /tmp/npuzzle_glib
mkdir /tmp/npuzzle_glib/sfml
cp glib/sfml/lib/* /tmp/npuzzle_glib/sfml
export LD_LIBRARY_PATH="/tmp/npuzzle_glib/sfml"
