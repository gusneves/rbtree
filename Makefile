TARGET=main
COMPILER=g++
LIB=rbtree

build: deps
	$(COMPILER) -Wall -o $(TARGET) $(TARGET).o $(LIB).o -lm

deps: 
	$(COMPILER) -Wall -g -c $(LIB).cpp && $(COMPILER) -Wall -g -c $(TARGET).cpp

clean:
	rm -rf *.o

install: build clean