#ifndef __INTEGRATORS_HPP__
#define __INTEGRATORS_HPP__

/*	Integrators.hpp
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
 *	Adrien KERFOURN
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

		virtual void operator()(T &t, DynamicalSystem<T> &system) = 0;
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




#endif

