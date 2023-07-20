CC = gcc
TARGET = arrays
SOURCE = arrays.c
SORCE_FOR_HEADER = operations.c

all: $(TARGET)

$(TARGET): 
	$(CC) -o $(TARGET) $(SORCE_FOR_HEADER) $(SOURCE)

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE) 

clean:
	rm -rf *.o $(TARGET) 
	

