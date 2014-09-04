CXX = g++
OPTS = -I./../..

all:rnet

rnet: rnet.cpp LRossler.hpp RosslerConnection.hpp
	$(CXX) -g -o rnet rnet.cpp $(OPTS)

force:
	$(CXX) -g -o rnet rnet.cpp $(OPTS)

clean: 
	rm -f rnet out.dat

run:
	./rnet

