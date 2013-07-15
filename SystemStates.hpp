#ifndef __SYSTEMSTATES_HPP__
#define __SYSTEMSTATES_HPP__

/*	SystemStates.hpp
 *
 *		Fournit une classe de manipulation de vecteurs d'état. Elle est composé
 * de deux vecteurs x et y. Le vecteur x correspond aux variables d'état du
 * système (c.a.d. les variables qui évoluent par l'action d'un intégrateur)
 * tandis que le vecteur y correspond aux sorties du système (c.a.d. les
 * variables qui n'évoluent pas par l'action d'un intégrateur).
 *
 *		Il est tout à fait possible d'avoir un système sans variables de sortie
 * ou un système sans variables d'état.
 *
 *		SystemStates utilise un template afin d'être compatible avec tous les
 * type possibles : il est ainsi possible d'utiliser tous les types standards
 * (p.e. int, float, double, ...) de C++. Il est aussi possible d'utiliser des
 * types personnalisés à condition qu'ils surchargent les opérateurs
 * arithmétiques et d'affectation. Afin de pouvoir utiliser toString (qui
 * utilise un objet "std::ostringstream" pour faire la convertion de type) il 
 * est nécessaire de faire une surcharge de l'opérateur de flux << compatible
 * avec "std::ostringstream".
 *
 *	Adrien KERFOURN (2013)
 */


/* TODO FIXME
 * 		Les assesseurs de SystemStates renvois une référence permettant la
 * modification. Il faudrait peut-être essayer d'avoir une seconde version
 * renvoyant une copie de l'élement ?
 * 		Problème : si T est une classe particulière, comment va fonctionner
 * la recopie ?
 *
 * 		Ici le constructeur par recopie ne fait qu'adapter les dimensions. Je ne
 * pense pas que ce soit le comportement attendu par défaut ! Il faut faire une
 * vrai copie ( this->copy(ref) ).
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

		std::vector<T> x;	// Variables d'état du système.
		std::vector<T> y;	// Sorties du système.

	public:

		SystemStates(void);
		SystemStates(const long nstates);
		SystemStates(const long nstates, const long noutput);
		SystemStates(SystemStates<T> &ref);
		virtual ~SystemStates(void){};

		virtual inline void resize(void);
		virtual inline void resize(const long nstates);
		virtual inline void resize(const long nstates, const long noutput);
		virtual inline void resize(SystemStates<T> &fromstates);

		virtual inline void copy(SystemStates<T> &fromstates);

		inline T &operator[](const long index);				// Équivalent à un getx(...).
		inline T operator[](const long index) const;		// TODO ? comprendre cette construction

		inline T &operator()(const long index);				// Équivalent à un gety(...).
		inline T operator()(const long index) const;		// TODO ? comprendre cette construction

		inline bool operator==(SystemStates<T> const &other);	// TODO : Tester !
		inline bool operator!=(SystemStates<T> const &other);	// TODO : Tester !


		/* Attention, il n'y a pas de vérification d'indice pour ces assesseurs
		 * et mutateurs :
		 */
		inline T &getx(const long index);
		inline T getx(const long index) const;
		inline T &gety(const long index);
		inline T gety(const long index) const;
		inline void setx(const long index, const T value);
		inline void sety(const long index, const T value);

		/* Par contre, ces assesseurs et mutateurs effectuent une vérification 
		 * d'indice (renvoie une exception de type SystemStatesIndexError en cas
		 * de problème) :
		 */
		inline T &sgetx(const long index);
		inline T sgetx(const long index) const;
		inline T &sgety(const long index);
		inline T sgety(const long index) const;
		inline void ssetx(const long index, const T value);
		inline void ssety(const long index, const T value);

		inline long sizex(void);
		inline long sizey(void);

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
		inline void toString(std::string &string);
		inline void toString(std::string &string, int precision, int width, char separator);
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
SystemStates<T>::SystemStates(const long nstates)
{
	this->resize(nstates);
	return;
}

template<typename T>
SystemStates<T>::SystemStates(const long nstates, const long noutput)
{
	this->resize(nstates, noutput);
	return;
}

template<typename T>
SystemStates<T>::SystemStates(SystemStates<T> &ref)
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
inline void SystemStates<T>::resize(const long nstates)
{
	this->resize(nstates,0);
	return;
}

template<typename T>
inline void SystemStates<T>::resize(const long nstates, const long noutput)
{
	if ( (nstates >= 0) && (noutput >= 0) )
	{
		this->x.resize(nstates);
		this->y.resize(noutput);
	}
	else
		throw SystemStatesIndexError();

	return;
}

template<typename T>
inline void SystemStates<T>::resize(SystemStates<T> &fromstates)
{
	this->resize(fromstates.sizex(), fromstates.sizey());
	return;
}



/* Copie */

template<typename T>
inline void SystemStates<T>::copy(SystemStates<T> &fromstates)
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



/* Surcharges d'opérateurs */

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

	/* Vérification des x (un à un) : */
	for(i = 0; i < this->sizex(); ++i)
	{
		if (this->getx(i) != other.gety(i)) return false;
	}

	/* Vérification des y (un à un) : */
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



/* geteurs et seteur */

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
inline long SystemStates<T>::sizex(void)
{
	return (long)this->x.size();
}

template<typename T>
inline long SystemStates<T>::sizey(void)
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

