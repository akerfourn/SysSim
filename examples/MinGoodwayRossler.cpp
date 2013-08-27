/* The minimal good way to simulate rossler system with SysSim !
 * (it can be smaller by using C++11 and delegating constructor : don't need an init function)
 */
#include <fstream>
#include "DynamicalSystem.hpp"
#include "RungeKutta4.hpp"
#include "Simulation.hpp"

template<typename T>
class Rossler: public DynamicalSystem<T>
{
	private:
		using DynamicalSystem<T>::dx;	// Allow to use "dx" instead of "this->dx" in f function.
		T a,b,c;
		
	public:
		void init(T a, T b, T c)
		{
			this->a = a;
			this->b = b;
			this->c = c;
		};
		Rossler(T a, T b, T c):DynamicalSystem<T>(3)
		{
			this->init(a,b,c);
		};
		Rossler(void):DynamicalSystem<T>(3)
		{
			this->init(0.398,2.0,4.0);
		};

		virtual void f(T t, SystemStates<T>& x)
		{
			dx[0] = -x[1] - x[2];
			dx[1] = x[0] + a * x[1];
			dx[2] = b + x[2] * ( x[0] - c);
		};
};

int main(void)
{
	Rossler<double> ross(0.40,2.0,4.0);
	RungeKutta4<double> integrator(1e-2);
	Simulation<double> sim(ross,integrator);
	std::ofstream datfile("mgout.dat", std::ios::out | std::ios::trunc);

	ross[0] = 0.0;
	ross[1] = 0.0;
	ross[2] = 0.0;

	sim.run(datfile, (unsigned long)20000,(unsigned long)1000);
		
	datfile.close();
}

