#ifndef __LOCALSYSTEM_HPP__
#define __LOCALSYSTEM_HPP__

/* LocalSystem.hpp
 *
 *		Permet de définir un système local dans un réseau. Sont intérêt est de
 * définir un certain nombre de voisin connecté au système (pour couplage).
 *
 *	Adrien KERFOURN
 */

#include <vector>

#include "SystemStates.hpp"
#include "DynamicalSystem.hpp"
#include "Connection.hpp"

template<typename T>
class LocalSystem
{
	protected:
		std::vector< Connection<T>* > neighbors;

		Connection<T>& get(long i);

	public:
		LocalSystem(void);
		virtual ~LocalSystem(void){};

		void add(Connection<T>& connection);

		virtual void localf(T t, SystemStates<T>& x, DynamicalSystem<T>& network, long basex, long basey) = 0;

		virtual long sizex(void) = 0;
		virtual long sizey(void) = 0;
};

template<typename T>
LocalSystem<T>::LocalSystem(void)
{
	return;
}

template<typename T>
inline Connection<T>& LocalSystem<T>::get(long i)
{
	return *this->neighbors[i];
}

template<typename T>
inline void LocalSystem<T>::add(Connection<T>& connection)
{
	this->neighbors.push_back(&connection);
	return;
}



#endif

