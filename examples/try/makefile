CXX = g++
OPTS = -I./../..

all:try

try: try.cpp LRossler.hpp
	$(CXX) -pg -o try try.cpp $(OPTS)

clean: 
	rm -f try out.dat

run:
	./try

