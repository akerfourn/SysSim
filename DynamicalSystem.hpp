#ifndef __DYNAMICALSYSTEM_HPP__
#define __DYNAMICALSYSTEM_HPP__

/*	DynamicalSystem.hpp
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
 *		Fournit une class abstraite définissant un système dynamique. Un système
 * dynamique est définit comme ayant un vecteur de variables d'état "x", un 
 * vecteur de variables de sortie "y" ainsi que la définition d'une dynamique
 * (donnée par la fonction "f" qui donne la dérivée des états du système en
 * fonction de ceux-ci et d'un certain nombre de paramètre intrinsèque au
 * système à définir).
 *		Cette classe est abstraite et ne sert que de base à la définition d'un
 * système. Ainsi pour définir un système l'implémentation minimal consiste en
 * la définition d'une classe héritant de DynamicalSystem et définissant la
 * fonction "f".
 *
 * * NOTE 1 : La fonction "f" doit créer un objet de type SystemState contenant,
 * a minima, les dérivées des états (et donc, si possible, aussi les sorties).
 * Le choix de la création d'un objet plutôt que l'utilisation d'un attribut
 * s'explique par l'utilisation de méthode d'intégration d'ordre supérieur à
 * un (tel que le Runge-Kutta 4, par exemple). Dans ces méthodes, on effectue
 * une synthèse de plusieurs estimations de la dérivé du système : l'utilisation
 * d'un attribut aurait donc nécessité des copies d'objets couteuses en temps
 * d'execution.
 *
 * * NOTE 2 : Voir "Rossler.hpp" pour un exemple d'implémentation.
 *
 */

/* FIXME
 *	Dans la fonction "f" le temps est de type "T". Le problème étant qu'il n'est
 * alors pas possible d'avoir un temps non-entier pour un vecteur d'état
 * d'entier.
 * Une solution est d'utiliser des doubles. Néanmoins il pourrait exister des
 * particulier où l'on voudrait des temps très long ou très précis (et
 * utilisant dans ce cadre un type particulier sans relation avec le type des
 * états).
 * Une autre solution et d'utiliser un template avec un second type. Le problème
 * et alors qu'on complexifie fortement l'utilisation de la classe dans le cas
 * général pour un comportement très particulier.
 * Peut-être que l'on peut par héritage avoir une classe d'utilisation plus
 * simple, par exemple :
 *		template<typename T, typename U> class A {...};
 *		template<typename T> class B: public class A {};
 * où le contenu de la classe B est absolument vide ?
 */

#include <string>
#include <sstream>

#include "Vector.hpp"

template<typename T>
class DynamicalSystem
{
	public:
		typedef typename Vector<T>::size_type size_type;
	
	protected:
		
		Vector<T> *mx;
		Vector<T> *mdx;
		Vector<T> *my;
		
		bool self_mx;
		bool self_mdx;
		bool self_my;
		
		size_type nstates;
		size_type noutputs;

	public:

		DynamicalSystem(void);
		DynamicalSystem(const size_type nstates, const bool newvectors = true);
		DynamicalSystem(Vector<T> &x, Vector<T> &dx);
		DynamicalSystem(Vector<T> *x, Vector<T> *dx);
		DynamicalSystem(const size_type nstates, const size_type noutputs, const bool newvectors = true);
		DynamicalSystem(Vector<T> &x, Vector<T> &dx, Vector<T> &y);
		DynamicalSystem(Vector<T> *x, Vector<T> *dx, Vector<T> *y);
		DynamicalSystem(DynamicalSystem<T> &ref);
		virtual ~DynamicalSystem(void);
		
		inline Vector<T>& getx(void);
		inline Vector<T>& getdx(void);
		inline Vector<T>& gety(void);
		
		inline void setx(Vector<T> &x, bool force_self = false);
		inline void setx(Vector<T> *x, bool force_self = false);
		inline void setx(Vector<T> &x, Vector<T> &dx, bool force_self = false);
		inline void setx(Vector<T> *x, Vector<T> *dx, bool force_self = false);
		inline void setdx(Vector<T> &dx, bool force_self = false);
		inline void setdx(Vector<T> *dx, bool force_self = false);
		inline void sety(Vector<T> &y, bool force_self = false);
		inline void sety(Vector<T> *y, bool force_self = false);

