#SETUP
CC = gcc
PARAMS = -Wall -Wextra -g
EXE = blitzbolt

build: $(EXE)

$(EXE): main.o 
	$(CC) $(PARAMS) main.o -o $(EXE)

main.o: main.c struct.h
	$(CC) $(PARAMS) -c main.c

run: $(EXE)
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(EXE)

clean:
	rm -f ./blitzbolt
	rm -f ./*.o