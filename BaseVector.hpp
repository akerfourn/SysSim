#ifndef __BASEVECTOR_HPP__
#define __BASEVECTOR_HPP__

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

#include "Vector.hpp"
#include "SubVector.hpp"


template<typename T>
class BaseVector: public Vector<T>
{
	public:
		typedef typename Vector<T>::size_type size_type;
	
	protected:

		std::vector<T> *data;
		
		inline void init(void);
		inline void init(const size_type size);
		inline void init(std::vector<T> &data);
		inline void init(BaseVector<T> &vector);
		
	public:
		
		BaseVector(void);
		BaseVector(const size_type size);
		BaseVector(std::vector<T> &data);
		BaseVector(BaseVector<T> &vector);
		virtual ~BaseVector();
		
		virtual std::vector<T>& getData(void);
		virtual void setData(std::vector<T> &data);
		
		virtual void copy(BaseVector<T> &vector);
		
		virtual size_type size(void) const;

		virtual void resize(const size_type size);
		virtual void resize(const Vector<T> &ref);
		
		virtual T &at(const size_type index);
		virtual T at(const size_type index) const;
		
		virtual T &operator[](const size_type index);
		virtual T operator[](const size_type index) const;
		
		virtual T &operator()(const size_type index);
		virtual T operator()(const size_type index) const;
		
		virtual SubVector<T> &operator()(const size_type begin, const size_type end);
		
		
	
		// TODO inline SystemStates& operator=(SystemStates<T> const &other);
		virtual bool operator==(Vector<T> const &other) const;	// TODO : Test !
		virtual bool operator!=(Vector<T> const &other) const;	// TODO : Test !
		
};

template<typename T>
inline void BaseVector<T>::init(void)
{
	this->data = new std::vector<T>();
	return;
}

template<typename T>
inline void BaseVector<T>::init(const size_type size)
{
	this->data = new std::vector<T>(size);
}

template<typename T>
inline void BaseVector<T>::init(std::vector<T> &data)
{
	this->data = &data;
}

template<typename T>
inline void BaseVector<T>::init(BaseVector<T> &vector)
{
	this->copy(vector);
}


template<typename T>
BaseVector<T>::BaseVector(void)
{
	this->init();
	return;
}

template<typename T>
BaseVector<T>::BaseVector(const size_type size)
{
	this->init(size);
	return;
}

template<typename T>
BaseVector<T>::BaseVector(std::vector<T> &data)
{
	this->init(data);
	return;
}

template<typename T>
BaseVector<T>::BaseVector(BaseVector<T> &vector)
{
	this->init(vector);
	return;
}

template<typename T>
BaseVector<T>::~BaseVector()
{
	delete this->data;
	return;
}


template<typename T>
std::vector<T>& BaseVector<T>::getData(void)
{
	return (*this->data);
}

template<typename T>
void BaseVector<T>::setData(std::vector<T> &data)
{
	this->data = &data;
	return;
}


template<typename T>
void BaseVector<T>::copy(BaseVector<T> &vector)
{
	if (this->data != NULL)
	{
		delete this->data;
	}
	this->data = new std::vector<T>(vector.getData());	// TODO Check that is a true copy (no reference to the other object)
}


template<typename T>
typename BaseVector<T>::size_type BaseVector<T>::size(void) const
{
	return this->data->size();
}

template<typename T>
void BaseVector<T>::resize(const size_type size)
{

	this->data->resize(size);
	return;
}

template<typename T>
void BaseVector<T>::resize(const Vector<T> &ref)
{
	this->resize(ref.size());
	return;
}


template<typename T>
T &BaseVector<T>::at(const size_type index)
{
	return this->data->at(index);
}
		
template<typename T>
T BaseVector<T>::at(const size_type index) const
{
	return this->data->at(index);
}



template<typename T>
T &BaseVector<T>::operator[](const size_type index)
{
	return (*this->data)[index];
}

template<typename T>
T BaseVector<T>::operator[](const size_type index) const
{
	return (*this->data)[index];
}

template<typename T>
T &BaseVector<T>::operator()(const size_type index)
{
	return (*this->data)[index];
}

template<typename T>
T BaseVector<T>::operator()(const size_type index) const
{
	return (*this->data)[index];
}


template<typename T>
SubVector<T> &BaseVector<T>::operator()(const size_type ibegin, const size_type iend)
{
		SubVector<T> *subvector = new SubVector<T>(*this, ibegin,iend);
		return *subvector;
}

		

template<typename T>
bool BaseVector<T>::operator==(Vector<T> const &other) const
{
	if ( this->size() != other.size() )
	{
		return false;
	}

	/* Checks each x (one by one) : */
	for(size_type i = 0; i < this->size(); ++i)
	{
		if (this->at(i) != other.at(i) ) return false;
	}

	return true;
}
		
template<typename T>
bool BaseVector<T>::operator!=(Vector<T> const &other) const
{
	return !(*this == other);
}

#endif
