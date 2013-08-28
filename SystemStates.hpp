#ifndef __SYSTEMSTATES_HPP__
#define __SYSTEMSTATES_HPP__

/*	SystemStates.hpp
 *
 *		Gives a class for state vectors manipulation. It consist of two vectors.
 * The first one x correspond with the state variables of the system and the
 * second one y correspond with the outputs of the system.
 *
 *		You can have a system without output variables or a system without
 * state variables.
 *
 *		SystemStates uses template to be compatible with all C++ standard types
 * (int, float, double, ...). You can also use your own types. In this case
 * you type must overload arithmetics and assignment operators. But you must
 * also overload the << with std::ostream object to allow you to write
 * your results on a string or in an output file.
 *
 *	Adrien KERFOURN (2013)
 */

#include <vector>
#include <exception>

#include <string>
#include <sstream>

class SystemStatesIndexError: public std::exception
{
	public:

		virtual const char* what() const throw()
		{
			return "Indice en dehors des bornes.";
		}
};

template<typename T>
class SystemStates
{
	protected:

		std::vector<T> x;	// State variables of the system.
		std::vector<T> y;	// Outputs of the system.

	public:

		SystemStates(void);
		SystemStates(const long nbstates);
		SystemStates(const long nbstates, const long nboutput);
		SystemStates(SystemStates<T> const &ref);
		virtual ~SystemStates(void){};

		virtual inline void resize(void);
		virtual inline void resize(const long nbstates);
		virtual inline void resize(const long nbstates, const long nboutput);
		virtual inline void resize(SystemStates<T> const &fromstates);

		virtual inline void copy(SystemStates<T> const &fromstates);

		inline T &operator[](const long index);				// Equivalent to getx(...).
		inline T operator[](const long index) const;		

		inline T &operator()(const long index);				// Equivalent to gety(...).
		inline T operator()(const long index) const;

		inline bool operator==(SystemStates<T> const &other);	// TODO : Test !
		inline bool operator!=(SystemStates<T> const &other);	// TODO : Test !


		/* Warning, there is no check of the index for these getters en setters
		 * functions :
		 */
		inline T &getx(const long index);
		inline T getx(const long index) const;
		inline T &gety(const long index);
		inline T gety(const long index) const;
		inline void setx(const long index, const T value);
		inline void sety(const long index, const T value);

		/* However, these ones check the index (and send an
		 * SystemStatesIndexError exception if it's out of boundary) :
		 */
		inline T &sgetx(const long index);
		inline T sgetx(const long index) const;
		inline T &sgety(const long index);
		inline T sgety(const long index) const;
		inline void ssetx(const long index, const T value);
		inline void ssety(const long index, const T value);

		inline long sizex(void) const;
		inline long sizey(void) const;

		/*	TODO FIXME : Il faudrait peut être passer à une surcharge de << ...
		 * "toString" ça fait un peu trop java !
		 */

		/* toString ajoute à "string" une représentation de l'objet SystemStates
		 * (ou dérivé). Les éléments sont ajoutés les uns à la suite des autres
	     * en commençant par les éléments du vecteur x avant de finir avec les
		 * éléments du vecteur y. Ces éléments sont séparés par un séparateur
		 * (typiquement une espace ' ' ou une tabulation '\t') : par défaut le
		 * séparateur est une espace ' '.
		 *
		 * Informations complémentaires :
		 *  - int precision : donne le nombre de chiffre après la virgule (2 par
		 *		défaut).
		 *	- int width : donne le nombre total de caractères utilisés pour
		 *		écrire le nombre (6 par défaut).
		 */
		virtual inline void toString(std::string &string);
		virtual inline void toString(std::string &string, int precision, int width, char separator);
		/* FIXME
		inline std::string toString(std::string &string);
		inline std::string toString(std::string &string, int precision, int width, char separator);
		inline std::string toString(int precision, int width, char separator);
		*/

};

/* Constructeurs */

template<typename T>
SystemStates<T>::SystemStates(void)
{
	this->resize();
	return;
}

template<typename T>
SystemStates<T>::SystemStates(const long nbstates)
{
	this->resize(nbstates);
	return;
}

template<typename T>
SystemStates<T>::SystemStates(const long nbstates, const long nboutput)
{
	this->resize(nbstates, nboutput);
	return;
}

template<typename T>
SystemStates<T>::SystemStates(SystemStates<T> const &ref)
{
	this->copy(ref);
	return;
}


/* Initialisations */

template<typename T>
inline void SystemStates<T>::resize(void)
{
	this->resize(0,0);
}

template<typename T>
inline void SystemStates<T>::resize(long nbstates)
{
	this->resize(nbstates,0);
	return;
}

template<typename T>
inline void SystemStates<T>::resize(long nbstates, long nboutput)
{
	if ( (nbstates >= 0) && (nboutput >= 0) )
	{
		this->x.resize(nbstates);
		this->y.resize(nboutput);
	}
	else
		throw SystemStatesIndexError();

	return;
}

template<typename T>
inline void SystemStates<T>::resize(SystemStates<T> const &fromstates)
{
	this->resize(fromstates.sizex(), fromstates.sizey());
	return;
}




