#ifndef __INTEGRATORS_HPP__
#define __INTEGRATORS_HPP__

/*	Integrators.hpp
 *
 *		Définitions de foncteurs implémentant l'interface Integrator. Cela
 * permet de définir différente méthodes d'intégration tout en gardant une
 * utilisation générique.
 *		L'utilisation de foncteurs et non de fonctions permet d'utiliser
 * n'importe quelle méthode d'intégration de manière transparente en la passant
 * en paramètre de la fonction (ou méthode) réalisant la simulation.
 *
 *		Méthodes d'intégration disponibles :
 *			- Runge-Kutta 4
 *
 * TODO FIXME Il est possible que le retour de référence soit inutile. À voir si
 * une classe générant des diagrammes de bifurcations peut le faire élégamment
 * sans ce retour.
 *		Il serait peut-être judicieux de remplacer le paramètre "T t" par du
 * "T &t" pour le l'intégrateur incrémente lui-même le temps (utile pour des
 * méthode à pas variable).
 *		Il faut donc peut-être déporter l'argument "pas" dans les attributs
 * de la classe (des méthodes à pas variables définisant d'autres critères
 * d'évolutions).
 */

#include "DynamicalSystem.hpp"
#include "SystemStates.hpp"

#include <iostream>

template<typename T>
class Integrator
{
	public:
		virtual ~Integrator(void){};

		virtual SystemStates<T>& operator()(T &t, DynamicalSystem<T> &system) = 0;
};



template<typename T>
class FixedStepIntegrator: public Integrator<T>
{
	protected:
		T step;

	public:
		FixedStepIntegrator(void);
		FixedStepIntegrator(T step);
		FixedStepIntegrator(FixedStepIntegrator<T> &other);
		virtual ~FixedStepIntegrator(void){};

		inline T &getstep(void);
		inline void setstep(T newstep);
		inline void setstep(FixedStepIntegrator<T> &other);
};

template<typename T>
FixedStepIntegrator<T>::FixedStepIntegrator(void)
{
	this->setstep( (T)0.0 );
	return;
}

template<typename T>
FixedStepIntegrator<T>::FixedStepIntegrator(T step)
{
	this->setstep( (T)step );
	return;
}

template<typename T>
FixedStepIntegrator<T>::FixedStepIntegrator(FixedStepIntegrator<T> &other)
{
	this->setstep(other);
	return;
}



template<typename T>
inline T& FixedStepIntegrator<T>::getstep(void)
{
	return this->step;
}

template<typename T>
inline void FixedStepIntegrator<T>::setstep(T step)
/* TODO
 *		Vérifier que "step" est bien un nombre possitif et renvoyer une
 * exception sinon.
 */
{
	this->step = step;
	return;
}

template<typename T>
inline void FixedStepIntegrator<T>::setstep(FixedStepIntegrator<T> &other)
{
	this->setstep( other.getstep() );
	return;
}


/* 
 * Méthode Runge-Kutta 4 :
 *
 *	Implémente la méthode d'écrite sur l'article : http://fr.wikipedia.org/wiki/M%C3%A9thodes_de_Runge-Kutta
 *
 */

template<typename T>
class RungeKutta4: public FixedStepIntegrator<T>
{
	public:
		RungeKutta4(void):FixedStepIntegrator<T>(){};
		RungeKutta4(T step):FixedStepIntegrator<T>(step){};
		RungeKutta4(FixedStepIntegrator<T> &other):FixedStepIntegrator<T>(other){};

		SystemStates<T>& operator()(T &t, DynamicalSystem<T> &system);
};

template<typename T>
SystemStates<T>& RungeKutta4<T>::operator()(T &t, DynamicalSystem<T> &system)
{
	SystemStates<T> *k1 = NULL, *k2 = NULL, *k3 = NULL, *k4 = NULL;
	SystemStates<T> *out = new SystemStates<T>(system);
	SystemStates<T> tmp(system);
	long i;

	tmp.resize(system);

	k1 = &system.f(t, system);

	for (i = 0; i < system.sizey(); ++i)
	{
		(*out)(i) = (*k1)(i);
		tmp(i) = system(i);
	}

	for (i = 0; i < system.sizex(); ++i)
	{
		tmp[i] = system[i] + ( this->step / ((T)2.0) ) * (*k1)[i];
	}

	k2 = &system.f(t + ( this->step / ((T)2.0) ), tmp);

	for (i = 0; i < system.sizex(); ++i)
	{
		tmp[i] = system[i] + ( this->step / ((T)2.0) ) * (*k2)[i];
	}

	k3 = &system.f(t + ( this->step / ((T)2.0) ), tmp);
	
	for (i = 0; i < system.sizex(); ++i)
	{
		tmp[i] = system[i] + this->step * (*k3)[i];
	}

	k4 = &system.f(t + this->step, tmp);

	for (i = 0; i < system.sizex(); ++i)
	{
		(*out)[i] = system[i] + ( this->step / ((T)6.0) ) * ( (*k1)[i] + ((T)2.0) * (*k2)[i] + ((T)2.0) * (*k3)[i] + (*k4)[i] );
		system[i] = (*out)[i];
	}

	for (i = 0; i < system.sizey(); ++i)
    {
        (*out)(i) = (*k4)(i);
        system(i) = (*out)(i);
    }

	delete k1;
	delete k2;
	delete k3;
	delete k4;

	t = t + this->step;

	return (*out);
}






























#endif

