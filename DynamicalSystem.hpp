#ifndef __DYNAMICALSYSTEM_HPP__
#define __DYNAMICALSYSTEM_HPP__

/*	DynamicalSystem.hpp
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
 * Adrien KERFOURN (2013)
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
		std::vector<T> dx;

	public:
		DynamicalSystem(void):SystemStates<T>(){};
		DynamicalSystem(const long nstates):SystemStates<T>(nstates)
		{
			dx.resize(nstates);
		};
		DynamicalSystem(const long nstates, const long noutput):SystemStates<T>(nstates,noutput)
		{
			dx.resize(nstates);
		};
		DynamicalSystem(SystemStates<T> &ref):SystemStates<T>(ref){};
		virtual ~DynamicalSystem(void){};

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

		inline T &getdx(const long index);
		inline T getdx(const long index) const;
		inline void setdx(const long index, const T value);

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
		this->getx(i) = xi[i];
	}
	return;
}

template<typename T>
void DynamicalSystem<T>::init(std::vector<T> &xi)
//FIXME : /!\ Aucune gestion d'erreur (alors que possible assez simplement).
{
	for(long i = 0; i < this->sizex(); ++i)
	{
		this->getx(i) = xi[i];
	}
	return;
}

template<typename T>
inline T &DynamicalSystem<T>::getdx(const long index)
{
	return this->dx[index];
}

template<typename T>
inline T DynamicalSystem<T>::getdx(const long index) const
{
	return this->dx[index];
}

template<typename T>
inline void DynamicalSystem<T>::setdx(const long index, const T value)
{
	this->dx[index] = value;
	return;
}


#endif

