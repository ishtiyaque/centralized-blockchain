CXX = g++

server : blockchain.o main.o
	$(CXX) -o server blockchain.o main.o

%.o: %.cpp %.h

.PHONY: clean

clean:
	rm -f server *.o