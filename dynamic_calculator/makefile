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
ADDLIB = libaddition.so
SUBLIB = libsubstraction.so
DIVLIB = libdivision.so
MULLIB = libmultiplication.so
SOURCE_FOR_HEADER = plugin.c
LIBS = $(ADDLIB) $(MULLIB) $(DIVLIB) $(SUBLIB)

all: $(TARGET)

$(TARGET): $(LIBS)
	$(CC) $(CFLAGS) $(SOURCE) $(SOURCE_FOR_HEADER) -o $(TARGET)

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