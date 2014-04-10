#ifndef __RUNGEKUTTA4_HPP__
#define __RUNGEKUTTA4_HPP__

/* 	RungeKutta4.hpp
 *
 * Copyright Adrien KERFOURN (2014)
 *
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 * 
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 *
 *
 *
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

	tmp.resize(system.sizex(), system.sizey());

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

