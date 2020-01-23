CXX = g++

server.out : blockchain.o main.o
	$(CXX) -o server.out blockchain.o main.o

%.o: %.cpp %.h utils.h

.PHONY: clean

clean:
	rm -f server.out *.o