#ifndef __SYSTEMSTATES_HPP__
#define __SYSTEMSTATES_HPP__

/*	SystemStates.hpp
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
 */

#include <vector>

#include <string>
#include <sstream>

template<typename T>
class SystemStates
{
	protected:

		std::vector<T> mx;

	public:

		SystemStates(void);
		SystemStates(const long nbstates);
		SystemStates(const SystemStates<T> &ref);
		virtual ~SystemStates(void){};

		inline T &at(const long index);
		inline T at(const long index) const;

		inline T &operator[](const long index);
		inline T operator[](const long index) const;

		inline long size(void) const;

		inline void resize(const long nbstates);
		inline void resize(const SystemStates<T> &fromstates);

		inline void copy(const SystemStates<T> &fromstates);
	
		// TODO inline SystemStates& operator=(SystemStates<T> const &other);
		inline bool operator==(SystemStates<T> const &other);	// TODO : Test !
		inline bool operator!=(SystemStates<T> const &other);	// TODO : Test !


		

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
//	this->resize(0);
	return;
}

template<typename T>
SystemStates<T>::SystemStates(const long nbstates)
{
	this->resize(nbstates);
	return;
}

template<typename T>
SystemStates<T>::SystemStates(const SystemStates<T> &ref)
{
	this->copy(ref);
	return;
}


/* Access */

template<typename T>
inline T& SystemStates<T>::at(const long index)
{
	return this->mx.at(index);
}

template<typename T>
inline T SystemStates<T>::at(const long index) const
{
	return this->mx.at(index);
}

template<typename T>
inline T& SystemStates<T>::operator[](const long index)
{
	return this->mx.at(index);
}

template<typename T>
inline T SystemStates<T>::operator[](const long index) const
{
	return this->mx.at(index);
}



template<typename T>
inline long SystemStates<T>::size(void) const
{
	return this->mx.size();
}

/* Initialisations */

template<typename T>
inline void SystemStates<T>::resize(const long nbstates)
{
	this->mx.resize(nbstates);
	return;
}

template<typename T>
inline void SystemStates<T>::resize(const SystemStates<T> &fromstates)
{
	this->resize(fromstates.size());
	return;
}




template<typename T>
inline void SystemStates<T>::copy(const SystemStates<T> &fromstates)
{
	long i;

	this->resize(fromstates.size());

	for(i = 0; i < fromstates.size(); ++i)
	{
		this->at(i) = fromstates[i];
	}

	return;
}



/* Operators overload */

template<typename T>
inline bool SystemStates<T>::operator==(SystemStates<T> const &other)
{
	long i;
	if ( this->size() != other.size() )
	{
		return false;
	}

	/* Checks each x (one by one) : */
	for(i = 0; i < this->size(); ++i)
	{
		if (this->at(i) != other.at(i) ) return false;
	}

	return true;
}

template<typename T>
inline bool SystemStates<T>::operator!=(SystemStates<T> const &other)
{
	return !(*this == other);
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

	if ( (this->size() <= 0) && (this->size() <= 0) )
	{
		return;
	}

	if (string.length() > 0)
	{
		string += separator;
	}

	if (this->size() > 0)
	{
		oss.precision(precision);
		oss.width(width);
		oss << this->at(0);
		string += oss.str();
		oss.str("");

		for(i = 1; i < this->size(); ++i)
		{
			oss.precision(precision);
			oss.width(width);
			oss << this->at(i);
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

