CXX = g++
LIBS = -lpthread

client.out : client_receiver.o clock.o condition_handler.o dispatcher.o main.o request.o server_handler.o sync_map.o sync_priority_queue.o sync_queue.o utils.o
	$(CXX) -o client *.o $(LIBS)

sync_priority_queue.o : sync_priority_queue.h
sync_queue.o : sync_queue.h
%.o: %.cpp %.h

.PHONY: clean

clean:
	rm -f client.out *.o