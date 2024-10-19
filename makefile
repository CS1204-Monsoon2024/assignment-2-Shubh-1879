CC=gcc # define the compiler to use
TARGET=main.out
SOURCES=main.cpp HashTable.cpp
CFLAGS=-O1
LFLAGS=-lm

################################################################################
### DO NOT EDIT THE FOLLOWING LINES ############################################

# define list of objects
OBJSC=$(SOURCES:.c=.o) # This is for C files, not needed here
OBJS=$(SOURCES:.cpp=.o) # Correctly replace .cpp files with .o files

# the target is obtained by linking all .o files
all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

purge: clean
	rm -f $(TARGET)

clean:
	rm -f *.out
