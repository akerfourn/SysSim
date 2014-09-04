CXX = g++
OPTS = -I./../..

all:Rossler

force:
	$(CXX) -o Rossler Rossler.cpp $(OPTS)

Rossler: Rossler.hpp Rossler.cpp
	$(CXX) -o Rossler Rossler.cpp $(OPTS)

clean: 
	rm -f Rossler out.dat

run:
	./Rossler

