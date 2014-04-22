#ifndef __GAINCOUPLING_HPP__
#define __GAINCOUPLING_HPP__

/* 	GainCoupling.hpp
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
 */

#include "StatesCoupling.hpp"

template<typename T>
class GainCoupling: public StatesCoupling<T>
{
	public: typedef typename StatesCoupling<T>::size_type size_type;

	protected:
		T gain;

	public:
		GainCoupling(void):StatesCoupling<T>()
		{
			this->setGain((T)0.0);
			return;
		}
		GainCoupling(Network<T>& network, const T gain, const size_type from,const size_type to):StatesCoupling<T>(network,from,to)
		{
			this->setGain(gain);
			return;
		}
		GainCoupling(Network<T>& network, const T gain, const LocalSystem<T>& from, const LocalSystem<T>& to, const size_type statesoffset = 0):StatesCoupling<T>(network,from,to,stateoffset)
		{
			this->setGain(gain);
			return;
		}

		void setGain(const T gain);

		virtual T operator()(void);

}

template<typename T>
inline void GainCoupling<T>::setGain(const T gain)
{
	this->gain = gain;
	return;
}

template<typename T>
virtual T GainCoupling<T>::operator()(void)
{
	return (this->gain)*(network.x(this->from) - network.x(this->to));
}


#endif















