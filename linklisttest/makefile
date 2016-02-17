CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-Wall -g
CSOURCES=linkedlisttest.c linkedlisttestiterators.c ../linklist.c ../utils.c
CHEADERS=../linklist.h ../utils.h
NLSOURCE=linkedlisttest.c
NLHEARDERS=../linklist.h ../utils.h

LIBFLAGS=-L.. -llinklist -lutils

SOURCES=$(CSOURCES)
LIBOBJECTS=../linklist.o ../utils.o
COBJECTS=$(CSOURCES:.c=.o)
OBJECTS= $(COBJECTS) 
EXECUTABLES=linkedlisttest.exe linkedlisttestiterators.exe

all: $(SOURCES) $(COBJECTS) $(EXECUTABLES) 


    
$(EXECUTABLES): %.exe: %.o 
	$(CC) $(LDFLAGS) $(LIBOBJECTS) $< -o $@

$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
shared: $(NLSOURCE)
	$(CC) $(LDFLAGS) $(LIBFLAGS) -o $(EXECUTABLE) $(NLSOURCE) 
	
	
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
