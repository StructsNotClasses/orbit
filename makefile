CC=clang++
CFLAGS=-Wall -g -v
LINKERS=-lSDL2 -lm -std=c++11
INCLUDE= -I headers
DEPS=object.h input.h game.h helpers.h player.h object.h star.h
OBJ=src/main.cpp src/game.cpp src/helpers.cpp src/player.cpp src/object.cpp src/star.cpp src/planet.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/main: $(OBJ)
	$(CC) $(INCLUDE) -o $@ $^ $(CFLAGS) $(LINKERS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
