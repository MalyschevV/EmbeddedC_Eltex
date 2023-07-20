CC = gcc
TARGET = phonebook
SOURCE = phonebook_main.c
SORCE_FOR_HEADER = phonebook.c

all: $(TARGET)

$(TARGET): 
	$(CC) -o $(TARGET) $(SORCE_FOR_HEADER) $(SOURCE)

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE) 

clean:
	rm -rf *.o $(TARGET) 
	