template<typename T>
inline void SystemStates<T>::copy(SystemStates<T> const &fromstates)
{
	long i;

	this->resize(fromstates.sizex(),fromstates.sizey());

	for(i = 0; i < fromstates.sizex(); ++i)
	{
		this->getx(i) = fromstates[i];
	}

	for(i = 0; i < fromstates.sizey(); ++i)
	{
		this->gety(i) = fromstates(i);
	}

	return;
}



/* Operators overload */

template<typename T>
inline T &SystemStates<T>::operator[](const long index)
{
	return this->getx(index);
}

template<typename T>
inline T SystemStates<T>::operator[](const long index) const
{
	return this->getx(index);
}

template<typename T>
inline T &SystemStates<T>::operator()(const long index)
{
	return this->gety(index);
}

template<typename T>
inline T SystemStates<T>::operator()(const long index) const
{
	return this->gety(index);
}

template<typename T>
inline bool SystemStates<T>::operator==(SystemStates<T> const &other)
{
	long i;
	if ( (this->sizex() != other.sizex) || (this->sizey() != other.sizey()) ) return false;

	/* Checks each x (one by one) : */
	for(i = 0; i < this->sizex(); ++i)
	{
		if (this->getx(i) != other.gety(i)) return false;
	}

	/* Checks each y (one by one) : */
	for(i = 0; i < this->sizey(); ++i)
	{
		if (this->gety() != other.gety()) return false;
	}

	return true;
}

template<typename T>
inline bool SystemStates<T>::operator!=(SystemStates<T> const &other)
{
	return !(*this == other);
}



/* getters and setters */

template<typename T>
inline T &SystemStates<T>::getx(const long index)
{
	return this->x[index];
}

template<typename T>
inline T SystemStates<T>::getx(const long index) const
{
	return this->x[index];
}

template<typename T>
inline T &SystemStates<T>::gety(const long index)
{
	return this->y[index];
}

template<typename T>
inline T SystemStates<T>::gety(const long index) const
{
	return this->y[index];
}

template<typename T>
inline void SystemStates<T>::setx(const long index, T value)
{
	this->x[index] = value;
	return;
}

template<typename T>
inline void SystemStates<T>::sety(const long index, T value)
{
	this->y[index] = value;
	return;
}

template<typename T>
inline T &SystemStates<T>::sgetx(const long index)
{
	if ( (index >= 0) && (index < (long)this->x.size()) )
		return this->x[index];
	else
		throw SystemStatesIndexError();
}

template<typename T>
inline T SystemStates<T>::sgetx(const long index) const
{
	if ( (index >= 0) && (index < (long)this->x.size()) )
		return this->x[index];
	else
		throw SystemStatesIndexError();
}

template<typename T>
inline T &SystemStates<T>::sgety(const long index)
{
	if ( (index >= 0) && (index < (long)this->y.size()) )
		return this->y[index];
	else
		throw SystemStatesIndexError();
}

template<typename T>
inline T SystemStates<T>::sgety(const long index) const
{
	if ( (index >= 0) && (index < (long)this->y.size()) )
		return this->y[index];
	else
		throw SystemStatesIndexError();
}

template<typename T>
inline void SystemStates<T>::ssetx(const long index, T value)
{
	this->getx(index) = value;
	return;
}

template<typename T>
inline void SystemStates<T>::ssety(const long index, T value)
{
	this->gety(index) = value;
	return;
}



/* size */

template<typename T>
inline long SystemStates<T>::sizex(void) const
{
	return (long)this->x.size();
}

template<typename T>
inline long SystemStates<T>::sizey(void) const
{
	return (long)this->y.size();
}


/* Affichage */

template<typename T>
inline void SystemStates<T>::toString(std::string &string)
{
	this->toString(string,2,6,' ');
	return;
}

template<typename T>
inline void SystemStates<T>::toString(std::string &string, int precision, int width , char separator = ' ')
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
	int i;

	oss.setf(std::ios::fixed, std::ios::floatfield);
	oss.setf(std::ios::left, std::ios::adjustfield);

	if ( (this->sizex() <= 0) && (this->sizey() <= 0) )
		return;

	if (string.length() > 0)
		string += separator;

	if (this->sizex() > 0)
	{
		oss.precision(precision);
		oss.width(width);
		oss << this->getx(0);
		string += oss.str();
		oss.str("");

		for(i = 1; i < this->sizex(); ++i)
		{
			oss.precision(precision);
			oss.width(width);
			oss << this->getx(i);
			string += separator + oss.str();
			oss.str("");
		}
	}

	if (this->sizey() > 0)
	{
		if (this->sizex() > 0)
			string += separator;
		
		oss.precision(precision);
		oss.width(width);
		oss << this->gety(0);
		string += oss.str();
		oss.str("");

		for(i = 1; i < this->sizey(); ++i)
		{
			oss.precision(precision);
			oss.width(width);
			oss << this->gety(i);
			string += separator + oss.str();
			oss.str("");
		}
	}

	
}
/* FIXME
template<typename T>
inline std::string SystemStates<T>::toString(std::string &string)
{
	std::string ret = string;

	this->toString(ret);

	return ret;
}

template<typename T>
inline std::string SystemStates<T>::toString(std::string &string, int precision, int width, char separator = ' ')
{
	std::string ret = string;

	this->toString(ret,precision,width,separator);

	return ret;	
}

template<typename T>
inline std::string SystemStates<T>::toString(int precision, int width, char separator = ' ')
{
	std::string ret = "";

	this->toString(ret,precision,width,separator);

	return ret;
}
*/


#endif

