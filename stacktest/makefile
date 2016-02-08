CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-Wall -g
CSOURCES=stacktest.c ../stack.c ../utils.c
CHEADERS==../stack.h ../utils.h
NLSOURCE=stacktest.c
NLHEARDERS=../stack.h ../utils.h

LIBFLAGS=-L.. -lstack -lutils

SOURCES=$(CSOURCES)
COBJECTS=$(CSOURCES:.c=.o)
OBJECTS= $(COBJECTS) 
EXECUTABLE=stacktest.exe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(COBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(COBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	
shared: $(NLSOURCE)
	$(CC) $(LDFLAGS) $(LIBFLAGS) -o $(EXECUTABLE) $(NLSOURCE) 
	
	
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)