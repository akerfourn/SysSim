CXX = g++
OPTS = -I./../..

all:Rossler

Rossler: Rossler.hpp Rossler.cpp
	$(CXX) -o Rossler Rossler.cpp $(OPTS)

clean: 
	rm -f Rossler out.dat

run:
	./Rossler

