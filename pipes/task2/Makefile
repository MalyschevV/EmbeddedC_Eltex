CC = gcc
TARGET = fifo
SOURCE = fifo.c

all: $(TARGET)

$(TARGET): 
	$(CC) $(SOURCE) -o $(TARGET) 

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE)

clean:
	rm -rf *.o $(TARGET) 
	

