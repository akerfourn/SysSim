#ifndef __ROSSLER_HPP__
#define __ROSSLER_HPP__

/*	Rossler.hpp
 *
 *		Définition du système de Rössler :
 * dx = - y - z
 * dy = x + a * y
 * dz = b + z * (x - c)
 *		où x, y et z représentent les 3 variables d'état du système et a, b et c
 * représente 3 paramètres du système.
 *
 * Voir : http://www.scholarpedia.org/article/Rossler_attractor
 *
 * Paramètres de simulation fonctionnels :
 *	- a = 0.432
 *	- b = 2
 *	- c = 4
 *
 * Conditions initiales fonctionnelles (pour les paramètres ci-dessus) :
 *	- xi = 0.0
 *	- yi = 0.0
 *	- zi = 0.0
 *
 * Le constructeur par défaut définit le système avec ces paramètres et ces
 * conditions initiales.
 *
 */

#include "DynamicalSystem.hpp"

template<typename T>
class Rossler: public DynamicalSystem<T>
{
	private:
		using DynamicalSystem<T>::dx;	// Allow to use "dx" instead of "this->dx" in f function.
		T a, b, c;

	public:
		Rossler(void);
		Rossler(T a, T b, T c);
		virtual ~Rossler(void){};

		inline void changeparameters(T a, T b, T c);

		virtual void f(T t, SystemStates<T>& x);
};


template<typename T>
Rossler<T>::Rossler(void):DynamicalSystem<T>(3)
{
	this->changeparameters( (T)0.432, (T)2.0, (T)4.0 );
	this->getx(0) = (T)0.0;
	this->getx(1) = (T)0.0;
	this->getx(2) = (T)0.0;
	return;
}

template<typename T>
Rossler<T>::Rossler(T a, T b, T c):DynamicalSystem<T>(3)
{
	this->changeparameters(a, b, c);
	this->getx(0) = (T)0.0;
	this->getx(1) = (T)0.0;
	this->getx(2) = (T)0.0;
	return;
}

template<typename T>
inline void Rossler<T>::changeparameters(T a, T b, T c)
{
	this->a = a;
	this->b = b;
	this->c = c;
	return;
}

template<typename T>
void Rossler<T>::f(T t, SystemStates<T>& x)
{
	dx[0] = -x[1] - x[2];
	dx[1] = x[0] + a * x[1];
	dx[2] = b + x[2] * ( x[0] - c);
	return;
}

#endif

