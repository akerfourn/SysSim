#ifndef __POINCARESECTION_HPP__
#define __POINCARESECTION_HPP__

#include "SystemStates.hpp"

template<typename T>
class PoincareSection: public SystemStates<T>
{

	public:
		typedef typename SystemStates<T>::size_type size_type;

		PoincareSection():SystemStates<T>(){};
		PoincareSection(const size_type ndim):SystemStates<T>(ndim){};
		virtual ~PoincareSection(){};

		virtual bool crossed(SystemStates<T> current_state) = 0;
		virtual T getdistance(void) = 0;

};


#endif

