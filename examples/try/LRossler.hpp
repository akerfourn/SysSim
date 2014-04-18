#ifndef __LROSSLER_HPP__
#define __LROSSLER_HPP__

/*	LRossler
 *
 * Adrien KERFOURN
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
		using typename LocalSystem<T>::size_type;

		LRossler(void);
		LRossler(T a, T b, T c);

		inline void changeparameters(T a, T b, T c);

		virtual void localf(T t);

		virtual size_type sizex(void){return (size_type)3;};
		virtual size_type sizey(void){return (size_type)0;};

};

template<typename T>
LRossler<T>::LRossler(void)
{
	this->changeparameters( (T)0.432, (T)2.0, (T)4.0 );
	return;
}

template<typename T>
LRossler<T>::LRossler(T a, T b, T c)
{
	this->changeparameters(a, b, c);
	return;
}


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

	T u = 0;
	for (int i = 0; i < this->sizen(); ++i)
	{
		u += this->get(i)();
	}

	dx(0) = -x(1) - x(2) + u;
	dx(1) = x(0) + a * x(1);
	dx(2) = b + x(2) * ( x(0) - c);
}


#endif

