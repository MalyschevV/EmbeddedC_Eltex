CC = gcc
CFLAGS = -lncurses
TARGET = editor
SOURCE = editor.c

all: $(TARGET)

$(TARGET): 
	$(CC) $(SOURCE) -o $(TARGET) $(CFLAGS) 

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE)

clean:
	rm -rf *.o $(TARGET) 