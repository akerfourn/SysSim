#ifndef __RUNGEKUTTA4_HPP__
#define __RUNGEKUTTA4_HPP__

/* 
 * Méthode Runge-Kutta 4 :
 *
 *	Implémente la méthode d'écrite sur l'article : http://fr.wikipedia.org/wiki/M%C3%A9thodes_de_Runge-Kutta
 *
 */

#include "Integrators.hpp"

template<typename T>
class RungeKutta4: public FixedStepIntegrator<T>
{
	protected:

		SystemStates<T> k1,k2,k3,tmp;

	public:
		RungeKutta4(void):FixedStepIntegrator<T>(){};
		RungeKutta4(T step):FixedStepIntegrator<T>(step){};
		RungeKutta4(FixedStepIntegrator<T> &other):FixedStepIntegrator<T>(other){};

		void operator()(T &t, DynamicalSystem<T> &system);
};

template<typename T>
void RungeKutta4<T>::operator()(T &t, DynamicalSystem<T> &system)
{
	long i;

	k1.resize(system.sizex());
	k2.resize(system.sizex());
	k3.resize(system.sizex());	

	tmp.resize(system.sizex());

	system.f(t, system);

	for (i = 0; i < system.sizex(); ++i)
	{
		k1[i] = system.getdx(i);
		tmp[i] = system[i] + ( this->step / ((T)2.0) ) * k1[i];
	}

	system.f(t + ( this->step / ((T)2.0) ), tmp);

	for (i = 0; i < system.sizex(); ++i)
	{
		k2[i] = system.getdx(i);
		tmp[i] = system[i] + ( this->step / ((T)2.0) ) * k2[i];
	}

	system.f(t + ( this->step / ((T)2.0) ), tmp);
	
	for (i = 0; i < system.sizex(); ++i)
	{
		k3[i] = system.getdx(i);
		tmp[i] = system[i] + this->step * k3[i];
	}

	system.f(t + this->step, tmp);

	for (i = 0; i < system.sizex(); ++i)
	{
		system[i] = system[i] + ( this->step / ((T)6.0) ) * ( k1[i] + ((T)2.0) * k2[i] + ((T)2.0) * k3[i] + system.getdx(i) );
	}

	t = t + this->step;

	return;
}


#endif

