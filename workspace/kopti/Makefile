CC = gcc
CFLAGS = -W -WALL
TARGET = spectrum_exe
OBJECTS = main.o

$(TARGET) : $(OBJECTS) 
	
main.o : main.c
	$(CC) $(CFLAGS) -c -o main.o main.c


clean :
	rm *.o spectrum_exe
