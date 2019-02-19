CC=g++
CFLAGS=-Wall -O3 -larmadillo -fstack-protector-all
DFLAGS=-D_FORTIFY_SOURCE=2
LDFLAGS=-Wl,-z,relro,-z,now 
DIR=src/
DIROUT=bin/

all: 
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.cpp -c lib/*.h -c lib/*.cpp
	$(CC) -o $(DIROUT)knn_test *.o $(LDFLAGS)
	rm *.o

clean:
	rm -f *.o heap_detective
