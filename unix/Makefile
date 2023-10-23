LIB_NAME=adapter.o
ENTRY_POINT=adapter.c
CC=cc
LIBS=
EXTRA= -c 

.PHONY: all

all: clean compile

compile:
	$(CC) $(EXTRA) -o $(LIB_NAME) $(ENTRY_POINT) $(LIBS)

clean:
	rm -rf *.o
	
