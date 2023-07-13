CC = gcc
CFLAGS = -pthread
TARGET = threadrace
SOURCE = threadrace.c

all: $(TARGET)

$(TARGET): 
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) 

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE)

clean:
	rm -rf *.o $(TARGET) 