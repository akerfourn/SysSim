#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

/* Connection.hpp
 *
 *	Permet de définir des liens (couplage) avec un autre système. En créant des
 * classes dérivées, il est possible de stocker des informations supplémentaires
 * dans cette objet (variable de couplage, gain, etc.).
 * 
 *	Adrien KERFOURN
 */

#include "DynamicalSystem.hpp"

template<typename T>
class Connection
{
	protected:
		DynamicalSystem<T>* system;

	public:
		Connection(void){};
		Connection(DynamicalSystem<T> &system)
		{
			this->system = &system;
		};
		virtual ~Connection(void){};

		DynamicalSystem<T>& getSystem(void);
		inline DynamicalSystem<T>& operator()(void)
		{
			return this->getSystem();
		};
}

template<typename T>
inline DynamicalSystem<T>& Connection<T>::getSystem(void)
{
	return this->*system;
}


#endif

