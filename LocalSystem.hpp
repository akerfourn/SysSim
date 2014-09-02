#ifndef __LOCALSYSTEM_HPP__
#define __LOCALSYSTEM_HPP__

/* LocalSystem.hpp
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
 *		Permet de définir un système local dans un réseau. Sont intérêt est de
 * définir un certain nombre de voisin connecté au système (pour couplage).
 *
 */

#include <vector>
#include <stdexcept>

#include "Vector.hpp"
#include "DynamicalSystem.hpp"
#include "Connection.hpp"

template<typename T>
class LocalSystem
{
	public: typedef typename std::vector<T>::size_type size_type;

	protected:

		std::vector< Connection<T>* > neighbors;

		Vector<T> *currentx;

		DynamicalSystem<T> *network;
		size_type basex;
		size_type basey;

		Connection<T>& get(const size_type i);

	public:

		LocalSystem(void);
		LocalSystem(DynamicalSystem<T>& network, const size_type basex, const size_type basey);
		virtual ~LocalSystem(void){};

		inline void init(DynamicalSystem<T>& network, const size_type basex, const size_type basey);
		inline void init();

		inline void rebase(const size_type basex, const size_type basey);

		void add(Connection<T>& connection);


		inline T &x(const size_type index);
		inline T x(const size_type index) const;

		inline T &dx(const size_type index);
		inline T dx(const size_type index) const;

		inline T &y(const size_type index);
		inline T y(const size_type index) const; 

		virtual void localf(T t) = 0;

		inline size_type sizen(void) const;

		virtual size_type sizex(void) = 0;
		virtual size_type sizey(void) = 0;

		inline void setcx(Vector<T> &x);
		inline void unsetcx(void);

		inline size_type getbasex(void) const;
		inline size_type getbasey(void) const;
};

template<typename T>
LocalSystem<T>::LocalSystem(void)
{
	this->init();
	return;
}

template<typename T>
LocalSystem<T>::LocalSystem(DynamicalSystem<T>& network, const size_type basex, const size_type basey = 0)
{
	this->init(network,basex,basey);
	return;
}

template<typename T>
inline void LocalSystem<T>::init(DynamicalSystem<T>& network, const size_type basex, const size_type basey = 0)
{
	this->currentx = NULL;
	this->network = &network;
	this->basex = basex;
	this->basey = basey;
	return;
}

template<typename T>
inline void LocalSystem<T>::init()
{
	this->currentx = NULL;
	this->network = NULL;
	this->basex = 0;
	this->basey = 0;
	return;
}

template<typename T>
inline void LocalSystem<T>::rebase(const size_type basex, const size_type basey = 0)
{
	this->basex = basex;
	this->basey = basey;
}



template<typename T>
inline T& LocalSystem<T>::x(const size_type index)
{
	if ( (index < 0) || (index >= this->sizex()) )
	{
		throw std::out_of_range("LocalSystem::x");
	}
	return this->currentx->at(this->basex+index);
}

template<typename T>
inline T LocalSystem<T>::x(const size_type index) const
{
	if ( (index < 0) || (index >= this->sizex()) )
	{
		throw std::out_of_range("LocalSystem::x");
	}
	return this->currentx->at(this->basex+index);
}

template<typename T>
inline T& LocalSystem<T>::dx(const size_type index)
{
	if ( (index < 0) || (index >= this->sizex()) )
	{
		throw std::out_of_range("LocalSystem::dx");
	}
	return this->network->dx(this->basex+index);
}

template<typename T>
inline T LocalSystem<T>::dx(const size_type index) const
{
	if ( (index < 0) || (index >= this->sizex()) )
	{
		throw std::out_of_range("LocalSystem::dx");
	}
	return this->network->dx(this->basex+index);
}

template<typename T>
inline T& LocalSystem<T>::y(const size_type index)
{
	if ( (index < 0) || (index >= this->sizey()) )
	{
		throw std::out_of_range("LocalSystem::y");
	}
	return this->network->y(this->basey+index);
}

template<typename T>
inline T LocalSystem<T>::y(const size_type index) const
{
	if ( (index < 0) || (index >= this->sizey()) )
	{
		throw std::out_of_range("LocalSystem::y");
	}
	return this->network->y(this->basey+index);
}



template<typename T>
inline Connection<T>& LocalSystem<T>::get(const size_type i)
{
	return *this->neighbors[i];
}

template<typename T>
inline void LocalSystem<T>::add(Connection<T>& connection)
{
	this->neighbors.push_back(&connection);
	return;
}

template<typename T>
inline typename LocalSystem<T>::size_type LocalSystem<T>::sizen(void) const
{
	return this->neighbors.size();
}

template<typename T>
inline void LocalSystem<T>::setcx(Vector<T> &x)
{
	this->currentx = &x;
	return;
}

template<typename T>
inline void LocalSystem<T>::unsetcx(void)
{
	this->currentx = NULL;
	return;
}

template<typename T>
inline typename LocalSystem<T>::size_type LocalSystem<T>::getbasex(void) const
{
	return this->basex;
}

template<typename T>
inline typename LocalSystem<T>::size_type LocalSystem<T>::getbasey(void) const
{
	return this->basey;
}

#endif

