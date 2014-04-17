#ifndef __ROSSLERCONNECTION_HPP__
#define __ROSSLERCONNECTION_HPP__

/* RosslerConnection
 *
 *	Adrien KERFOURN
 *
 */

#include "Connection.hpp"

template<typename T>
class RosslerConnection: public Connection<T>
{

	private:
		Network<T> *network;
		long i,j;
		T K;

	public:
		RosslerConnection(Network<T>& network, long i, long j, T gain);
		virtual ~RosslerConnection(void){};

		T operator()(void);
};

template<typename T>
RosslerConnection<T>::RosslerConnection(Network<T>& network, long i, long j, T gain)
{
	this->network = &network;
	this->i = i;
	this->j = j;
	this->K = gain;
	return;
}

template<typename T>
T RosslerConnection<T>::operator()(void)
{
	return K*( this->network->x(this->i) - this->network->x(this->j) );
}

#endif

