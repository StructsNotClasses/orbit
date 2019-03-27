CC=g++
CFLAGS=-Wall -g -lSDL2
INCLUDE= -I headers
DEPS=object.h input.h game.h helpers.h
OBJ=src/main.cpp src/game.cpp src/helpers.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/main: $(OBJ)
	$(CC) $(INCLUDE) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
