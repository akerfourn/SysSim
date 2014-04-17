#ifndef __DYNAMICALSYSTEM_HPP__
#define __DYNAMICALSYSTEM_HPP__

/*	DynamicalSystem.hpp
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
 *		Fournit une class abstraite définissant un système dynamique. Un système
 * dynamique est définit comme ayant un vecteur de variables d'état "x", un 
 * vecteur de variables de sortie "y" ainsi que la définition d'une dynamique
 * (donnée par la fonction "f" qui donne la dérivée des états du système en
 * fonction de ceux-ci et d'un certain nombre de paramètre intrinsèque au
 * système à définir).
 *		Cette classe est abstraite et ne sert que de base à la définition d'un
 * système. Ainsi pour définir un système l'implémentation minimal consiste en
 * la définition d'une classe héritant de DynamicalSystem et définissant la
 * fonction "f".
 *
 * * NOTE 1 : La fonction "f" doit créer un objet de type SystemState contenant,
 * a minima, les dérivées des états (et donc, si possible, aussi les sorties).
 * Le choix de la création d'un objet plutôt que l'utilisation d'un attribut
 * s'explique par l'utilisation de méthode d'intégration d'ordre supérieur à
 * un (tel que le Runge-Kutta 4, par exemple). Dans ces méthodes, on effectue
 * une synthèse de plusieurs estimations de la dérivé du système : l'utilisation
 * d'un attribut aurait donc nécessité des copies d'objets couteuses en temps
 * d'execution.
 *
 * * NOTE 2 : Voir "Rossler.hpp" pour un exemple d'implémentation.
 *
 */

/* FIXME
 *	Dans la fonction "f" le temps est de type "T". Le problème étant qu'il n'est
 * alors pas possible d'avoir un temps non-entier pour un vecteur d'état
 * d'entier.
 * Une solution est d'utiliser des doubles. Néanmoins il pourrait exister des
 * particulier où l'on voudrait des temps très long ou très précis (et
 * utilisant dans ce cadre un type particulier sans relation avec le type des
 * états).
 * Une autre solution et d'utiliser un template avec un second type. Le problème
 * et alors qu'on complexifie fortement l'utilisation de la classe dans le cas
 * général pour un comportement très particulier.
 * Peut-être que l'on peut par héritage avoir une classe d'utilisation plus
 * simple, par exemple :
 *		template<typename T, typename U> class A {...};
 *		template<typename T> class B: public class A {};
 * où le contenu de la classe B est absolument vide ?
 */

#include <vector>

#include "SystemStates.hpp"

template<typename T>
class DynamicalSystem: public SystemStates<T>
{
	protected:
		std::vector<T> mdx;
		std::vector<T> my;

	public:
		DynamicalSystem(void):SystemStates<T>(){};
		DynamicalSystem(const long nstates):SystemStates<T>(nstates)
		{
			this->mdx.resize(nstates);
		};
		DynamicalSystem(const long nstates, const long noutput):SystemStates<T>(nstates)
		{
			this->mdx.resize(nstates);
			this->my.resize(noutput);
		};
		DynamicalSystem(SystemStates<T> &ref):SystemStates<T>(ref){};
		virtual ~DynamicalSystem(void){};

		virtual inline void resize(const long nbstates, const long nboutput);

		/* La fonction "f" définie la dynamique du système en fonction du temps
		 * "t" et d'un vecteur d'état "state".
		 */
		virtual void f(T t, SystemStates<T>& state) = 0;
		virtual inline void f(T t);

		virtual void h(T t, SystemStates<T>& state);
		virtual inline void h(T t);

		virtual inline void init(SystemStates<T> &xi);
		virtual void init(T xi[]);
		virtual void init(std::vector<T> &xi);

		virtual inline T &getdx(const long index);
		virtual inline T getdx(const long index) const;
		virtual inline void setdx(const long index, const T value);

		virtual inline T &gety(const long index);
		virtual inline T gety(const long index) const;

		inline T &y(const long index);
		inline T y(const long index) const;

		inline T &dx(const long index);
		inline T dx(const long index) const;

		inline T &x(const long index);
		inline T x(const long index) const;

		virtual inline long sizex(void) const;
		virtual inline long sizedx(void) const;
		virtual inline long sizey(void) const;

};




template<typename T>
inline void DynamicalSystem<T>::f(T t)
{
	this->f(t,*this);
	return;
}



template<typename T>
void DynamicalSystem<T>::h(T t, SystemStates<T>& state)
{
	return;
}

template<typename T>
inline void DynamicalSystem<T>::h(T t)
{
	this->h(t,*this);
	return;
}




template<typename T>
inline void DynamicalSystem<T>::resize(long nbstates, long nboutput)
{
	SystemStates<T>::resize(nbstates);
	this->mdx.resize(nbstates);
	this->my.resize(nboutput);

	return;
}




template<typename T>
inline void DynamicalSystem<T>::init(SystemStates<T> &xi)
{
	this->copy(xi);
	return;
}

template<typename T>
void DynamicalSystem<T>::init(T xi[])
{
	for(long i = 0; i < this->sizex(); ++i)
	{
		this->at(i) = xi[i];
	}
	return;
}

template<typename T>
void DynamicalSystem<T>::init(std::vector<T> &xi)
//FIXME : /!\ Aucune gestion d'erreur (alors que possible assez simplement).
{
	for(long i = 0; i < this->sizex(); ++i)
	{
		this->at(i) = xi[i];
	}
	return;
}

template<typename T>
inline T &DynamicalSystem<T>::getdx(const long index)
{
	return this->mdx[index];
}

template<typename T>
inline T DynamicalSystem<T>::getdx(const long index) const
{
	return this->mdx[index];
}

template<typename T>
inline void DynamicalSystem<T>::setdx(const long index, const T value)
{
	this->mdx[index] = value;
	return;
}

template<typename T>
inline T &DynamicalSystem<T>::gety(const long index)
{
	return this->my[index];
}

template<typename T>
inline T DynamicalSystem<T>::gety(const long index) const
{
	return this->my[index];
}



template<typename T>
inline T& DynamicalSystem<T>::y(const long index)
{
	return this->my[index];
}

template<typename T>
inline T DynamicalSystem<T>::y(const long index) const
{
	return this->my[index];
}

template<typename T>
inline T& DynamicalSystem<T>::dx(const long index)
{
	return this->mdx[index];
}

template<typename T>
inline T DynamicalSystem<T>::dx(const long index) const
{
	return this->mdx[index];
}

template<typename T>
inline T& DynamicalSystem<T>::x(const long index)
{
	return this->at(index);
}

template<typename T>
inline T DynamicalSystem<T>::x(const long index) const
{
	return this->at(index);
}

template<typename T>
inline long DynamicalSystem<T>::sizex(void) const
{
	return this->size();
}

template<typename T>
inline long DynamicalSystem<T>::sizedx(void) const
{
	return (long)this->mdx.size();
}

template<typename T>
inline long DynamicalSystem<T>::sizey(void) const
{
	return (long)this->my.size();
}

#endif

