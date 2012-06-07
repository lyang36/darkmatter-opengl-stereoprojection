CC=g++
#MACOS
LFLAGS=-framework Carbon -framework OpenGL -framework GLUT


all: obj
	$(CC) --link *.o -o dmvis $(LFLAGS)
	@echo success

obj:
	$(CC) -c *.cpp    
	#$(CC) -c *.cu

clean:
	rm -f *.o
	rm -f dmvis
