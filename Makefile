OBJS	= main.o getChar.o ScreenBackend.o Worm.o cell.o -lncurses
SOURCE	= main.cpp getChar.cpp ScreenBackend.cpp Worm.cpp cell.cpp
HEADER	= getChar.hpp ScreenBackend.hpp Worm.hpp cell.hpp
OUT	= worm.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

getChar.o: getChar.cpp
	$(CC) $(FLAGS) getChar.cpp

ScreenBackend.o: ScreenBackend.cpp
	$(CC) $(FLAGS) ScreenBackend.cpp

Worm.o: Worm.cpp
	$(CC) $(FLAGS) Worm.cpp

cell.o: cell.cpp
	$(CC) $(FLAGS) cell.cpp


clean:
	rm -f *.o *.gch
