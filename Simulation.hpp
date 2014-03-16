#ifndef __SIMULATION_HPP__
#define __SIMULATION_HPP__

/*	Simulation.hpp
 *
 *		Définit les paramètres de simulation et l'exécute. Le système ainsi que
 * l'intégrateur son des objets externes qui dérivent respectivement de
 * DynamicalSystem et Integrator.
 *
 * Adrien KERFOURN
 */

/* TODO
 *	Faire gestion des erreurs. Il faut lancer des exceptions lorsque l'on essaye
 * de faire un "run" alors le système ou l'intégrateur n'ont pas été défini.
 */

#include <iostream>
#include <sstream>
#include <string>

#include "DynamicalSystem.hpp"
#include "Integrators.hpp"
#include "PrePostOp.hpp"

template<typename T>
class Simulation
{
	protected:
		DynamicalSystem<T> *dynamicalsystem;
		Integrator<T> *integrator;

		PrePostOp<T> *preop;
		PrePostOp<T> *postop;

		long WSmax, WScount;	// writingstep

		inline void initprepostop(void);

	public:
		Simulation(void);
		Simulation(DynamicalSystem<T> &dynamicalsystem);
		Simulation(Integrator<T> &integrator);
		Simulation(DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator);
		virtual ~Simulation(void){};

		inline void writingstep(long ws);
		inline void writingstep(void);

		inline DynamicalSystem<T> &getdynamicalsystem();
		inline Integrator<T> &getintegrator();
		inline void setdynamicalsystem(DynamicalSystem<T> &dynamicalsystem);
		inline void setintegrator(Integrator<T> &integrator);
		inline void unsetdynamicalsystem(void);
		inline void unsetintegrator(void);

		inline PrePostOp<T> &getpreop();
		inline PrePostOp<T> &getpostop();
		inline void setpreop(PrePostOp<T> &preop);
		inline void setpostop(PrePostOp<T> &postop);
		inline void unsetpreop(void);
		inline void unsetpostop(void);

		void run(std::ostream &ostream, T ti, T tf, T tisim);
		inline void run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, T tisim);
		inline void run(std::ostream &ostream, T ti, T tf, Integrator<T> &integrator, T tisim);
		inline void run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, T tisim);
	
		void run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints);
		inline void run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, unsigned long nbskipedpoints);
		inline void run(std::ostream &ostream, unsigned long nbpoitns, Integrator<T> &integrator, unsigned long nbskipedpoints);
		inline void run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, unsigned long nbskipedpoints);

};

template<typename T>
Simulation<T>::Simulation(void)
{
	this->unsetdynamicalsystem();
	this->unsetintegrator();
	this->writingstep((long)0);
	this->initprepostop();
	return;
}

template<typename T>
Simulation<T>::Simulation(DynamicalSystem<T> &dynamicalsystem)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->unsetintegrator();
	this->writingstep((long)0);
	this->initprepostop();
	return;
}

template<typename T>
Simulation<T>::Simulation(Integrator<T> &integrator)
{
	this->unsetdynamicalsystem();
	this->setintegrator(integrator);
	this->writingstep((long)0);
	this->initprepostop();
	return;
}

template<typename T>
Simulation<T>::Simulation(DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->setintegrator(integrator);
	this->writingstep((long)0);
	this->initprepostop();
	return;
}



template<typename T>
inline void Simulation<T>::writingstep(long ws)
{
	this->WSmax = ws;
	this->WScount = 0;
	return;
}

template<typename T>
inline void Simulation<T>::writingstep(void)
{
	this->writingstep((long)0);
	return;
}




template<typename T>
inline DynamicalSystem<T> &Simulation<T>::getdynamicalsystem()
{
	return this->*dynamicalsystem;
}

template<typename T>
inline Integrator<T> &Simulation<T>::getintegrator()
{
	return this->*integrator;
}

template<typename T>
inline void Simulation<T>::setdynamicalsystem(DynamicalSystem<T> &dynamicalsystem)
{
	this->dynamicalsystem = &dynamicalsystem;
	return;
}

template<typename T>
inline void Simulation<T>::setintegrator(Integrator<T> &integrator)
{
	this->integrator = &integrator;
	return;
}

template<typename T>
inline void Simulation<T>::unsetdynamicalsystem(void)
{
	this->dynamicalsystem = NULL;
	return;
}

