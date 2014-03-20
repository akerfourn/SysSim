#ifndef __MATRIXNETWORK_HPP__
#define __MATRIXNETWORK_HPP__

/* MatrixNetwork
 *
 *
 *
 * 
 *	Adrien KERFOURN
 *
 */

#include <vector>

#include "NetworkedDynamicalSystem.hpp"

template<typename T>
class MatrixNetwork: public NetworkedDynamicalSystem<T>
{

	protected:
		std::vector<unsigned int> currentposition;
		std::vector<unsigned int> sizes;
		long ndimension;

		long nextposition(void);

	public:
		MatrixNetwork(void):NetworkedDynamicalSystem<T>()
		{
			this->dimension = 0;
		}
		MatrixNetwork(std::vector sizes, long nstatesbysystem, long noutputbysystem);

		std::vector<unsigned int>& getsizes(void);
		long getndimension(void);
		long getindex(std::vector<unsigned int> &position);
		long getindex(void);

}

template<typename T>
long MatrixNetwork<T>::nextposition(void)
{
	this->currentposition[0]++;
	long i = 0;
	for(; i < this.currentposition.size()-1; ++i)
	{
		if (this->currentposition[i] >= this->sizes[i])
		{
			this->currentposition[i] = 0;
			this->currentposition[i+1]++;
		}
		else
		{
			return this->getindex();
		}
	}
	if (this->currentposition[i] >= this->sizes[i])
	{
		this->currentposition[i] = 0;
	}
	return this->getindex();
}

template<typename T>
MatrixNetwork::MatrixNetwork(std::vector sizes, long nstatesbysystem, long noutputbysystem)
{
	long nsystems = 0;
	this->ndimension = sizes.size();
	this->sizes.resize(this->ndimension);
	this->currentposition.resize(this->ndimension);
	for (long i = 0; i < sizes.size(); ++i)
	{
		nsystems += sizes[i];
		this.sizes[i] = sizes[i];
		this.currentposition[i] = sizes[i]-1;
	}
	this.resize(nsystems, nstatesbysystem, noutputbysystem);
	return;		
}

template<typename T>
std::vector<unsigned int>& inline MatrixNetwork<T>::getsizes(void)
{
	return this->sizes;
}

template<typename T>
long inline MatrixNetwork<T>::getndimension(void)
{
	return this->ndimension;
}

template<typename T>
long inline MatrixNetwork<T>::getindex(std::vector<unsigned int> &position)
{
	// TODO Gestion des dépassements limite (erreur ou bouclage ? faire une fonction / cas ?)
	long index = 0;
	for(long i = 0; i < position.size()-1; ++i)
	{
		index += position[i]*this->sizes[i];
	}
	index += position[position.size()-1];
	return index*this->nsystems;
}

template<typename T>
long inline MatrixNetwork<T>::getindex(void)
{
	return this->getindex(this->currentposition);
}




















#endif