		inline void copy(const DynamicalSystem<T> &ref);

		/* La fonction "f" définie la dynamique du système en fonction du temps
		 * "t" et d'un vecteur d'état "state".
		 */
		virtual void f(T t, Vector<T>& x) = 0;
		inline void f(T t);

		virtual void h(T t, Vector<T>& x);
		inline void h(T t);

		virtual void init(void);
		virtual void init(const size_type nstates, const bool newvectors = true);
		inline void init(Vector<T> &x, Vector<T> &dx);
		virtual void init(Vector<T> *x, Vector<T> *dx);
		virtual void init(const size_type nstates, const size_type noutputs, const bool newvectors = true);
		inline void init(Vector<T> &x, Vector<T> &dx, Vector<T> &y);
		virtual void init(Vector<T> *x, Vector<T> *dx, Vector<T> *y);
		virtual void init(const DynamicalSystem<T> &ref);
		virtual void init(const T xi[]);
		virtual void init(const std::vector<T> &xi);

		inline T &y(const size_type index);
		inline T y(const size_type index) const;

		inline T &dx(const size_type index);
		inline T dx(const size_type index) const;

		inline T &x(const size_type index);
		inline T x(const size_type index) const;

		inline size_type sizex(void) const;
		inline size_type sizedx(void) const;
		inline size_type sizey(void) const;
		
		virtual size_type dimStates(void) const;
		virtual size_type dimOutputs(void) const;
		
		virtual void toString(std::string &string);
		virtual void toString(std::string &string, int precision, int width, char separator);

};

template<typename T>
DynamicalSystem<T>::DynamicalSystem(void)
{
	this->init();
	return;
}

template<typename T>
DynamicalSystem<T>::DynamicalSystem(const size_type nstates, const bool newvectors)
{
	this->init();
	this->init(nstates, newvectors);
	return;
}

template<typename T>
DynamicalSystem<T>::DynamicalSystem(Vector<T> &x, Vector<T> &dx)
{
	this->init();
	this->init(x,dx);
	return;
}

template<typename T>
DynamicalSystem<T>::DynamicalSystem(Vector<T> *x, Vector<T> *dx)
{
	this->init();
	this->init(x,dx);
	return;
}

template<typename T>
DynamicalSystem<T>::DynamicalSystem(const size_type nstates, const size_type noutputs, const bool newvectors)
{
	this->init();
	this->init(nstates,noutputs, newvectors);
	return;
}

template<typename T>
DynamicalSystem<T>::DynamicalSystem(Vector<T> &x, Vector<T> &dx, Vector<T> &y)
{
	this->init();
	this->init(x,dx,y);
	return;
}

template<typename T>
DynamicalSystem<T>::DynamicalSystem(Vector<T> *x, Vector<T> *dx, Vector<T> *y)
{
	this->init();
	this->init(x,dx,y);
	return;
}

template<typename T>
DynamicalSystem<T>::DynamicalSystem(DynamicalSystem<T> &ref)
{
	this->init();
	this->init(ref);
	return;
}

template<typename T>
DynamicalSystem<T>::~DynamicalSystem(void)
{
	if (this->self_mx == true)
	{
		delete this->mx;
	}
	if (this->self_mdx == true)
	{
		delete this->mdx;
	}
	if (this->self_my == true)
	{
		delete this->my;
	}
	return;
}



template<typename T>
inline Vector<T>& DynamicalSystem<T>::getx(void)
{
	return (*this->mx);
}

template<typename T>
inline Vector<T>& DynamicalSystem<T>::getdx(void)
{
	return (*this->mdx);
}

template<typename T>
inline Vector<T>& DynamicalSystem<T>::gety(void)
{
	return (*this->my);
}


template<typename T>
inline void DynamicalSystem<T>::setx(Vector<T> &x, bool force_self)
{
	this->setx(&x,force_self);
	return;
}

template<typename T>
inline void DynamicalSystem<T>::setx(Vector<T> *x, bool force_self)
{
	this->mx = x;
	this->self_mx = force_self;
	return;
}

template<typename T>
inline void DynamicalSystem<T>::setx(Vector<T> &x, Vector<T> &dx, bool force_self)
{
	this->setx(&x,&dx,force_self);
	return;
}

