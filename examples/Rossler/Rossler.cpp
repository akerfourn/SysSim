#include <iostream>
#include <fstream>

#include "examples/Rossler/Rossler.hpp"
#include "RungeKutta4.hpp"
#include "Euler.hpp"
#include "Simulation.hpp"

int main(void)
{
	Rossler<double> ross(0.398,2.0,4.0);
	RungeKutta4<double> integrator(1e-2);
//	Euler<double> integrator(1e-2);
	Simulation<double> sim(ross,integrator);

	double ti = 0.0;
	double tf = 200.0;
	long npts = 10000;

	std::ofstream datfile("out.dat", std::ios::out | std::ios::trunc);

	ross[0] = 0.0;
	ross[1] = 0.0;
	ross[2] = 0.0;

	if (datfile)
	{
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



