#include <iostream>
#include <fstream>

#include "examples/Rossler/Rossler.hpp"
#include "RungeKutta4.hpp"
#include "Euler.hpp"
#include "Simulation.hpp"
#include "Network.hpp"

int main(void)
{
	Rossler<double> ross1(0.398,2.0,4.0);
	Rossler<double> ross2(0.398,2.0,4.0);
	Rossler<double> ross3(0.398,2.0,4.0);
	RungeKutta4<double> integrator(1e-2);
//	Euler<double> integrator(1e-2);
	Network<double> network;

	Simulation<double> sim(network,integrator);

	network.add(ross1);
	network.add(ross2);
	network.add(ross3);

	double ti = 0.0;
	double tf = 200.0;
	long npts = 10000;

	std::ofstream datfile("out.dat", std::ios::out | std::ios::trunc);

	ross1[0] = 0.0;
	ross1[1] = 0.0;
	ross1[2] = 0.0;
	ross2[0] = 0.0;
	ross2[1] = 0.0;
	ross2[2] = 0.0;
	ross3[0] = 0.0;
	ross3[1] = 0.0;
	ross3[2] = 0.0;

	if (datfile)
	{
		std::cout << "sizex = " << network.sizex() << std::endl;
		std::cout << "sizey = " << network.sizey() << std::endl;
		//sim.run(std::cout, ti, tf);
		//sim.run(datfile, npts);
		sim.run(datfile, ti, tf);

		
		datfile.close();
	}
	else
	{
		std::cerr << "Erreur à l'ouverture du fichier !" << std::endl;
	}
	
	return 0;

}



