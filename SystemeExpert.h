/////////////////////////////////////////////////////////////////////////////
//Fichier SystemeExpert.h
/////////////////////////////////////////////////////////////////////////////
/**
 * \file SystemeExpert.h
 * \brief Ce fichier contient une définition de la classe SystemeExpert
 * \author IFT-2008
 * \version 0.1
 * \date fév. 2023
 *
 * Ce fichier contient l'inteface d'un systeme expert permettant
 *	à partir de premisses de trouver des conclusions qui permettent
 *	finalement d'affirmer ou d'infirmer des reponses.
 *	Le systeme expert emploie les definitions de l'ensemble de regles et
 *	de l'ensemble de faits.
 *	A partir d'une comparaison systematique des faits aux regles connues,
 *	nous serons à meme de déduire des faits nouveaux.
 */

#ifndef _SYSTEMEEXPERT_H
#define _SYSTEMEEXPERT_H

#include <iostream>
#include <fstream>
#include "Regle.h"
#include <vector>
#include <list>
#include <algorithm>

namespace tp1
{

class SystemeExpert{

  public:

	SystemeExpert(); //constructeur
	~SystemeExpert(); //destructeur
	SystemeExpert(const SystemeExpert & se); //constructeur de copie
	SystemeExpert & operator = (const SystemeExpert & se); // surcharge de l’opérateur =

	// Surcharge de l’opérateur <<
	// Ne pas toucher à cette méthode
	friend std::ostream & operator << (std::ostream & os, const SystemeExpert & se)
	{
		os << "Base de regles:" << std::endl;

		if (se.baseRegles.empty())
            os << "La base de regles est vide" << std::endl;
		else
		{
            int nb = 1;
            for (auto itr = se.baseRegles.begin(); itr!= se.baseRegles.end(); ++itr)
            {
                os << "Regle numero " << nb << ": " << std::endl;
                os << *itr << std::endl;
                nb++;
            }
		}

		os << "Base de faits:" << std::endl;

		if(se.baseFaits.empty())
			os << "La base de faits est vide" << std::endl;
		else
		{
			for (auto itr = se.baseFaits.begin(); itr!= se.baseFaits.end(); ++itr)
			    os << *itr << std::endl;
		}

		return os;
	}

	// Permet d'ajouter la règle tr (déjà créée et initialisée) au système expert
	// Ne rien faire si la règle existe déjà !
	void ajouterRegleSE(const Regle & tr);

	// Permet d'ajouter le fait tf (déjà créé et initialisé) au système expert
	// Ne rien faire si le fait existe déjà !
	void ajouterFaitSE(const TypeFait & tf);

    /*	La méthode fournie chargerSE permet de charger un système expert à partir d'un fichier texte reçu en paramètre.
        Le fichier EntreeFichier a déjà été ouvert à l'aide de la méthode "open", préalablement à l'appel de la fonction "chargerSE".
    */
    void chargerSE(std::ifstream & EntreeFichier);

    /*	La méthode chainageAvant permet de saturer la base de faits du système expert se en retrouvant
        les faits qui peuvent être déduits de la base de faits du système expert en question
        et en se basant sur les règles de celui-ci. Cette fonction retourne (par référence) le vecteur de règles qui ont
        permis à déduire de nouveaux faits.
        Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
		Attention: er est passé par référece, donc elle est accessible par la méthode appelante (le main dans notre cas: voir case 6).
    */
	void chainageAvant(std::vector<Regle> & er);

    /*	La méthode chainageArriere est une fonction récursive qui permet de démontrer
        la véracité du fait hypothèse en se basant sur les faits et les règles du système expert.
        Si celui-ci est démontré, la valeur VRAI est retournée dans demontre, FAUX sinon.
        Les règles qui ont permis de déduire de nouveaux faits sont retournées dans le vecteur de règles.
        Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
    */
    std::vector<Regle> chainageArriere (const TypeFait& hypothese, bool& demontre);

	//Accesseurs
    std::vector<Regle> & getBaseRegles () {return baseRegles;}
	std::list<TypeFait> & getBaseFaits () {return baseFaits;}

    // Méthodes

    void copierConteneursDeDonnees(const SystemeExpert & p_objetACopie);

    int compteurLignesTxt(const TypeFait p_Texte) const;
    bool conclusionEstPremierElementDansPremisse(const TypeFait p_Conclusion, const TypeFait p_Premisse) const;
    bool faitEstDansPremisse(const TypeFait p_Fait, const TypeFait p_Premisse) const;
    TypeFait concatenerPremisses(std::list<TypeFait> p_liste);
    TypeFait concatenerConclusions(std::list<TypeFait> p_liste);


  private:

    std::vector<Regle> baseRegles;	//Contient toutes les règles connues du système expert (utilise un vector de la STL)
    std::list<TypeFait> baseFaits;	//Contient tous les faits connus du système expert (utilise une list de la STL)

   //Ajouter ici des fonctions utilitaires si nécessaire.

    bool p_hypotheseDansConclusionRegle = false; // booléen qui sert d'indicateur aux méthodes, si l'hypothèse a été
                                                // trouvée dans la règle en évaluation.
    bool p_elementDansListeFaits = false;   // booléen qui sert d'indicateur aux méthodes, s'il y a au moins un fait,
                                            // des prémisses de la règle, qui se retrouve dans la lise de faits de l'objet.
    std::list<TypeFait> pl_FaitsTampon; // vecteur contenant les faits des premisses de la règle en évaluation par le programme.
    std::list<TypeFait> p_lFaitsListeComparative;   // liste ou on ajoute les faits qui se retrouve autant dans la liste
                                                    // des premisses que dans la liste des faits de l'objet. Servira de
                                                    // comparaison avec la liste de faits de l'objet pour valider l'hypothèse.
    int i_regle = -1; // iterateur pour connaître la position de la regle dans le vecteur 'regles'
    tp1::TypeFait m_hypothese; // hypothèse qui est en évaluation par le programme
    std::vector<Regle> m_regles; // vecteur contenant les regles utilisée pour la validation d'une hypothèse
    int p_tailleVReglesEntree; // taile du vecteur à l'entrée de l'évaluation d'une hypopthèse
    int p_tailleVReglesSortie; // taille du vecteiur à la sortie de l'évaluation d'une hypthèse

    TypeFait m_conclusion = "";
    TypeFait m_conclusionTronquee = "";
    int compteur = 0;

};

}

#endif
