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
#include "SimulationPredicate.hpp"

template<typename T>
class Simulation
{
	protected:
		DynamicalSystem<T> *dynamicalsystem;
		Integrator<T> *integrator;

		T time;

		long WSmax, WScount;	// writingstep


	public:
		Simulation(void);
		Simulation(DynamicalSystem<T> &dynamicalsystem);
		Simulation(Integrator<T> &integrator);
		Simulation(DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator);
		virtual ~Simulation(void){};

		inline void writingstep(long ws);
		inline void writingstep(void);

		inline T getTime(void);
		inline T setTime(T time);

		inline DynamicalSystem<T> &getdynamicalsystem();
		inline Integrator<T> &getintegrator();
		inline void setdynamicalsystem(DynamicalSystem<T> &dynamicalsystem);
		inline void setintegrator(Integrator<T> &integrator);
		inline void unsetdynamicalsystem(void);
		inline void unsetintegrator(void);

		void run(std::ostream &ostream, T ti, T tf, PrePostOp<T> &preop, PrePostOp<T> &postop);
		void run(std::ostream &ostream, T ti, T tf);
	
		void run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints, PrePostOp<T> &preop, PrePostOp<T> &postop);
		void run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints);
		
		void run(std::ostream &ostream, SimulationPredicate<T> &transiant, SimulationPredicate<T> &nontransiant, PrePostOp<T> &preop, PrePostOp<T> &postop);

};

template<typename T>
Simulation<T>::Simulation(void)
{
	this->unsetdynamicalsystem();
	this->unsetintegrator();
	this->writingstep((long)0);
	this->time = (T)0.0;
	return;
}

template<typename T>
Simulation<T>::Simulation(DynamicalSystem<T> &dynamicalsystem)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->unsetintegrator();
	this->writingstep((long)0);
	this->time = (T)0.0;
	return;
}

template<typename T>
Simulation<T>::Simulation(Integrator<T> &integrator)
{
	this->unsetdynamicalsystem();
	this->setintegrator(integrator);
	this->writingstep((long)0);
	this->time = (T)0.0;
	return;
}

template<typename T>
Simulation<T>::Simulation(DynamicalSystem<T> &dynamicalsystem, Integrator<T> &integrator)
{
	this->setdynamicalsystem(dynamicalsystem);
	this->setintegrator(integrator);
	this->writingstep((long)0);
	this->time = (T)0.0;
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
inline T Simulation<T>::getTime(void)
{
	return this->time;
}

template<typename T>
inline T Simulation<T>::setTime(T time)
{
	this->time = time;
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
void inline Simulation<T>::run(std::ostream &ostream, T ti, T tf, PrePostOp<T> &preop, PrePostOp<T> &postop)
{
	TimePredicate<T> *transiant = new TimePredicate<T>(this->time, ti);
	TimePredicate<T> *nontransiant = new TimePredicate<T>(this->time, tf);

	this->run(ostream, *transiant, *nontransiant, preop, postop);

	delete transiant;
	delete nontransiant;

	return;
}

template<typename T>
void inline Simulation<T>::run(std::ostream &ostream, T ti, T tf)
{
	NoOp<T> *noop = new NoOp<T>();

	this->run(ostream, ti, tf, *noop, *noop);

	delete noop;

	return;
}




template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints, PrePostOp<T> &preop, PrePostOp<T> &postop)
{

	IterativePredicate<T> *transiant = new IterativePredicate<T>(nbskipedpoints);
	IterativePredicate<T> *nontransiant = new IterativePredicate<T>(nbpoints);

	this->run(ostream, *transiant, *nontransiant, preop, postop);

	delete transiant;
	delete nontransiant;

	return;

}

template<typename T>
inline void Simulation<T>::run(std::ostream &ostream, unsigned long nbpoints, unsigned long nbskipedpoints = 0)
{
	NoOp<T> *noop = new NoOp<T>();

	this->run(ostream, nbpoints, nbskipedpoints, *noop, *noop);

	delete noop;

	return;
}


template<typename T>
void Simulation<T>::run(std::ostream &ostream, SimulationPredicate<T> &transiant, SimulationPredicate<T> &nontransiant, PrePostOp<T> &preop, PrePostOp<T> &postop)
{
	
	// TODO raise an error if some élement are not defined (integrator and dynamicalsystem)
		
	std::ostringstream oss;
	std::string aff;

	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);

	while(transiant.test() == true)
	{
		(*this->integrator)(this->time, *this->dynamicalsystem);
	}

	while(nontransiant.test() == true)
	{
		if (this->WScount <= 0)
		{
			oss.precision(3);
			oss.width(6);
			oss << this->time;
			aff = oss.str();
			oss.str("");
			this->dynamicalsystem->toString(aff);
			ostream << aff << std::endl;
		}
		this->WScount++;
		if (this->WScount >= this->WSmax)
		{
			this->WScount = 0;
		}

		preop(*this->integrator, *this->dynamicalsystem);		// Processing Pre-integration
		(*this->integrator)(this->time, *this->dynamicalsystem);
		postop(*this->integrator, *this->dynamicalsystem);		// Processing Post-integration
	}

	return;

}





#endif

