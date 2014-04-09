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

template<typename T>
class Connection
{
	public:
		Connection(void){};
		virtual ~Connection(void){};

		virtual T operator()(void) = 0;
};



#endif

