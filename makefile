CC=gcc
CFLAGS=-c -Wall -fpic -g
LDFLAGS=-shared
LIBFLAGS=-L. -lutils
CSOURCES=stack.c linklist.c 
CHEADERS=stack.h linklist.h
PRIMARY=utils.c
PHEADERS=utils.h

SOURCES=$(CSOURCES)
COBJECTS=$(CSOURCES:.c=.o)
SLIBS=$(COBJECTS:.o=.dll)
POBJECTS=$(PRIMARY:.c=.o)
PLIBS=$(POBJECTS:.o=.dll)
OBJECTS= $(COBJECTS) $(POBJECTS) 
LIBS= $(PLIBS) $(SLIBS)

slib: lib $(PLIBS) $(SLIBS) 
 
$(SLIBS): %.dll: %.o
	$(CC) $(LDFLAGS) $(LIBFLAGS) $< -o $@

$(PLIBS):%.dll: %.o
	$(CC) $(LDFLAGS) $< -o $@	
 
lib: $(PRIMARY) $(SOURCES) $(OBJECTS)
	
$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@	

clean:
	rm -f  $(OBJECTS) $(LIBS)