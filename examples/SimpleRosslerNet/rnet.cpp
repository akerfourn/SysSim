#include <iostream>
#include <fstream>

#include "examples/SimpleRosslerNet/LRossler.hpp"
#include "RungeKutta4.hpp"
#include "Simulation.hpp"
#include "Network.hpp"
#include "RosslerConnection.hpp"
#include "examples/SimpleRosslerNet/Rossler.hpp"

int main(void)
{

	LRossler<double> ross1(0.398,2.0,4.0);
	LRossler<double> ross2(0.398,2.0,4.0);
	LRossler<double> ross3(0.398,2.0,4.0);
	Rossler<double> ross4(0.398,2.0,4.0,false);

	RungeKutta4<double> integrator(1e-2);
	Network<double> network;

	Simulation<double> sim(network,integrator);

	RosslerConnection<double> c1(network,0,3,5e-1);
	RosslerConnection<double> c2(network,3,6,5e-1);
	RosslerConnection<double> c3(network,6,0,5e-1);

	network.add(ross1);
	network.add(ross2);
	network.add(ross3);
	network.add(ross4);
	network.finish();

	ross1.add(c3);
	ross2.add(c1);
	ross3.add(c2);

	network.x(0) = (double)1.85;
	network.x(1) = (double)0.42;
	network.x(2) = (double)1.07;

	network.x(3) = (double)1.88;
	network.x(4) = (double)0.67;
	network.x(5) = (double)2.86;

	network.x(6) = (double)0.02;
	network.x(7) = (double)0.71;
	network.x(8) = (double)0.89;
	
	ross4.x(0) = 0.0;
	ross4.x(1) = 0.0;
	ross4.x(2) = 0.0;

	double ti = 0.0;
	double tf = 200.0;

	std::ofstream datfile("out.dat", std::ios::out | std::ios::trunc);


	if (datfile)
	{
		std::cout << "sizex = " << network.sizex() << std::endl;
		std::cout << "sizey = " << network.sizey() << std::endl;

		sim.run(datfile, ti, tf);

		
		datfile.close();
	}
	else
	{
		std::cerr << "Erreur à l'ouverture du fichier !" << std::endl;
	}
	

	return 0;

}



