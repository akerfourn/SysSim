#ifndef __STATESCOUPLING_HPP__
#define __STATESCOUPLING_HPP__

/* 	StatesCoupling.hpp
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

#include "Connection.hpp"
#include "LocalSystem.hpp"

template<typename T>
class StatesCoupling: public Connection<T>
{
	public: typedef typename LocalSystem<T>::size_type size_type;

	protected:
		size_t from, to;

	public:
		StatesCoupling(void);
		StatesCoupling(const size_type from,const size_type to);
		StatesCoupling(const LocalSystem<T>& from, const LocalSystem<T>& to, const size_type statesoffset = 0);
		virtual ~StatesCoupling(void){};

		void setStates(const size_type from, const size_type to);
		void setStates(const LocalSystem<T>& from, const LocalSystem<T>& to, const size_type statesoffset = 0);
}

template<typename T>
StatesCoupling<T>::StatesCoupling(void)
{
	this->setStates((size_type)0, (size_type)0);
	return;
}

template<typename T>
StatesCoupling<T>::StatesCoupling(const size_type from, const size_type to)
{
	this->setStates(from, to);
	return;
}

template<typename T>
StatesCoupling<T>::StatesCoupling(const LocalSystem<T>& from, const LocalSystem<T>& to, const size_type statesoffset = 0)
{
	this->setStates(from, to, stateoffset);
	return;
}



template<typename T>
void StatesCoupling<T>::setStates(const size_type from, const size_type to)
{
	this->from = from;
	this->to = to;
	return;
}

template<typename T>
void StatesCoupling<T>::setStates(const LocalSystem<T>& from, const LocalSystem<T>& to, const size_type statesoffset = 0)
{
	this->from = from.getbasex() + statesoffset;
	this->to = to.getbasex() + statesoffset;
	return;
}















#endif



