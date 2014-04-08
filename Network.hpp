#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

/* Network.hpp
 *
 *	Permet de définir un réseau générique.
 *
 *	Adrien KERFOURN
 */

#include <vector>

#include "DynamicalSystem.hpp"


template<typename T>
class Network: public DynamicalSystem<T>
{
	protected:
		std::vector< LocalSystem<T>* > systems;

	public:
		Network(void):DynamicalSystem<T>(0,0){};
		virtual ~Network(void){};

		void add(LocalSystem<T>& system);

		virtual void f(T t, SystemStates<T>& x);
};

template<typename T>
inline void Network<T>::add(LocalSystem<T>& system)
{
	long nstates = this->sizex();
	long noutputs = this->sizey();

	this->systems.push_back(&system);
	nstates += system.sizex();
	noutputs += system.sizey();

	this->resize(nstates, noutputs);
	return;
}



template<typename T>
void Network<T>::f(T t, SystemStates<T>& x)
{
	SystemStates<T> localx;
	long idx = 0;
	long idy = 0;
	for(int i = 0; i < this->systems.size(); ++i)
	{
		this->systems[i]->localf(t, x, *this, idx, idy);
		idx += this->systems[i]->sizex();
		idy += this->systems[i]->sizey();
	}
	return;
}


#endif





















