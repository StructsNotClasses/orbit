CC=clang++
CFLAGS=-Wall -g 
LINKERS=-lSDL2 -lSDL2_image -lSDL2_ttf -lm -std=c++11
INCLUDE= -I headers
DEPS=object.h input.h game.h helpers.h player.h object.h star.h fuel.h timer.h
OBJ=src/main.cpp src/game.cpp src/helpers.cpp src/player.cpp src/object.cpp src/star.cpp src/planet.cpp src/fuel.cpp src/timer.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/main: $(OBJ)
	$(CC) $(INCLUDE) -o $@ $^ $(CFLAGS) $(LINKERS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
