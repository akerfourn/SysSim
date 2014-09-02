#ifndef __ROSSLER_HPP__
#define __ROSSLER_HPP__

/*	Rossler.hpp
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
 *
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
		using DynamicalSystem<T>::dx;	// Allow to use "dx(...)" instead of "this->dx(...)" in f function.
		T a, b, c;

	public:
		Rossler(void);
		Rossler(T a, T b, T c);
		virtual ~Rossler(void){};

		inline void changeparameters(T a, T b, T c);

		virtual void f(T t, Vector<T>& x);
};


template<typename T>
Rossler<T>::Rossler(void):DynamicalSystem<T>(3)
{
	this->changeparameters( (T)0.432, (T)2.0, (T)4.0 );
	this->x(0) = (T)0.0;
	this->x(1) = (T)0.0;
	this->x(2) = (T)0.0;
	return;
}

template<typename T>
Rossler<T>::Rossler(T a, T b, T c):DynamicalSystem<T>(3)
{
	this->changeparameters(a, b, c);
	this->x(0) = (T)0.0;
	this->x(1) = (T)0.0;
	this->x(2) = (T)0.0;
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
void Rossler<T>::f(T t, Vector<T>& x)
{
	dx(0) = -x[1] - x[2];
	dx(1) = x[0] + a * x[1];
	dx(2) = b + x[2] * ( x[0] - c);
	return;
}

#endif

