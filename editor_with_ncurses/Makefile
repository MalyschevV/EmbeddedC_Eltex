CC = gcc
CFLAGS = -lncurses
TARGET = editor
SOURCE = editor.c
SORCE_FOR_HEADER = files.c

all: $(TARGET)

$(TARGET): 
	$(CC) -o $(TARGET) $(SORCE_FOR_HEADER) $(SOURCE) $(CFLAGS)

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE) 

clean:
	rm -rf *.o $(TARGET) 
	

