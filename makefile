CC=g++ # Use g++ for C++ files
TARGET=main.out
SOURCES=main.cpp HashTable.cpp
CFLAGS=-O1
LFLAGS=-lm

# define list of objects
OBJS=$(SOURCES:.cpp=.o) # Correctly replace .cpp files with .o files

# the target is obtained by linking all .o files
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

purge: clean
	rm -f $(TARGET)

clean:
	rm -f *.o
	rm -f *.out
