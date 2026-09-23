CC=gcc
CFLAGS=-Wall
TARGET=inv

all: $(TARGET)

$(TARGET): inverse_de_matrice.c
	$(CC) $(CFLAGS) inverse_de_matrice.c -o $(TARGET)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)

