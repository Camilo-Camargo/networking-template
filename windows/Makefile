LIB_NAME=adapter.o
ENTRY_POINT=adapter.c
CC=x86_64-w64-mingw32-cc
LIBS=-lwsock32 -liphlpapi -lws2_32
EXTRA= -c 

.PHONY: all

all: clean compile

compile:
	$(CC) $(EXTRA) -o $(LIB_NAME) $(ENTRY_POINT) $(LIBS)

run:
	wine a.exe

clean:
	rm -rf *.o
	
