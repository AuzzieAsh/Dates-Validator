CC = gcc
CFLAGS = -g -Wall
TARGET = dates

default: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	$(RM) $(TARGET) $(TARGET).exe *.o *~
