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
		std::vector< DynamicalSystem<T>* > systems;
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

		virtual void f(T t, SystemStates<T>& x);
};

template<typename T>
inline void Network<T>::add(DynamicalSystem<T>& system)
{
	this->systems.push_back(&system);
	this->nstates += system.sizex();
	this->noutputs += system.sizey();
	return;
}

template<typename T>
inline T& Network<T>::getx(long index)
{
	long idsystem = 0;
	while(index >= this->systems[idsystem]->sizex())
	{
		++idsystem;
		index = index - this->systems[idsystem]->sizex();
	}
	return this->systems[idsystem]->getx(index);	
}

template<typename T>
inline T& Network<T>::gety(long index)
{
	long idsystem = 0;
	while(index >= this->systems[idsystem]->sizey())
	{
		++idsystem;
		index = index - this->systems[idsystem]->sizey();
	}
	return this->systems[idsystem]->gety(index);	
}

template<typename T>
inline T& Network<T>::getdx(long index)
{
	long idsystem = 0;
	while(index >= this->systems[idsystem]->sizex())
	{
		++idsystem;
		index = index - this->systems[idsystem]->sizex();
	}
	return this->systems[idsystem]->getdx(index);	
}

template<typename T>
inline T Network<T>::getx(long index) const
{
	return this->Network<T>::getx(index);		// TODO Vérifier si nécessaire (je crains une récurcivité infinie sans ça)
}

template<typename T>
inline T Network<T>::gety(long index) const
{
	return this->gety(index);		// TODO Vérifier si nécessaire (je crains une récurcivité infinie sans ça)
}

template<typename T>
inline T Network<T>::getdx(long index) const
{
	return this->getdx(index);		// TODO Vérifier si nécessaire (je crains une récurcivité infinie sans ça)
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
		sizex += this->systems[i]->sizex();
	}
	return sizex;
}

template<typename T>
inline long Network<T>::sizey(void) const
{
	long sizey = 0;
	for(long i = 0; i < this->systems.size(); ++i)
	{
		sizey += this->systems[i]->sizey();
	}
	return sizey;
}

template<typename T>
void Network<T>::f(T t, SystemStates<T>& x)
{
	SystemStates<T> localx;
	long idx = 0;
	long idy = 0;
	for(int i = 0; i < this->systems.size(); ++i)
	{
		localx.resize(*this->systems[i]);
		for (long j = 0; j < this->systems[i]->sizex(); ++j)
		{
			localx.getx(j) = x.getx(idx);
			idx++;
		}
		for (long j = 0; j < this->systems[i]->sizey(); ++j)
		{
			localx.gety(j) = x.gety(idy);
			idy++;
		}
		this->systems[i]->f(t,localx);
	}
	return;
}


#endif





















