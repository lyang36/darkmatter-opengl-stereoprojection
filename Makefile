CC=g++

all: obj
	$(CC) --link *.o -o dmvis
	@echo success

obj:
	$(CC) -c *.cpp    
	#$(CC) -c *.cu

clean:
	rm -f *.o
	rm -f dmvis
