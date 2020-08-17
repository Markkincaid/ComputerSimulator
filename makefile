TARGET = progC
LIBS = -lm -lwiringPi
CC = gcc
CFLAGS = -g -Wall -std=c11
AS = as

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
SRCOBJECTS = $(patsubst %.s, %.o, $(wildcard *.s))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS) $(SRCOBJECTS)
	$(CC) $(OBJECTS) $(SRCOBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
