
#SETUP

CC = gcc
PARAMS = -Wall -Wextra -std=c99 -g
EXE = blitzbolt
OBJ = main.o
DEPS = struct.h

build: $(DEPS) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(PARAMS) -o $@ $^

%.o: %.c
	$(CC) $(PARAMS) -c -o $@ $<

run: $(EXE)
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(EXE)

clean:
	rm -f $(EXE) *.o