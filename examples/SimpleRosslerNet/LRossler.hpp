#ifndef __LROSSLER_HPP__
#define __LROSSLER_HPP__

/*	LRossler.hpp
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

#include "LocalSystem.hpp"

template<typename T>
class LRossler: public LocalSystem<T>
{
	protected:
		T a, b, c;

	public:
		using LocalSystem<T>::dx;
		using LocalSystem<T>::x;
		typedef typename LocalSystem<T>::size_type size_type;

		LRossler(void):LocalSystem<T>()
		{
			this->changeparameters( (T)0.432, (T)2.0, (T)4.0 );
			return;
		}
		LRossler(T a, T b, T c):LocalSystem<T>()
		{
			this->changeparameters(a, b, c);
			return;
		}

		inline void changeparameters(T a, T b, T c);

		virtual void localf(T t);

		virtual inline size_type sizex(void){return (size_type)3;};
		virtual inline size_type sizey(void){return (size_type)0;};

};


template<typename T>
inline void LRossler<T>::changeparameters(T a, T b, T c)
{
	this->a = a;
	this->b = b;
	this->c = c;
	return;
}


template<typename T>
void LRossler<T>::localf(T t)
{
	dx(0) = -x(1) - x(2);
	dx(1) = x(0) + a * x(1);
	dx(2) = b + x(2) * ( x(0) - c);

	for (int i = 0; i < this->sizen(); ++i)
	{
		dx(0) += this->get(i)();
	}
}


#endif

