#!/bin/sh

g++ -c src/Grid.cpp -o compiled/linux/Grid.o

g++ -c src/Historic.cpp -o compiled/linux/Historic.o

g++ -c src/sdl_text.cpp -o compiled/linux/sdl_text.o `sdl2-config --cflags `

g++ -c src/Window.cpp -o compiled/linux/Window.o `sdl2-config --cflags `

g++ -c src/fd/tinyfiledialogs.c -o compiled/linux/tfd.o

echo "compiling accueil.cpp..."
g++ -c src/accueil.cpp -o compiled/linux/accueil.o `sdl2-config --cflags `
if [ $? -eq 1 ]; then echo "Failed to compile main.cpp"; exit; fi

echo "compiling jeux.cpp..."
g++ -c src/jeux.cpp -o compiled/linux/jeux.o `sdl2-config --cflags `
if [ $? -eq 1 ]; then echo "Failed to compile jeux.cpp"; exit; fi

echo "compiling chiffres.cpp..."
g++ -c src/chiffres.cpp -o compiled/linux/chiffres.o `sdl2-config --cflags `
if [ $? -eq 1 ]; then echo "Failed to compile chiffres.cpp"; exit; fi

echo "compiling selecCase.cpp..."
g++ -c src/selecCase.cpp -o compiled/linux/selecCase.o `sdl2-config --cflags `
if [ $? -eq 1 ]; then echo "Failed to compile selecCase.cpp"; exit; fi

echo "compiling mainProject.cpp..."
g++ -c main.cpp -o compiled/linux/main.o `sdl2-config --cflags `
if [ $? -eq 1 ]; then echo "Failed to compile mainf4.cpp"; exit; fi

echo "compiling mainpage.cpp..."
g++ -c src/mainpage.cpp -o compiled/linux/mainpage.o `sdl2-config --cflags `
if [ $? -eq 1 ]; then echo "Failed to compile mainpage.cpp"; exit; fi

echo "compiling menuContext.cpp..."
g++ -c src/menuContext.cpp -o compiled/linux/menuContext.o `sdl2-config --cflags `
if [ $? -eq 1 ]; then echo "Failed to compile menuContext.cpp"; exit; fi

echo "compiling Project...Linux"
g++ compiled/linux/jeux.o compiled/linux/menuContext.o compiled/linux/selecCase.o compiled/linux/sdl_text.o compiled/linux/accueil.o compiled/linux/mainpage.o compiled/linux/Historic.o compiled/linux/Window.o compiled/linux/Grid.o compiled/linux/tfd.o compiled/linux/chiffres.o compiled/linux/main.o -o sudoku `sdl2-config --libs` -lSDL2_ttf
if [ $? -eq 1 ]; then echo "Failed to compile Project"; exit; fi

