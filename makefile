CC = gcc
CFLAGS = -Wall -pedantic-errors

# Executable names
HEAD = head
WC = wc

# target
all: $(HEAD) $(WC) 

# build head executable
$(HEAD): head.c
	$(CC) $(CFLAGS) -o $(HEAD) head.c

# build wc executable
$(WC): wc.c
	$(CC) $(CFLAGS) -o $(WC) wc.c

clean:
	rm -f $(HEAD) $(WC)
