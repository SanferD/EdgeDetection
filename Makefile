all:
	g++ main.cpp src/* -Iinc -o main `pkg-config --cflags --libs opencv`
 