template<typename T>
inline void DynamicalSystem<T>::setx(Vector<T> *x, Vector<T> *dx, bool force_self)
{
	this->setx(x,force_self);
	this->setdx(dx,force_self);
	return;
}

template<typename T>
inline void DynamicalSystem<T>::setdx(Vector<T> &dx, bool force_self)
{
	this->setdx(&dx,force_self);
	return;
}

template<typename T>
inline void DynamicalSystem<T>::setdx(Vector<T> *dx, bool force_self)
{
	this->mdx = dx;
	this->self_mdx = force_self;
	return;
}

template<typename T>
inline void DynamicalSystem<T>::sety(Vector<T> &y, bool force_self)
{
	this->sety(&y,force_self);
	return;
}

template<typename T>
inline void DynamicalSystem<T>::sety(Vector<T> *y, bool force_self)
{
	this->my = y;
	this->self_my = force_self;
	return;
}



template<typename T>
inline void DynamicalSystem<T>::f(T t)
{
	this->f(t,this->getx());
	return;
}



template<typename T>
void DynamicalSystem<T>::h(T t, Vector<T>& x)
{
	return;
}

template<typename T>
inline void DynamicalSystem<T>::h(T t)
{
	this->h(t,this->getx());
	return;
}


/*

template<typename T>
inline void DynamicalSystem<T>::resize(const size_type nbstates, const size_type nboutput)
{
	SystemStates<T>::resize(nbstates);
	this->mdx.resize(nbstates);
	this->my.resize(nboutput);

	return;
}

template<typename T>
inline void DynamicalSystem<T>::resize(const DynamicalSystem<T> &ref)
{
	SystemStates<T>::resize(ref.sizex());
	this->mdx.resize(ref.sizedx());
	this->my.resize(ref.sizey());
	return;
}

*/

template<typename T>
inline void DynamicalSystem<T>::copy(const DynamicalSystem<T> &ref)
{
	for(size_type i = (size_type)0; i < ref.sizex(); ++i)
	{
		this->x(i) = ref.x(i);
	}

	for(size_type i = (size_type)0; i < ref.sizedx(); ++i)
	{
		this->dx(i) = ref.dx(i);
	}

	for(size_type i = (size_type)0; i < ref.sizey(); ++i)
	{
		this->y(i) = ref.y(i);
	}
	return;
}



template<typename T>
void DynamicalSystem<T>::init(void)
{
	this->mx = NULL;
	this->my = NULL;
	this->mdx = NULL;
	this->self_mx = false;
	this->self_my = false;
	this->self_mdx = false;
	this->nstates = 0;
	this->noutputs = 0;
	return;
}

template<typename T>
void DynamicalSystem<T>::init(const size_type nstates, const bool newvectors)
{
	if (this->self_mx == true)
	{
		delete this->mx;
	}
	if (this->self_mdx == true)
	{
		delete this->my;
	}
	if (newvectors == true)
	{
		this->mx = new BaseVector<T>(nstates);
		this->mdx = new BaseVector<T>(nstates);
		this->self_mx = true;
		this->self_mdx = true;
	}
	this->nstates = nstates;
	return;
}

template<typename T>
inline void DynamicalSystem<T>::init(Vector<T> &x, Vector<T> &dx)
{
	this->init(&x,&dx);
	return;
}

template<typename T>
void DynamicalSystem<T>::init(Vector<T> *x, Vector<T> *dx)
{
	if (x->size() != dx->size())
	{
		// TODO : Raise error : the x and dx vectors must have the same size.
		return;
	}
	this->setx(x);
	this->setdx(dx);
	return;
}

template<typename T>
void DynamicalSystem<T>::init(const size_type nstates, const size_type noutputs, const bool newvectors)
{
	this->init(nstates, newvectors);
	if (noutputs <= 0)
	{
		return;
	}
	if (this->self_my == true)
	{
		delete this->my;
	}
	if (newvectors == true)
	{
		this->my = new BaseVector<T>(noutputs);
		this->self_my = true;
	}
	return;
}

template<typename T>
inline void DynamicalSystem<T>::init(Vector<T> &x, Vector<T> &dx, Vector<T> &y)
{
	this->init(&x,&dx,&y);
	return;
}

