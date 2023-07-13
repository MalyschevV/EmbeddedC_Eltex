CC = gcc
CFLAGS = -ldl
LFLAGS = -shared
MFLAGS = -fPIC
TARGET = main
SOURCE = main.c
ADDMODULE = addition.o
SUBMODULE = substraction.o
DIVMODULE = division.o
MULMODULE = multiplication.o
ADD = addition.c
SUB = substraction.c
MUL = multiplication.c
DIV = division.c
ADDLIB = addition.so
SUBLIB = substraction.so
DIVLIB = division.so
MULLIB = multiplication.so
LIBS = $(ADDLIB) $(MULLIB) $(DIVLIB) $(SUBLIB)

all: $(TARGET)

$(TARGET): $(LIBS)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

$(ADDLIB): $(ADDMODULE)
	$(CC) $(LFLAGS) -o $(ADDLIB) $(ADDMODULE)

$(SUBLIB): $(SUBMODULE)
	$(CC) $(LFLAGS) -o $(SUBLIB) $(SUBMODULE)

$(DIVLIB): $(DIVMODULE)
	$(CC) $(LFLAGS) -o $(DIVLIB) $(DIVMODULE)

$(MULLIB): $(MULMODULE)
	$(CC) $(LFLAGS) -o $(MULLIB) $(MULMODULE)

$(ADDMODULE):
	$(CC) $(MFLAGS) -c $(ADD)

$(SUBMODULE):
	$(CC) $(MFLAGS) -c $(SUB)

$(DIVMODULE):
	$(CC) $(MFLAGS) -c $(DIV)

$(MULMODULE):
	$(CC) $(MFLAGS) -c $(MUL)

run:
	./$(TARGET)

format:
	clang-format -style=Google -i $(SOURCE)

clean:
	rm -rf *.o *.so $(TARGET)