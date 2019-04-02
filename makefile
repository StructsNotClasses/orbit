CC=g++
CFLAGS=-Wall -g -lSDL2
INCLUDE= -I headers
DEPS=object.h input.h game.h helpers.h player.h
OBJ=src/main.cpp src/game.cpp src/helpers.cpp src/player.cpp 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/main: $(OBJ)
	$(CC) $(INCLUDE) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
