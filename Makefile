all: geometry

geometry: geometry.c
	gcc -Wall -O0 -g geometry.c -o geometry
