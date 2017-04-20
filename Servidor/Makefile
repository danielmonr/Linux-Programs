All: server
.PHONY=clean test

test: test.cpp helpers.h ./Protocols/messages.h
	g++ --std=c++11 test.cpp -o test -pthread

clean:
	\rm -rf server test

server: main.cpp helpers.h
	g++ --std=c++11 main.cpp -o server -pthread
