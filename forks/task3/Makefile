CC = gcc
TARGET = interpretator
SOURCE = command_interpretator.c

all: $(TARGET)

$(TARGET): 
	$(CC) $(SOURCE) -o $(TARGET) 

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE)

clean:
	rm -rf *.o $(TARGET) 
	

