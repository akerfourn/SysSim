#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

/* Network.hpp
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
 *	Permet de définir un réseau générique.
 *
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

	system.init(*this,nstates, noutputs);

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
	for(int i = 0; i < this->systems.size(); ++i)
	{
		this->systems[i]->setcx(x);
		this->systems[i]->localf(t);
		this->systems[i]->unsetcx();
	}
	return;
}


#endif





















