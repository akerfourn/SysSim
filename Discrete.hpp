#ifndef __EULER_HPP__
#define __EULER_HPP__

/* 
 * Intégrateur pour système discret x[n+1] = f(t,x[n]) (x = dx).
 *
 *	Adrien KERFOURN
 *
 */

#include "Integrators.hpp"

template<typename T>
class Discrete: public FixedStepIntegrator<T>
{
	public:
		Discrete(void):FixedStepIntegrator<T>(){};
		Discrete(T step):FixedStepIntegrator<T>(step){};
		Discrete(FixedStepIntegrator<T> &other):FixedStepIntegrator<T>(other){};

		void operator()(T &t, DynamicalSystem<T> &system);
};

template<typename T>
void Discrete<T>::operator()(T &t, DynamicalSystem<T> &system)
{
	long i;

	system.f(t,system);

	for(i = 0; i < system.sizex(); ++i)
	{
		system[i] = system.getdx(i);
	}

	t = t + this->step;

}

#endif
