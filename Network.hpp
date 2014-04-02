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
class Network: public DynamicalSystem
{
	protected:
		std::vector< DynamicalSystem<T> > systems;
		long nstates;
		long noutputs;

	public:
		Network(void):DynamicalSystem<T>(0,0){};
		virtual ~Network(void){};

		void add(DynamicalSystem<T>& system);

		inline T &getx(const long index);
		inline T getx(const long index) const;
		inline T &gety(const long index);
		inline T gety(const long index) const;
		inline void setx(const long index, const T value);
		inline void sety(const long index, const T value);

		inline T &getdx(const long index);
		inline T getdx(const long index) const;
		inline void setdx(const long index, const T value);
}

template<typename T>
inline void Network<T>::add(DynamicalSystem<T>& system)
{
	this->systems.push_back(system);
	this->nstates += system.sizex();
	this->noutputs += system.sizey();
}

#endif





















