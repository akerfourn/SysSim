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

		inline T &getx(long index);
		inline T getx(long index) const;
		inline T &gety(long index);
		inline T gety(long index) const;
		inline void setx(long index, const T value);
		inline void sety(long index, const T value);

		inline T &getdx(long index);
		inline T getdx(long index) const;
		inline void setdx(long index, const T value);

		inline long sizex(void) const;
		inline long sizey(void) const;
}

template<typename T>
inline void Network<T>::add(DynamicalSystem<T>& system)
{
	this->systems.push_back(system);
	this->nstates += system.sizex();
	this->noutputs += system.sizey();
}

template<typename T>
inline T& Network<T>::getx(long index)
{
	long idsystem = 0;
	while(index >= this->systems[idsystem].sizex())
	{
		++idsystem;
		index = index - this->systems[idsystem].sizex();
	}
	return this->systems[idsystem].getx(index);	
}

template<typename T>
inline T& Network<T>::gety(long index)
{
	long idsystem = 0;
	while(index >= this->systems[idsystem].sizey())
	{
		++idsystem;
		index = index - this->systems[idsystem].sizey();
	}
	return this->systems[idsystem].gety(index);	
}

template<typename T>
inline T& Network<T>::getdx(long index)
{
	long idsystem = 0;
	while(index >= this->systems[idsystem].sizedx())
	{
		++idsystem;
		index = index - this->systems[idsystem].sizedx();
	}
	return this->systems[idsystem].getdx(index);	
}

template<typename T>
inline T Network<T>::getx(long index)
{
	T& retval = this->getx(index);		// TODO Vérifier si nécessaire (je crains une récurcivité infinie sans ça)
	return retval;
}

template<typename T>
inline T Network<T>::gety(long index)
{
	T& retval = this->gety(index);		// TODO Vérifier si nécessaire (je crains une récurcivité infinie sans ça)
	return retval;
}

template<typename T>
inline T Network<T>::getdx(long index)
{
	T& retval = this->getdx(index);		// TODO Vérifier si nécessaire (je crains une récurcivité infinie sans ça)
	return retval;
}

template<typename T>
inline void Network<T>::setx(long index, const T value)
{
	this->getx(index) = value;
	return;
}

template<typename T>
inline void Network<T>::sety(long index, const T value)
{
	this->gety(index) = value;
	return;
}

template<typename T>
inline void Network<T>::setdx(long index, const T value)
{
	this->getdx(index) = value;
	return;
}

template<typename T>
inline long Network<T>::sizex(void) const
{
	long sizex = 0;
	for(long i = 0; i < this->systems.size(); ++i)
	{
		sizex += this->systems[i].sizex();
	}
	return sizex;
}

template<typename T>
inline long Network<T>::sizey(void) const
{
	long sizey = 0;
	for(long i = 0; i < this->systems.size(); ++i)
	{
		sizey += this->systems[i].sizey();
	}
	return sizey;
}


#endif





















