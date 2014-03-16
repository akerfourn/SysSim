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
		SimulationPredicate(void);
		virtual ~SimulationPredicate(void){};

		virtual bool operator()(void) = 0;
};

template<typename T>
class IterativePredicate: public SimulationPredicate
{
	protected:
		unsigned long nbskipedpoints;
		unsigned long nbpoints;
		unsigned long i;

		bool firststep;
	public:
		IterativePredicate(unsigned long nbpoints, unsigned long nbskipedpoints = (unsigned long)0);
		virtual ~IterativePredicate(void){};

		virtual bool operator()(void);
};

template<typename T>
IterativePredicate<T>::IterativePredicate(unsigned long nbpoints, unsigned long nbskipedpoints = (unsigned long)0)
{
	this->nbskipedpoints = nbskipedpoints+1;
	this->nbpoints = nbpoints+1;
	this->i = 0;
	this->firststep = true;
}

template<typename T>
inline bool operator()(void)
{
	++(this->i);

	if (this->firststep)
	{
		if (this->i < this->nbskipedpoints)
		{
			return true;
		}
		else
		{
			this->i = 0;
			this->firstep = false;
			return false;
		}
	}
	else
	{
		return (this->i < this->nbpoints);
	}
}

template<typename T>
class TimePredicate<T>: public SimulationPredicate
{
	protected:
		T *t;
		
		T ti, tf;

		bool firststep;

	public:
		TimePredicate(T &t, T tf, T ti = (T)0.0);
		virtual ~TimePredicate(void){};

		virtual bool operator()(void);
		
};

template<typename T>
TimePredicate<T>::TimePredicate(T &t, T tf, T ti = (T)0.0)
{
	this->ti = ti;
	this->tf = tf;
	this->t = &t;
	this->>firststep = true;
}

template<typename T>
inline bool operator()(void)
{
	if (firststep)
	{
		if (*this->t < ti)
		{
			return true;
		}
		else
		{
			this->firststep = false;
			return false;
		}
	}
	else
	{
		return (*this->t < tf);
	}
}






#endif

