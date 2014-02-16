CXX = g++
OPTS = -I./..

all:Rossler

Rossler: Rossler.hpp Rossler.cpp
	$(CXX) -o Rossler Rossler.cpp $(OPTS)

good: Rossler.hpp MinGoodwayRossler.cpp
	$(CXX) -o Rossler MinGoodwayRossler.cpp $(OPTS)

bad: Rossler.hpp MinBadwayRossler.cpp
	$(CXX) -o Rossler MinBadwayRossler.cpp $(OPTS)

clean: 
	rm -f Rossler out.dat

run:
	./Rossler

