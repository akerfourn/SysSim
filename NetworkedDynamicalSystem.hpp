#ifndef __NETWORKEDDYNAMICALSYSTEM_HPP__
#define __NETWORKEDDYNAMICALSYSTEM_HPP__

/* NetworkedDynamicalSystem
 *
 *	Réseau de systèmes dynamiques (les sous-systèmes ont la même équation
 * dynamique mais les paramètres peuvent varier en fonction de l'implémentation
 * de l'utilisation).
 *
 * Adrien KERFOURN
 *
 */

#include "DynamicalSystem.hpp"

template<typename T>
class NetworkedDynamicalSystem: public DynamicalSystem
{
	protected:
		long nstatesbysystem;
		long noutputbysystem;
		long nsystem;

	public:
		NetworkedDynamicalSystem(void):DynamicalSystem<T>()
		{
			this->nstatesbysystem = 0;
			this->noutputbysystem = 0;
			this->nsystem = 0;
		}
		NetworkedDynamicalSystem(long nsystem, long nstatesbysystem, long noutputbyssystem = 0):DynamicalSystem<T>(nsystem*nstatesbysystem, nsystem*noutputbysystem)
		{
			this->nstatesbysystem = nstatesbysystem;
			this->noutputbysystem = noutputbysystem;
			this->nsystem = nsystem;
		}
		virtual ~NetworkedDynamicalSystem(){};
	
		long getnsystem(void);
		long getnstatesbysystem(void);
		long getnoutputbysystem(void);

		void localf(T t, SystemStates<T> &state) = 0;
};

template<typename T>
void inline NetworkedDynamicalSystem<T>::getnsystem(void)
{
	return this->nsystem;
}

template<typename T>
void inline NetworkedDynamicalSystem<T>::getnstatesbysystem(void)
{
	return this->nstatesbysystem;
}

template<typename T>
void inline NetworkedDynamicalSystem<T>::getnoutputbysystem(void)
{
	return this->noutputbysystem;
}


#endif
