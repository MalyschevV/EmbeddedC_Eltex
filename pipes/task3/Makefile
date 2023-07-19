CC = gcc
TARGET = pipe_interpretator
SOURCE = pipe_interpretator.c

all: $(TARGET)

$(TARGET): 
	$(CC) $(SOURCE) -o $(TARGET) 

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE)

clean:
	rm -rf *.o $(TARGET) 
	

