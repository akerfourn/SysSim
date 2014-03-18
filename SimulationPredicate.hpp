#ifndef __SIMULATIONPREDICATE_HPP__
#define __SIMULATIONPREDICATE_HPP__

/* SimulationPredicate
 *
 *
 *
 *	Adrien KERFOURN
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

