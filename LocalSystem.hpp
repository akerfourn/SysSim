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

#include "DynamicalSystem.hpp"
#include "Connection.hpp"

template<typename T>
class LocalSystem: public DynicalSystem<T>
{
	protected:
		std::vector< Connection<T> > neighbors;
}


#endif

