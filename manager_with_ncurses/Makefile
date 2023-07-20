CC = gcc
CFLAGS = -lncurses
TARGET = manager
SOURCE = manager.c
SORCE_FOR_HEADER = dirs.c

all: $(TARGET)

$(TARGET): 
	$(CC) -o $(TARGET) $(SORCE_FOR_HEADER) $(SOURCE) $(CFLAGS)

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE) 

clean:
	rm -rf *.o $(TARGET) 
	

