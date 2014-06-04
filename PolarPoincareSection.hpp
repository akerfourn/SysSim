#ifndef __POLARPOINCARESECTION_HPP__
#define __POLARPOINCARESECTION_HPP__

#include "PoincareSection.hpp"
#include "SystemStates.hpp"
#include <cmath>

#define PPS_PI 3.14159265358979323846

template<typename T>
class PolarPoincareSection: public PoincareSection<T>
{
	protected:

		SystemStates<T> previous;

		std::vector<PoincareSection<t>::size_type> index;

		T xcenter, ycenter;
		T angle;

		T angle(const T x,const T y, const T refangle, const T dist) const;

	public:

		typedef typename PoincareSection<T>::size_type size_type;

		PolarPoincareSection():PoincareSection()
		{
			this->init((size_type)0);
		};
		PolarPoincareSection(const size_type ndim):PoincareSection(ndim)
		{
			this->init(ndim);
		};
		virtual PolarPoincareSection(){};

		void init(const size_type ndim);

		void setcenter(T xcenter, T ycenter);
		void setangle(T angle);
		void setindex(std::vector<size_type> index);

		virtual bool crossed(SystemStates<T> current_state);
		virtual T getdistance(void);

};


template<typename T>
T PolarPoincareSection<T>::angle(const T x,const T y, const T refangle, const T dist) const
{
	T angle = (T)0.0;
	T ysign = (T)1.0;
	if (y < (T)0.0)
	{
		ysign = (T)-1.0;
	}

	if (y != (T)0.0)
	{
		angle = ysign*(T)acos( x / dist); 
	}
	else
	{
		if (x >= (T)0.0)
		{
			angle = (T)0.0;
		}
		else
		{
			angle = (T)PPS_PI;
		}
	}

	angle = angle - refangle;

	if (angle > (T)PPS_PI)
	{
		angle = angle - (T)2.0*(T)PPS_PI;
	}
	else if (theta <= -(T)PPS_PI)
	{
		angle = angle + (T)2.0*(T)PPS_PI;
	}

	return angle;
}

template<typename T>
void PolarPoincareSection<T>::init(const size_type ndim)
{
		this->previous.resize(ndim);
		this->index.resize(ndim);
		this->xcenter = (T)0.0;
		this->ycenter = (T)0.0;
		this->refangle = (T)0.0;
		return;
}

template<typename T>
void PolarPoincareSection<T>::setcenter(T xcenter, T ycenter)
{
	this->xcenter = xcenter;
	this->ycenter = ycenter;
	return;
}

template<typename T>
void PolarPoincareSection<T>::setangle(T angle)
{
	this->angle = angle;
	return;
}

template<typename T>
void PolarPoincareSection<T>::setindex(std::vector<size_type> index)
{
	for(size_type i; i < this->index.size(); ++i)
	{
		this->index.at(i) = index.at(i);
	}
	return;
}


template<typename T>
bool PolarPoincareSection<T>::crossed(SystemStates<T> current_state)
{
	T distance;
	T angle, pangle;
	T x,y;
	bool crossed = false;

	x = current_state.at(this->index.at(0));
	y = current_state.at(this->index.at(1));

	distance = (T)sqrt(x*x+y*y);
	
	angle = this->angle(x,y,this->angle,distance);
	pangle = this->previous.at(1);
	
	if ( (pangle < (T)0.0) && (angle >= (T)0.0) )
	{
		T alpha = -pangle/(angle-pangle);
	
		this->at(0) = this->previous.at(0) + alpha * (distance - this->previous.at(0));
		for (int i = 1; i < this->previous.size(); ++i)
		{
			this->at(i) = this->previous.at(i) + alpha * (distance - this->previous.at(i));
		}
		crossed = true;
	}
	
	this->previous.at(0) = distance;
	this->previous.at(1) = angle;
	for (int i = 2; i < this->previous.size(); ++i)
	{
		this->previous.at(i) = current_state.at(this->index.at(i));
	}
	return crossed;
}


template<typename T>
T PolarPoincareSection<T>::getdistance(void)
{
	return this->at(0);
}

#endif

