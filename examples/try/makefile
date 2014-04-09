CXX = g++
OPTS = -I./../..

all:try

try: try.cpp LRossler.hpp RosslerConnection.hpp
	$(CXX) -g -o try try.cpp $(OPTS)

clean: 
	rm -f try out.dat

run:
	./try

