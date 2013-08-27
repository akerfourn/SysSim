/* The minimal bad way to simulate rossler system with SysSim !
 * It works but it clearly not the best way to code.
 */
#include <fstream>
#include "DynamicalSystem.hpp"
#include "RungeKutta4.hpp"
#include "Simulation.hpp"

template<typename T>
class Rossler: public DynamicalSystem<T>
{
	private: using DynamicalSystem<T>::dx;	// Allow to use "dx" instead of "this->dx" in f function.
		
	public:
		Rossler(void):DynamicalSystem<T>(3){};
		virtual void f(T t, SystemStates<T>& x)
		{
			T a = (T)0.432, b = (T)2.0, c = (T)4.0;
			dx[0] = -x[1] - x[2];
			dx[1] = x[0] + a * x[1];
			dx[2] = b + x[2] * ( x[0] - c);
		};
};

int main(void)
{
	Rossler<double> ross;
	RungeKutta4<double> integrator(1e-2);
	Simulation<double> sim(ross,integrator);
	std::ofstream datfile("mbout.dat", std::ios::out | std::ios::trunc);

	ross[0] = 0.0;
	ross[1] = 0.0;
	ross[2] = 0.0;

	sim.run(datfile, 10000);
		
	datfile.close();
}

