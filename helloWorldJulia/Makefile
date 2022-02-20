SOURCE	= src/main.cpp

OBJS    = $(SOURCE:.c=.o)

HEADER	= -Iinclude

OUT	= build/helloWorld

CC	 = g++

FLAGS	 = -g3 -c -Wall
LFLAGS	 = `sdl2-config --cflags --libs`

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(HEADER)

src/main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp

clean:
	rm -rf build/*

run: $(OUT)
	./$(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)