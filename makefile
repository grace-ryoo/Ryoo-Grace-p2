CC = gcc
CFLAGS = -Wall -pedantic-errors

# Executable names
HEAD = head

# target
all: $(HEAD) 

# build head executable
$(HEAD): head.c
	$(CC) $(CFLAGS) -o $(HEAD) head.c


clean:
	rm -f $(HEAD) 
