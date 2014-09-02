#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

/* Vector.hpp
 * 
 * Copyright Adrien KERFOURN (2014)
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
 * 		TODO : Description
 * 
 */


#include <vector>

template<typename T>
class SubVector;


template<typename T>
class Vector
{	
	public:
		typedef typename std::vector<T>::size_type size_type;
		
		virtual size_type size(void) const = 0;

		virtual void resize(const Vector<T> &ref) = 0;
		
		virtual T &at(const size_type index) = 0;
		virtual T at(const size_type index) const = 0;
		
		virtual T &operator[](const size_type index) = 0;
		virtual T operator[](const size_type index) const = 0;
		
		virtual T &operator()(const size_type index) = 0;
		virtual T operator()(const size_type index) const = 0;
		
		virtual SubVector<T> &operator()(const size_type begin, const size_type end) = 0;
			
		// TODO inline SystemStates& operator=(SystemStates<T> const &other);
		virtual bool operator==(Vector<T> const &other) const = 0;
		virtual bool operator!=(Vector<T> const &other) const = 0;
		
};

#include "SubVector.hpp"
#include "BaseVector.hpp"


#endif
