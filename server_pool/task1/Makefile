CC = gcc
TARGET_SERVER = server
SOURCE_SERVER = server.c
TARGET_CLIENT = client
SOURCE_CLIENT = client.c

all: $(TARGET_SERVER) $(TARGET_CLIENT)


$(TARGET_SERVER): 
	$(CC) $(SOURCE_SERVER) -o $(TARGET_SERVER)

$(TARGET_CLIENT):
	$(CC) $(SOURCE_CLIENT) -o $(TARGET_CLIENT)

runserver:
	./$(TARGET_SERVER)

runclient:
	./$(TARGET_CLIENT)

format:
	clang-format -style=Google -i $(SOURCE_SERVER) $(SOURCE_CLIENT)

clean:
	rm -rf *.o $(TARGET_SERVER) $(TARGET_CLIENT)



	

