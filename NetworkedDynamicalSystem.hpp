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
class NetworkedDynamicalSystem: public DynamicalSystem<T>
{
	protected:
		long nstatesbysystem;
		long noutputbysystem;
		long nsystems;

	public:
		NetworkedDynamicalSystem(void):DynamicalSystem<T>()
		{
			this->nstatesbysystem = 0;
			this->noutputbysystem = 0;
			this->nsystems = 0;
		}
		NetworkedDynamicalSystem(long nsystems, long nstatesbysystem, long noutputbyssystem = 0):DynamicalSystem<T>(nsystems*nstatesbysystem, nsystems*noutputbysystem)
		{
			this->nstatesbysystem = nstatesbysystem;
			this->noutputbysystem = noutputbysystem;
			this->nsystems = nsystems;
		}
		virtual ~NetworkedDynamicalSystem(){};

		virtual inline void resize(long nsystems, long nstatesbysystem, long noutputbyssystem = 0);
	
		long getnsystems(void);
		long getnstatesbysystem(void);
		long getnoutputbysystem(void);

		void localf(T t, SystemStates<T> &state) = 0;
};


template<typename T>
void inline NetworkedDynamicalSystem<T>::resize(long nsystems, long nstatesbysystem, long noutputbyssystem = 0)
{
	this->nstatesbysystem = nstatesbysystem;
	this->noutputbysystem = noutputbysystem;
	this->nsystems = nsystems;

	this->resize(nsystems*nstatesbysystem, nsystems*noutputbysystem);
}



template<typename T>
void inline NetworkedDynamicalSystem<T>::getnsystems(void)
{
	return this->nsystems;
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
