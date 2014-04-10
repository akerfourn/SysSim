#ifndef __SIMULATIONPREDICATE_HPP__
#define __SIMULATIONPREDICATE_HPP__

/* 	SimulationPredicate.hpp
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
 */


template<typename T>
class SimulationPredicate
{
	public:
		SimulationPredicate(void){};
		virtual ~SimulationPredicate(void){};

		virtual inline bool operator()(void)
		{
			return this->test();
		}

		virtual bool test(void) = 0;
};



template<typename T>
class IterativePredicate: public SimulationPredicate<T>
{
	protected:
		unsigned long nbpoints;
		unsigned long i;

		bool firststep;
	public:
		IterativePredicate(unsigned long nbpoints);
		virtual ~IterativePredicate(void){};

		virtual bool test(void);
};

template<typename T>
IterativePredicate<T>::IterativePredicate(unsigned long nbpoints)
{
	this->nbpoints = nbpoints+1;
	this->i = 0;
}

template<typename T>
inline bool IterativePredicate<T>::test(void)
{
	++(this->i);
	return (this->i < this->nbpoints);
}



template<typename T>
class TimePredicate: public SimulationPredicate<T>
{
	protected:
		T *t;
		
		T duration;

	public:
		TimePredicate(T &t, T duration);
		virtual ~TimePredicate(void){};

		virtual bool test(void);
		
};

template<typename T>
TimePredicate<T>::TimePredicate(T &t, T duration)
{
	this->duration = duration;
	this->t = &t;
}

template<typename T>
inline bool TimePredicate<T>::test(void)
{
	return (*this->t < this->duration);
}






#endif