template<typename T>
inline void Simulation<T>::unsetintegrator(void)
{
	this->integrator = NULL;
	return;
}


template<typename T>
inline PrePostOp<T> &Simulation<T>::getpreop()
{
	return this->*preop;
}

template<typename T>
inline PrePostOp<T> &Simulation<T>::getpostop()
{
	return this->*postop;
}

template<typename T>
inline void Simulation<T>::setpreop(PrePostOp<T> &preop)
{
	if (this->preop != NULL)
	{
		delete this->preop;
	}
	this->preop = &preop;
	return;
}

template<typename T>
inline void Simulation<T>::setpostop(PrePostOp<T> &postop)
{
	if (this->postop != NULL)
	{
		delete this->postop;
	}	
	this->postop = &postop;
	return;
}

template<typename T>
inline void Simulation<T>::unsetpreop(void)
{
	if (this->preop != NULL)
	{
		delete this->preop;
	}
	this->preop = new NoOp<T>();
	return;
}

template<typename T>
inline void Simulation<T>::unsetpostop(void)
{
	if (this->postop != NULL)
	{
		delete this->postop;
	}
	this->postop = new NoOp<T>();
	return;
}


template<typename T>
inline void Simulation<T>::initprepostop(void)
/* /!\ Attention : à n'utiliser que pour l'initialisation d'une simulation.
 * Dans le cas contraire il existe un risque de fuite de mémoire car l'objet
 * précédement pointé n'est pas supprimé.
 */
{
	this->preop = new NoOp<T>();
	this->postop = new NoOp<T>();
}




template<typename T>
void Simulation<T>::run(std::ostream &ostream, T ti, T tf, T tisim = (T)0.0)
{
	std::ostringstream oss;
	std::string aff;
	T t = tisim;

	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);

	while (t < ti)
	{
		(*this->integrator)(t, *this->dynamicalsystem);
	}

	while (t <= tf)
	{
		if (this->WScount <= 0)
		{
			oss.precision(3);
			oss.width(6);
			oss << t;
			aff = oss.str();
			oss.str("");
			this->dynamicalsystem->toString(aff);
			ostream << aff << std::endl;
		}
		this->WScount++;
		if (this->WScount >= this->WSmax)
			this->WScount = 0;

		(*this->preop)(*this->integrator, *this->dynamicalsystem);
		(*this->integrator)(t, *this->dynamicalsystem);
		(*this->postop)(*this->integrator, *this->dynamicalsystem);
	}

	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, T tisim = (T)0.0)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->run(ostream, ti, tf, tisim);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, T ti, T tf, Integrator<T> &integrator, T tisim = (T)0.0)
{
	this->setintegrator(integrator);
	this->run(ostream, ti, tf, tisim);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, T ti, T tf, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, T tisim = (T)0.0)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->setintegrator(integrator);
	this->run(ostream, ti, tf, tisim);
	return;
}





template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints = 0)
{
	std::ostringstream oss;
	std::string aff;
	T t = 0.0;
	unsigned long i;

	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);

	for(i = 0; i < nbskipedpoints; ++i)
	{
		(*this->integrator)(t, *this->dynamicalsystem);
	}

	for(i = 0; i < nbpoints; ++i)
	{
		if (this->WScount <= 0)
		{
			oss.precision(3);
			oss.width(6);
			oss << t;
			aff = oss.str();
			oss.str("");
			this->dynamicalsystem->toString(aff);
			ostream << aff << std::endl;
		}
		this->WScount++;
		if (this->WScount >= this->WSmax)
			this->WScount = 0;

		(*this->preop)(*this->integrator, *this->dynamicalsystem);
		(*this->integrator)(t, *this->dynamicalsystem);
		(*this->postop)(*this->integrator, *this->dynamicalsystem);
	}

	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, unsigned long nbskipedpoints = 0)
{
	this->setdynamicalsytem(dynamicalsystem);
	this->run(ostream, nbpoints, nbskipedpoints);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, Integrator<T> &integrator, unsigned long nbskipedpoints = 0)
{
	this->setintegrator(integrator);
	this->run(ostream, nbpoints, nbskipedpoints);
	return;
}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator, unsigned long nbskipedpoints = 0)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->setintegrator(integrator);
	this->run(ostream, nbpoints, nbskipedpoints);
	return;
}







#endif

