CC = gcc
CFLAGS = -g -Wpedantic -I./include -DSIZE=500000000 -pthread

OBJDIR = ./obj
SRCDIR = ./src
INCDIR = ./include

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/array.c $(SRCDIR)/sort.c
OBJECTS = $(OBJDIR)/main.o $(OBJDIR)/array.o $(OBJDIR)/sort.o

.PHONY: print
print:
	echo $(OBJECTS)

# run the executable
.PHONY: run
run: all
	./main

# build the executable
.PHONY: all
all: main

# remove generated executable and object files
.PHONY: clean
clean:
	rm -f main $(OBJECTS)
	rmdir obj

# build the executable
main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/main.o: $(SRCDIR)/main.c $(INCDIR)/array.h $(INCDIR)/sort.h objdir
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/array.o: $(SRCDIR)/array.c $(INCDIR)/array.h objdir
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(OBJDIR)/sort.o: $(SRCDIR)/sort.c $(INCDIR)/sort.h objdir
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: objdir
objdir:
	mkdir -p obj
