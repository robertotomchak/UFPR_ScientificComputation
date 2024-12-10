#!/bin/bash

if [ ! -d "graphics" ]; then
    mkdir graphics
fi

if [ ! -d "graphics/a" ]; then
    mkdir graphics/a
fi

if [ ! -d "graphics/b" ]; then
    mkdir graphics/b
fi

python3 create_graphics.py