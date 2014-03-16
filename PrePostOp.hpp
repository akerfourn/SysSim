#ifndef __PREPOSTOP_HPP__
#define	__PREPOSTOP_HPP__

/*	PrePostOp.hpp
 *
 *		Permet de définir des opérations pré- et post-intégration (c'est-à-dire
 * des opérations exécutés juste avant l'appel de l'intégrateur ou exécutés
 * juste après l'appel de l'intégrateur).
 *
 *	Adrien KERFOURN
 *
 */

#include "Integrators.hpp"
#include "SystemStates.hpp"

template<typename T>
class PrePostOp
{
	public:
		PrePostOp(void){};
		virtual ~PrePostOp(){};

		virtual void operator()(Integrator<T>& integrator, SystemStates<T>& states) = 0;
};

/*	NoOp	(No Operation)
 *
 * 		Définition d'une opération (pré- ou post-intégration) qui ne fait rien.
 * Elle ne sert que pour éviter de rajouter des conditions encadrants les appels
 * aux opérations pré- et post-intégration.
 */
template<typename T>
class NoOp: public PrePostOp<T>
{
	public:
		void operator()(Integrator<T>& integrator, SystemStates<T>& states);
};

template<typename T>
inline void NoOp<T>::operator()(Integrator<T>& integrator, SystemStates<T>& states)
{
	return;
}


#endif
