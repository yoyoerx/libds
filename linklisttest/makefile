CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-Wall -g
CSOURCES=linkedlisttest.c ../linklist.c ../utils.c
CHEADERS==../linklist.h ../utils.h
NLSOURCE=linkedlisttest.c
NLHEARDERS=../linklist.h ../utils.h

LIBFLAGS=-L.. -llinklist -lutils

SOURCES=$(CSOURCES)
COBJECTS=$(CSOURCES:.c=.o)
OBJECTS= $(COBJECTS) 
EXECUTABLE=linkedlisttest.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(COBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
shared: $(NLSOURCE)
	$(CC) $(LDFLAGS) $(LIBFLAGS) -o $(EXECUTABLE) $(NLSOURCE) 
	
	
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
