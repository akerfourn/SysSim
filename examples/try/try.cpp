#include <iostream>
#include <fstream>

#include "examples/try/LRossler.hpp"
#include "RungeKutta4.hpp"
#include "Euler.hpp"
#include "Simulation.hpp"
#include "Network.hpp"
#include "GainCoupling.hpp"

int main(void)
{

	LRossler<double> ross1(0.398,2.0,4.0);
	LRossler<double> ross2(0.398,2.0,4.0);
	LRossler<double> ross3(0.398,2.0,4.0);

	RungeKutta4<double> integrator(1e-2);
//	Euler<double> integrator(1e-2);
	Network<double> network;

	Simulation<double> sim(network,integrator);

	network.add(ross1);
	network.add(ross2);
	network.add(ross3);

	double K = 5e-1;

	GainCoupling<double> gc1(network,K,ross3,ross1,0);
	GainCoupling<double> gc2(network,K,ross1,ross2,0);
	GainCoupling<double> gc3(network,K,ross2,ross3,0);

	ross1.add(gc1);
	ross2.add(gc2);
	ross3.add(gc3);


	// 1.85   0.42   1.07
	// 1.88   0.67   2.86
	// 0.02   0.71   0.89

	network[0] = (double)1.85;
	network[1] = (double)0.42;
	network[2] = (double)1.07;

	network[3] = (double)1.88;
	network[4] = (double)0.67;
	network[5] = (double)2.86;


	network[6] = (double)0.02;
	network[7] = (double)0.71;
	network[8] = (double)0.89;

	double ti = 0.0;
	double tf = 200.0;
	long npts = 10000;

	std::ofstream datfile("out.dat", std::ios::out | std::ios::trunc);


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



