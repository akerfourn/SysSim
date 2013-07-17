#ifndef __EULER_HPP__
#define __EULER_HPP__

/* 
 * Méthode d'Euler (ou Runge-Kutta d'ordre 1) :
 *
 *	Implémente la méthode d'écrite sur l'article : http://fr.wikipedia.org/wiki/M%C3%A9thodes_de_Runge-Kutta
 *
 */

#include "Integrators.hpp"

template<typename T>
class Euler: public FixedStepIntegrator<T>
{
	public:
		Euler(void):FixedStepIntegrator<T>(){};
		Euler(T step):FixedStepIntegrator<T>(step){};
		Euler(FixedStepIntegrator<T> &other):FixedStepIntegrator<T>(other){};

		void operator()(T &t, DynamicalSystem<T> &system);
};

template<typename T>
void Euler<T>::operator()(T &t, DynamicalSystem<T> &system)
{
	long i;

	system.f(t,system);

	for(i = 0; i < system.sizex(); ++i)
	{
		system[i] = system[i] + (this->step) * system.getdx(i);
	}

	t = t + this->step;

	system.h(t,system);
}

#endif
