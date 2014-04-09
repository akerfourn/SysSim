#ifndef __LROSSLER_HPP__
#define __LROSSLER_HPP__

#include "LocalSystem.hpp"

template<typename T>
class LRossler: public LocalSystem<T>
{
	protected:
		T a, b, c;

	public:
		LRossler(void);
		LRossler(T a, T b, T c);

		inline void changeparameters(T a, T b, T c);

		virtual void localf(T t, SystemStates<T>& x, DynamicalSystem<T>& network, long basex, long basey);

		virtual long sizex(void){return (long)3;};
		virtual long sizey(void){return (long)0;};

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
void LRossler<T>::localf(T t, SystemStates<T>& x, DynamicalSystem<T>& network, long basex, long basey)
{
	T u = 0;
	for (int i = 0; i < this->neighbors.size(); ++i)
	{
		u += this->get(i)();
	}
	network.getdx(basex) = -x[basex+1] - x[basex+2] + u;
	network.getdx(basex+1) = x[basex+0] + a * x[basex+1];
	network.getdx(basex+2) = b + x[basex+2] * ( x[basex+0] - c);
}


#endif

