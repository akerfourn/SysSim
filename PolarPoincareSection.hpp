#ifndef __POLARPOINCARESECTION_HPP__
#define __POLARPOINCARESECTION_HPP__

#include "PoincareSection.hpp"
#include "SystemStates.hpp"

template<typename T>
class PolarPoincareSection: public PoincareSection<T>
{
	protected:

		std::vector<PoincareSection<t>::size_type> index;

		T xcenter, ycenter;
		T angle;

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
	return false;
}


template<typename T>
T PolarPoincareSection<T>::getdistance(void)
{
	return this->at(0);
}

#endif

