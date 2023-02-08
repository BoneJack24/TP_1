/////////////////////////////////////////////////////////////////////////////
//Fichier Regle.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Regle.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Regle
 * \author IFT-2008 & Étudiant(e)
 * \version 0.1
 * \date fév. 2023
 *
 */

#include "Regle.h"

namespace tp1
{
    // Compléter les méthodes demandées et corriger éventuellement la valeur de retour !
    // Ajouter aussi les balises Doxygen et commenter bien vos méthodes.

	//Constructeur de la classe Regle
	Regle::Regle()
	{
	}

	//Constructeur de copie.
	Regle::Regle(const Regle & r)
	{
	}

	//Destructeur
	Regle::~Regle()
	{
	}

	// surcharge de l’opérateur =
	Regle & Regle::operator = (const Regle & r)
	{
		return *this;
	}

	// surcharge de l’opérateur ==
	bool Regle::operator == (const Regle& r) const
	{
	    return true;
	}

	// surcharge de l’opérateur !=
	bool Regle::operator != (const Regle& r) const
	{
	    return true;
	}

}
