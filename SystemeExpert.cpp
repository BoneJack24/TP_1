/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author IFT-2008 & Étudiant(e)
 * \version 0.1
 * \date fév. 2023
 *
 */

#include "SystemeExpert.h"

namespace tp1
{
    // Compléter les méthodes demandées et corriger éventuellement la valeur de retour !
    // Ajouter aussi les balises Doxygen et commenter bien vos méthodes.

	//constructeur
	SystemeExpert::SystemeExpert()
	{
	}

	//destructeur
	SystemeExpert::~SystemeExpert()
	{
	}

	//constructeur de copie
	SystemeExpert::SystemeExpert(const SystemeExpert & se)
	{
	}

	// surcharge de l'opérateur =
	SystemeExpert & SystemeExpert::operator = (const SystemeExpert & se)
	{
		return *this;
	}

	// Permet d'ajouter la règle tr (déjà créée et initialisée) au système expert
	void SystemeExpert::ajouterRegleSE(const Regle & tr)
	{
	}

	// Permet d'ajouter le fait tf (déjà créé et initialisé) au système expert
	void SystemeExpert::ajouterFaitSE(const TypeFait & tf)
	{
	}

	/*	La méthode fournie chargerSE permet de charger un système expert à partir d'un fichier texte reçu en paramètre.
		Le fichier EntreeFichier a déjà été ouvert à l'aide de la méthode "open", préalablement à l'appel de la fonction "chargerSE"
	*/
	void SystemeExpert::chargerSE(std::ifstream & EntreeFichier)
	{
		Regle regle;		// Règle qui sera ajoutée au Système Expert.
		TypeFait faitLu;	// fait qui sera ajoutée soit à 'regle' soit à la base de faits.
		int section = 1;	// section 1: Premisses d'une règle.
							// section 2: Conclusions d'une règle.
							// section 3: Faits de base.

		// Vérifier si le fichier est ouvert en lecture
		if (!EntreeFichier.is_open()) throw std::logic_error("chargerSE: le fichier n'est pas ouvert");


		while(!EntreeFichier.eof()) // Jusqu'à ce qu'on ai atteint la fin du fichier
		{
			getline(EntreeFichier, faitLu);
			if (faitLu[0] == '!')	// Dans le format du fichier, le caractère '!'
			{						// indique un changement de section
				if (faitLu[1] == '>')	// "!>" indique que la prochaine section 
					section = 2;		// contient des conclusions.
				else
				{
					// La dernière section contenait des conclusions donc on
					// vient de finaliser une règle.  On l'ajoute maintenant au Système Expert
					ajouterRegleSE(regle);
					//Vider la règle en supprimant ses prémisses et ses conclusions
					regle.GetPremisses().clear();
					regle.GetConclusions().clear();
					
					section = (faitLu[1] == '%') ? 1 : 3; 
					// "!%" indique que la prochaine section contient 
					//	des premisses.
					// "!!" indique que la prochaine section contient 
					//	des faits.
				}

				getline(EntreeFichier, faitLu);
			}

			switch (section)
			{
				case 1:  // Ajout d'une premisse à une règle
					regle.GetPremisses().push_back(faitLu);
					break;

				case 2:	// Ajout d'une conclusion à une règle
					regle.GetConclusions().push_back(faitLu);
					break;
					
				case 3:	// Ajout d'un fait à la base de faits
					ajouterFaitSE(faitLu);
					break;
			}
		}
	}

	/*	La méthode chainageAvant permet de saturer la base de faits du système expert se en retrouvant
		les faits qui peuvent être déduits de la base de faits du système expert en question
		et en se basant sur les règles de celui-ci. Cette fonction retourne donc l’ensemble de règles qui ont
		permis à déduire de nouveaux faits.
		Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
	    Attention: er est passé par référece, donc elle est accessible par la méthode appelante (le main dans notre cas: voir case 6).
	*/
	void SystemeExpert::chainageAvant(std::vector<Regle> & er)
	{
	}

    /*	La méthode chainageArriere est une fonction récursive qui permet de démontrer
        la véracité du fait hypothese en se basant sur les faits et les règles du système expert.
        Si celui-ci est démontré, la valeur VRAI est retournée dans demontre, FAUX sinon.
        Les règles qui ont permis de déduire de nouveaux faits sont retournées dans l’ensemble de règles.
        Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
    */
    std::vector<Regle> SystemeExpert::chainageArriere (const TypeFait & hypothese, bool & demontre)
    {
        std::vector<Regle> regles;
        return regles;
    }
}