template<typename T>
void DynamicalSystem<T>::init(Vector<T> *x, Vector<T> *dx, Vector<T> *y)
{
	this->init(x,dx);
	this->sety(y);
	return;
}

template<typename T>
inline void DynamicalSystem<T>::init(const DynamicalSystem<T> &ref)
{
	// TODO
	return;
}

template<typename T>
void DynamicalSystem<T>::init(const T xi[])
{
	for(size_type i = 0; i < this->sizex(); ++i)
	{
		this->x(i) = xi[i];
	}
	return;
}

template<typename T>
void DynamicalSystem<T>::init(const std::vector<T> &xi)
//FIXME : /!\ Aucune gestion d'erreur (alors que possible assez simplement).
{
	for(size_type i = 0; i < this->sizex(); ++i)
	{
		this->x(i) = xi[i];
	}
	return;
}



template<typename T>
inline T& DynamicalSystem<T>::y(const size_type index)
{
	return (*this->my)[index];
}

template<typename T>
inline T DynamicalSystem<T>::y(const size_type index) const
{
	return (*this->my)[index];
}

template<typename T>
inline T& DynamicalSystem<T>::dx(const size_type index)
{
	return (*this->mdx)[index];
}

template<typename T>
inline T DynamicalSystem<T>::dx(const size_type index) const
{
	return (*this->mdx)[index];
}

template<typename T>
inline T& DynamicalSystem<T>::x(const size_type index)
{
	return (*this->mx)[index];
}

template<typename T>
inline T DynamicalSystem<T>::x(const size_type index) const
{
	return (*this->mx)[index];
}

template<typename T>
inline typename DynamicalSystem<T>::size_type DynamicalSystem<T>::sizex(void) const
{
	if (this->mx != NULL)
	{
		return this->mx->size();
	}
	else
	{
		return (size_type)0;
	}
}

template<typename T>
inline typename DynamicalSystem<T>::size_type DynamicalSystem<T>::sizedx(void) const
{
	if (this->mdx != NULL)
	{
		return this->mdx->size();
	}
	else
	{
		return (size_type)0;
	}
}

template<typename T>
inline typename DynamicalSystem<T>::size_type DynamicalSystem<T>::sizey(void) const
{
	if (this->my != NULL)
	{
		return this->my->size();
	}
	else
	{
		return (size_type)0;
	}
}


template<typename T>
typename DynamicalSystem<T>::size_type DynamicalSystem<T>::dimStates(void) const
{
	return this->nstates;
}

template<typename T>
typename DynamicalSystem<T>::size_type DynamicalSystem<T>::dimOutputs(void) const
{
	return this->noutputs;
}


/* Affichage */

template<typename T>
void DynamicalSystem<T>::toString(std::string &string)
{
	this->toString(string,2,6,' ');
	return;
}

template<typename T>
void DynamicalSystem<T>::toString(std::string &string, int precision, int width , char separator = ' ')
/*    Ajoute les élements de l'objet SystemStates à la chaine de caractère
 * "string". Les éléments sont ajouter les uns à la suite des autres en
 * commençant par les éléments de x puis en terminant avec les élements de y.
 *    Les valeurs sont écritent avec un certain nombre de chiffres après la
 * virgule défini par la variable "precision".
 *	  De plus les valeurs sont écrite sur un certain nombre de caractères
 * (total) défini par la variable "width".
 *	  Les élements sont séparés les uns des autres par un séparateur
 * (typiquement une espace ' ' ou une tabulation '\t') défini par la variable
 * "separator". Par défaut, le séparateur utilisé est l'espace ' '.
 */
{

	std::ostringstream oss;
	size_type i;

	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);

	if ( (this->sizex() <= 0) )
	{
		return;
	}

	if (string.length() > 0)
	{
		string += separator;
	}

	if (this->sizex() > 0)
	{
		oss.precision(precision);
		oss.width(width);
		oss << this->x(0);
		string += oss.str();
		oss.str("");

		for(i = 1; i < this->sizex(); ++i)
		{
			oss.precision(precision);
			oss.width(width);
			oss << this->x(i);
			string += separator + oss.str();
			oss.str("");
		}
	}
	
}

#endif

