#ifndef __SUBVECTOR_HPP__
#define __SUBVECTOR_HPP__

#include "Vector.hpp"

template<typename T>
class SubVector: public Vector<T>
{	
	public:
		typedef typename Vector<T>::size_type size_type;
		
	protected:
		
		Vector<T> *vector;
		size_type begin, end;
		
		inline void init(void);
		inline void init(Vector<T> &base, size_type begin, size_type end);
		inline void init(Vector<T> *base, size_type begin, size_type end);
		inline void init(size_type begin, size_type end);
	
	public:
		
		SubVector(void);
		SubVector(size_type begin, size_type end);
		SubVector(Vector<T> &base, size_type begin, size_type end);
		SubVector(Vector<T> *base, size_type begin, size_type end);
		virtual ~SubVector();
		
		virtual size_type getBegin(void) const;
		virtual size_type getEnd(void) const;
		
		virtual Vector<T>& getVector(void);
		inline void setVector(Vector<T> &vector);
		virtual void setVector(Vector<T> *vector);
		
		virtual void copy(SubVector<T> &ref);
		
		virtual size_type sizeVector(void) const;
		virtual size_type size(void) const;

		virtual void resize(const size_type begin, const size_type end);
		virtual void resize(const SubVector<T> &ref);
		virtual void resize(const Vector<T> &ref);
		
		virtual T &at(const size_type index);
		virtual T at(const size_type index) const;
		
		virtual T &operator[](const size_type index);
		virtual T operator[](const size_type index) const;
		
		virtual T &operator()(const size_type index);
		virtual T operator()(const size_type index) const;
		
		virtual SubVector<T> &operator()(const size_type begin, const size_type end);
			
		// TODO inline SystemStates& operator=(SystemStates<T> const &other);
		virtual bool operator==(Vector<T> const &other) const;
		virtual bool operator!=(Vector<T> const &other) const;
		
};

template<typename T>
inline void SubVector<T>::init(void)
{
	this->vector = NULL;
	this->begin = (size_type)0;
	this->end = (size_type)0;
	return;
}

template<typename T>
inline void SubVector<T>::init(Vector<T> &base, size_type begin, size_type end)
{
	this->init(*base, begin,end);
	return;
}

template<typename T>
inline void SubVector<T>::init(Vector<T> *base, size_type begin, size_type end)
{
	this->init(begin, end);
	this->vector = base;
	return;
}

template<typename T>
inline void SubVector<T>::init(size_type begin, size_type end)
{
	this->init();
	this->begin = begin;
	this->end = end;
	return;
}


template<typename T>
SubVector<T>::SubVector(void)
{
	this->init();
	return;
}

template<typename T>
SubVector<T>::SubVector(size_type begin, size_type end)
{
	this->init(begin,end);
	return;
}

template<typename T>
SubVector<T>::SubVector(Vector<T> *base, size_type begin, size_type end)
{
	this->init(base,begin,end);
	return;
}

template<typename T>
SubVector<T>::SubVector(Vector<T> &base, size_type begin, size_type end)
{
	this->init(&base,begin,end);
	return;
}

template<typename T>
SubVector<T>::~SubVector()
{
	this->vector = NULL;
	return;
}


template<typename T>
typename SubVector<T>::size_type SubVector<T>::getBegin(void) const
{
	return this->begin;
}

template<typename T>
typename SubVector<T>::size_type SubVector<T>::getEnd(void) const
{
	return this->end;
}


template<typename T>
Vector<T>& SubVector<T>::getVector(void)
{
	return (*this->vector);
}

template<typename T>
inline void SubVector<T>::setVector(Vector<T> &vector)
{
	this->setVector(&vector);
	return;
}

template<typename T>
void SubVector<T>::setVector(Vector<T> *vector)
{
	this->vector = vector;
	return;
}


template<typename T>
void SubVector<T>::copy(SubVector<T> &ref)
{
	this->begin = ref.getBegin();
	this->end = ref.getEnd();
	this->vector = &ref.getVector();
	return;
}


template<typename T>
typename SubVector<T>::size_type SubVector<T>::sizeVector(void) const
{
	return this->vector->size();
}

template<typename T>
typename SubVector<T>::size_type SubVector<T>::size(void) const
{
	return this->end - this->begin;
}


template<typename T>
void SubVector<T>::resize(const size_type begin, const size_type end)
{
	// TODO tests !
	this->begin = begin;
	this->end = end;
	return;
}

template<typename T>
void SubVector<T>::resize(const SubVector<T> &ref)
{
	this->begin = ref.getBegin();
	this->end = ref.getEnd();
	return;
}

template<typename T>
void SubVector<T>::resize(const Vector<T> &ref)
{
	this->begin = (size_type)0;
	this->end = ref.size();
	return;
}


template<typename T>
T &SubVector<T>::at(const size_type index)
{
	return this->vector->at(index+this->begin);
}

template<typename T>
T SubVector<T>::at(const size_type index) const
{
	return this->vector->at(index+this->begin);
}


template<typename T>
T &SubVector<T>::operator[](const size_type index)
{
	return (*this->vector)[index+this->begin];
}

template<typename T>
T SubVector<T>::operator[](const size_type index) const
{
	return (*this->vector)[index+this->begin];
}


template<typename T>
T &SubVector<T>::operator()(const size_type index)
{
	return (*this->vector)[index+this->begin];
}

template<typename T>
T SubVector<T>::operator()(const size_type index) const
{
	return (*this->vector)[index+this->begin];
}


template<typename T>
SubVector<T> &SubVector<T>::operator()(const size_type begin, const size_type end)
{
	// TODO test limits
	SubVector<T> *subvector = new SubVector(*this,begin,end);
	return *subvector;
}


template<typename T>
bool SubVector<T>::operator==(Vector<T> const &other) const
{
	if (this->size() != other.size())
	{
		return false;
	}
	
	for (size_type i = (size_type)0; i < other.size(); ++i)
	{
		if (this->at(i) != other.at(i)) return false;
	}
	
	return true;
}

template<typename T>
bool SubVector<T>::operator!=(Vector<T> const &other) const
{
	return !(*this==other);
}






#endif
