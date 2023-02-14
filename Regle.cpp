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
    /**
     * \fn      Regle()
     * \brief   Constructeur de la classe Règle
     *
     *      Constructeur d'un objet de la classe copléenne Règle, qui contient 2 listes de type 'TypeFait'
     *      où sont stockés respectivement les prémisses et les conclusions. L'objet contient aussi 2
     *      accesseurs à ces listes.
     */
	Regle::Regle() { }

	/**
	 * \fn          Regle(const Regle & r)
	 * \brief       Constructeur de copie de la classe Règle
	 * @param[in]   r qui est une référence à un objet de la classe Règle
	 * @param[out]  r la même référence à l'objet contenant les données copiées
	 *
	 *      Le constructeur de copie creer un objet de la classe règle, dont l'objet
	 *      passé en (aussi de la classe Règle), sera copié en profondeur dans celui-ci.
	 */
	Regle::Regle(const Regle & r)
	{
        if(this != &r )
        {
            copierListesPremissesConclusions(r);
        }
	}

	/**
	 * \fn      ~Regle()
	 * \brief   destructeur de l'objet de la classe Règle
	 *
	 *      Le destructeur détruit l'objet de la classe Règle ainsi que tous ses attributs et
	 *      conteneurs.
	 *
	 */
	Regle::~Regle() { }

	/**
	 * \fn          operator = (const Regle & r)
	 * \brief       surcharge de l’opérateur =
	 * @param[in]   r est un objet de la classe Règle dont les données seront copiées
	 * @return[out] *this qui est un pointeur sur l'objet contenant les données copiées.
	 *
	 *      La méthode de surcharge de l'opérateur = utilse la méthode 'copierListesPremissesConclusions'
	 *      pour copier chaque élément dans les listes Premisses et Conclusions de l'objet r dans les
	 *      listes Premisses et Conclusions de l'objet créer this
	 */
	Regle & Regle::operator = (const Regle & r)
	{
        if(this != & r)
        {
            copierListesPremissesConclusions(r);
        }
		return *this;
	}

	/**
	 * \fn          operator == (const Regle & r) const
	 * \brief       surcharge de l’opérateur ==
	 * @param[in]   r qui est un objet de la classe Règle à être comparer avec l'objet en question (this)
	 * @return[out] true qui est un booléen si les 2 objets contiennent les mêmes données, sinon false.
	 *
	 *       La méthode de surcharge de l'opérateur == compare, via un itérateur, chaque élément dans les listes
	 *       Premisses et Conclusions de chacun des 2 objets. S'ils sont tous identiques la méthode retourne le
	 *       booleen 'true' sinon false.
	 */
	bool Regle::operator == (const Regle & r) const
	{
        for(auto it_this = this->premisses.begin(); it_this != this->premisses.end(); ++it_this)
        {
            for(auto it_r = r.premisses.begin(); it_r != r.premisses.end(); ++it_r)
            {
                if(*it_this != *it_r)
                {
                    return false;
                }
            }
        }

        for(auto it_this = this->conclusions.begin(); it_this != this->conclusions.end(); ++it_this)
        {
            for(auto it_r = r.conclusions.begin(); it_r != r.conclusions.end(); ++it_r)
            {
                if(*it_this != *it_r)
                {
                    return false;
                }
            }
        }
        return true;
	}

    /**
     * \fn          operator != (const Regle & r) const
     * \brief       surcharge de l’opérateur !=
     * @param[in]   r qui est un objet de la classe Règle à être comparer avec l'objet en question (this)
     * @return[out] true qui est un booléen si les 2 objets ne contiennent pas les mêmes données, sinon false.
     *
     *       La méthode de surcharge de l'opérateur == compare, via un itérateur, chaque élément dans les listes
     *       Premisses et Conclusions de chacun des 2 objets. S'ils ne sont pas tous identiques la méthode retourne
     *       le booleen 'true' sinon false.
     */
	bool Regle::operator != (const Regle& r) const
	{
        for(auto it_this = this->premisses.begin(); it_this != this->premisses.end(); ++it_this)
        {
            for(auto it_r = r.premisses.begin(); it_r != r.premisses.end(); ++it_r)
            {
                if(*it_this == *it_r)
                {
                    return false;
                }
            }
        }

        for(auto it_this = this->conclusions.begin(); it_this != this->conclusions.end(); ++it_this)
        {
            for(auto it_r = r.conclusions.begin(); it_r != r.conclusions.end(); ++it_r)
            {
                if(*it_this == *it_r)
                {
                    return false;
                }
            }
        }
        return true;
	}

    // Méthodes

    /**
     * \fn          copierListesPremissesConclusions(const Regle & p_objetACopie)
     * \brief       méthode pour copier les éléments dans un liste à une autre liste
     * @param[in]   p_objetACopie qui est un objet de la classe Règle dont les données seront copiées
     *
     *      Cette méthode copie chaque élément de la liste Premisses de l'objet passé en paramètre dans
	 *      la liste Premisses de l'objet en question. Ensuite il répète la même chose pourn la liste
     *      Conclusions de l'objet passé en paramètre.
     */
    void Regle::copierListesPremissesConclusions(const Regle & p_objetACopie)
    {
        this->premisses.clear();
        this->conclusions.clear();

        for (auto it_tf = p_objetACopie.premisses.begin(); it_tf != p_objetACopie.premisses.end(); ++it_tf)
        {
            this->premisses.push_back(*it_tf);
        }
        for (auto it_tf = p_objetACopie.conclusions.begin(); it_tf != p_objetACopie.conclusions.end(); ++it_tf)
        {
            this->conclusions.push_back(*it_tf);
        }
    }
}
