FLAGS = -Wall -pedantic-errors

# Executable names
Head = head
WC = wc

# Source files
SRC_HEAD = $(HEAD).c
SRC_WC = $(WC).c

# Object files
OB_HEAD = $(HEAD).o
OB_WC = $(WC).o

# target
all: $(HEAD) $(WC)

# build head executable
$(HEAD): $(SRC_HEAD)
	$(CC) $(FLAGS) -o $(HEAD) $(SRC_HEAD)

# build wc executable
$(WC): $(SRC_WC)
	$(CC) $(FLAGS) -o $(WC) $(SRC_WC)


clean:
	rm -f $(HEAD) $(WC)
