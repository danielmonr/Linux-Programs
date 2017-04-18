All: server
.PHONY=clean test

test: test.cpp helpers.h
	g++ test.cpp -o test

clean:
	\rm -rf server test

server: main.cpp helpers.h
	g++ main.cpp -o server
