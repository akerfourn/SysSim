#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

/* Network.hpp
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
 *
 *
 *	Permet de définir un réseau générique.
 *
 */

#include <vector>

#include "DynamicalSystem.hpp"
#include "Vector.hpp"


template<typename T>
class Network: public DynamicalSystem<T>
{
	public:
		typedef typename DynamicalSystem<T>::size_type size_type;
	
	protected:
		std::vector< LocalSystem<T>* > local_systems;
		std::vector< DynamicalSystem<T>* > systems;
		
		Vector<T> *base;

	public:
		Network(void):DynamicalSystem<T>(0,0,false){};
		virtual ~Network(void){};

		void add(LocalSystem<T>& system);
		void add(DynamicalSystem<T> &system);
		void finish(Vector<T> *x, Vector<T> *dx, Vector<T> *y);
		void finish(void);

		virtual void f(T t, Vector<T>& x);
};

template<typename T>
void Network<T>::add(LocalSystem<T>& system)
{
	//long nstates = this->sizex();
	//long noutputs = this->sizey();

	system.init(*this,this->nstates, this->noutputs);

	this->local_systems.push_back(&system);
	this->nstates += system.sizex();
	this->noutputs += system.sizey();

	//this->resize(nstates, noutputs);
	return;
}

template<typename T>
void Network<T>::add(DynamicalSystem<T> &system)
{
	if (system.dimStates() > (size_type)0)
	{
		system.setx(new SubVector<T>(this->nstates, this->nstates+system.dimStates()),true);
		system.setdx(new SubVector<T>(this->nstates,this->nstates+system.dimStates()),true);
		this->nstates += system.dimStates();
	}
	if (system.dimOutputs() > (size_type)0)
	{
		system.sety(new SubVector<T>(this->noutputs,this->noutputs+system.dimOutputs()),true);
		this->noutputs += system.dimOutputs();
	}
	this->systems.push_back(&system);
	return;
}

template<typename T>
void Network<T>::finish(Vector<T> *x, Vector<T> *dx, Vector<T> *y)
{
	// TODO call init
	for (size_type i = (size_type)0; i < this->systems.size(); ++i)
	{
		if (this->systems[i]->dimStates() > (size_type)0)
		{
			((SubVector<T>*)(&this->systems[i]->getx()))->setVector(x);
			((SubVector<T>*)(&this->systems[i]->getdx()))->setVector(dx);
		}
		if(this->systems[i]->dimOutputs() > (size_type)0)
		{
			((SubVector<T>*)(&this->systems[i]->gety()))->setVector(y);
		}
	}
}

template<typename T>
void Network<T>::finish(void)
{
	this->init(this->nstates, this->noutputs,true);
	this->base = this->mx;
	this->mx = new SubVector<T>(this->base,(size_type)0,this->nstates);
	this->finish(this->mx,this->mdx,this->my);
	return;
}



template<typename T>
void Network<T>::f(T t, Vector<T>& x)
{
	//this->mx = &x;	// TODO c'est faux ! Ça ne fait pas ce qui est voulu
	if (&x != this->mx)
	{
		((SubVector<T>*)(this->mx))->setVector(x);
	}
	else
	{
		((SubVector<T>*)(this->mx))->setVector(this->base);
	}
	
	for(int i = 0; i < this->local_systems.size(); ++i)
	{
		this->local_systems[i]->setcx(x);
		this->local_systems[i]->localf(t);
		this->local_systems[i]->unsetcx();
	}
	
	for(int i = 0; i < this->systems.size(); ++i)
	{
		this->systems[i]->f(t);
	}
	
	//this->mx = this->originalx;
	((SubVector<T>*)(this->mx))->setVector(this->base);
	return;
}


#endif





















