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

    /**
     * \fn      SystemeExpert
     * \brief   constructeur d'un objet de la classe SystemeExpert
     */
    SystemeExpert::SystemeExpert() {}

    /**
     * \fn          ~SystemeExpert
     * \brief       destructeur de l'objet de la classe
     */
    SystemeExpert::~SystemeExpert() {
    }

    /**
     * \fn              SystemeExpert
     * \brief           constructeur de copie de la classe
     * @param[in] se    objet de la classe SystemeExpert vers lequel sera copié l'objet courant
     */
    SystemeExpert::SystemeExpert(const SystemeExpert &se)
    {
        if (this != &se)
        {
            copierConteneursDeDonnees(se);
        }
    }

    /**
     * \fn              operator=
     * \brief           surcharge de l'opérateur =
     * @param[in] se    objet de la classe SystemeExpert
     * @return          copie de l'objet passé en paramète dans l'objet courant
     */
    SystemeExpert &SystemeExpert::operator=(const SystemeExpert &se)
    {
        if (this != &se)
        {
            copierConteneursDeDonnees(se);
        }
        return *this;
    }

    /**
     * \fn              ajouterRegleSE
     * \brief           méthode qui permet d'ajouter une règle au système expert
     * @param[in] tr    objet de la classe Règle contenant la règle à ajouter
     */
    void SystemeExpert::ajouterRegleSE(const Regle &tr) {
        // TROUVER UNE MANIERE DE VÉRIFIER SI LA REGLE EXISTE DÉJÀ (Ex Iterateur avec operateur ==)
        this->getBaseRegles().push_back(tr);
    }

    /**
     * \fn              ajouterFaitSE
     * \brief           méthode qui permet d'ajouter un fait dans la base de faits
     * @param[in] tf    TypeFait (string) qui contient le fait à ajouter au systeme expert
     */
    void SystemeExpert::ajouterFaitSE(const TypeFait &tf) {
        // TROUVER UNE MANIERE DE VÉRIFIER SI LA REGLE EXISTE DÉJÀ (Ex Iterateur avec operateur ==)
        this->getBaseFaits().push_back(tf);
    }

    /**
     * \fn                      chargerSE
     * \brief                   méthode qui permet de charger un fichier contentant les données utilisé par le
     *                          Systeme Expert
     * @param[in] EntreeFichier InputFileStream du fichier
     *
     *      La méthode fournie chargerSE permet de charger un système expert à partir d'un fichier texte reçu en paramètre.
     *      Le fichier EntreeFichier a déjà été ouvert à l'aide de la méthode "open", préalablement à l'appel de la fonction
     *      "chargerSE"
    */
    void SystemeExpert::chargerSE(std::ifstream &EntreeFichier) {
        Regle regle;        // Règle qui sera ajoutée au Système Expert.
        TypeFait faitLu;    // fait qui sera ajoutée soit à 'regle' soit à la base de faits.
        int section = 1;    // section 1: Premisses d'une règle.
        // section 2: Conclusions d'une règle.
        // section 3: Faits de base.

        // Vérifier si le fichier est ouvert en lecture
        if (!EntreeFichier.is_open()) throw std::logic_error("chargerSE: le fichier n'est pas ouvert");


        while (!EntreeFichier.eof()) // Jusqu'à ce qu'on ai atteint la fin du fichier
        {
            getline(EntreeFichier, faitLu);
            if (faitLu[0] == '!')    // Dans le format du fichier, le caractère '!'
            {                        // indique un changement de section
                if (faitLu[1] == '>')    // "!>" indique que la prochaine section
                    section = 2;        // contient des conclusions.
                else {
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

            switch (section) {
                case 1:  // Ajout d'une premisse à une règle
                    regle.GetPremisses().push_back(faitLu);
                    break;

                case 2:    // Ajout d'une conclusion à une règle
                    regle.GetConclusions().push_back(faitLu);
                    break;

                case 3:    // Ajout d'un fait à la base de faits
                    ajouterFaitSE(faitLu);
                    break;
            }
        }
    }
    /**
     *
     * \fn              chainageAvant
     * \brief           méthode qui déduit des règles selon des faits donnés
     * @param[in] er    vecteur contenant des objets de la classe Règle.
     *
     *	    La méthode chainageAvant permet de saturer la base de faits du système expert se en retournant
     *      les faits qui peuvent être déduits de la base de faits du système expert en question
     *      et en se basant sur les règles de celui-ci. Cette fonction retourne donc l’ensemble de règles qui ont
     *      permis à déduire de nouveaux faits.
    */
    void SystemeExpert::chainageAvant(std::vector<Regle> &er) {
        int compteur = 1; // variable de compteur de faits pour une prémisse d'une règle.
        int tailleVecteurRegle = baseRegles.size();
        int nbreLignesPremisse;
        tp1::TypeFait p_conclusion = ""; // variable contenant une conclusion.
        tp1::TypeFait p_conclusionRegleValidee;
        tp1::TypeFait p_fait; // variable contenant un fait.
        tp1::TypeFait p_premisse; // variable contenant une prémisse.

        // Assignation du premier élément de la lise basesFaits
        std::list<tp1::TypeFait>::iterator it = baseFaits.begin(); // Création d'un iterateur sur une liste de type TypeFait
        p_fait = *it; // Assignation de l'élément à la variable de TypeFait

        // Boucle qui passe au travers chaque règle de la base de Règle
        for (int i = 0; i < tailleVecteurRegle; ++i) {
            std::cout << "Le programme entre dans la boucle for sur chaque règle" << std::endl;
            std::cout << "Le fait en évaluation est : " << p_fait << std::endl;
            std::cout << "La valeur de i est : " << i << std::endl;
            // Assignation de la premisse à la liste tampon d'une règle
            std::list<TypeFait> listeTamponPremisses = baseRegles[i].GetPremisses(); // Assignation d'une règle du vecteur baseRegles.
            std::list<TypeFait>::iterator it_ListeTamponPrem = listeTamponPremisses.begin(); // Création d'un iterateur sur une liste de type TypeFait
            std::list<TypeFait> listeTamponConclusion = baseRegles[i].GetConclusions(); // Assignation d'une règle du vecteur baseRegles.
            std::list<TypeFait>::iterator it_ListeTamponConc = listeTamponConclusion.begin(); // Création d'un iterateur sur une liste de type TypeFait
            p_premisse = concatenerPremisses(listeTamponPremisses);
            std::cout << "La premisse est : " << p_premisse << std::endl;
            p_conclusion = concatenerConclusions(
                    listeTamponConclusion); // ** VOIR SI ON DOIT ITERER OU NON SI JAMAIS UNE REGLE A PLUSIEURS PRÉMISSES
            std::cout << "La conclusion de cette prémisse est : " << p_conclusion << std::endl;
            nbreLignesPremisse = compteurLignesTxt(p_premisse);
            std::cout << "Il y a " << nbreLignesPremisse << " lignes dans la premisse en évaluation." << std::endl;

            // Validation du fait dans la règle sur laquelle le programme est en train d'itérer

            // option 1 - si le fait pointé par l'itérateur sur la base de Faits est inclus dans la prémisse de la règle en évaluation
            //            et qu'il y a seulement un élément dans cette prémisse.
            //              1-) assigner la conclusion à la variable de la conclusion
            //              2-) copier la règle dans le vecteur passer par référence en paramêtre
            //              3-) ajouter la conclusion dans la liste de la base de Faits de l'objet courant (se2)
            //              4-) passer à l'évaluation du fait suivant.

            if (nbreLignesPremisse == 1) {
                if (faitEstDansPremisse(p_fait, p_premisse)) {
                    std::cout << "L'Option 1 est utilisée pour valider cette prémisse" << std::endl;
                    std::cout << "La règle de l'option 1 est validée et la conclusion est : " << p_conclusion
                              << std::endl;
                    p_conclusionRegleValidee = p_conclusion;
                    er.push_back(
                            baseRegles[i]); // ** POURRAIT ETRE LA FONCTION ajouterReglesSE MAIS DERVRA ETRE MODIFIÉ
                    baseFaits.push_back(
                            p_conclusion); // ** POURRAIT ETRE LA FONCTION ajouterFaitsSE MAIS PEUT-ÊTRE DERVRA ETRE MODIFIÉ
                    advance(it, 1);
                    p_fait = *it;
                }
            }

            // option 2 - si la conclusion de la règle précédente et le fait pointé par l'itérateur sur la base de Faits sont
            //            inclus dans la prémisse de la règle en évaluation et que la conclusion est le premier élément de la
            //            prémisse et qu'il y a seulement 2 éléments dans cette prémisse.
            //              1-) assigner la conclusion à la variable de la conclusion
            //              2-) copier la règle dans le vecteur passer par référence en paramêtre
            //              3-) ajouter la conclusion dans la liste de la base de Faits de l'objet de l'objet courant (se2)
            //              4-) passer à l'évaluation du fait suivant.

            if (nbreLignesPremisse == 2) {
                std::cout << "L'Option 2 est utilisée pour valider cette prémisse" << std::endl;
                if (conclusionEstPremierElementDansPremisse(p_conclusionRegleValidee, p_premisse) &&
                    faitEstDansPremisse(p_fait, p_premisse)) {
                    std::cout << "L'Option 2 est utilisée pour valider cette prémisse" << std::endl;
                    std::cout << "La règle de l'option 2 est validée et la conclusion est : " << p_conclusion
                              << std::endl;
                    p_conclusionRegleValidee = p_conclusion;
                    er.push_back(
                            baseRegles[i]); // ** POURRAIT ETRE LA FONCTION ajouterReglesSE MAIS DERVRA ETRE MODIFIÉ
                    baseFaits.push_back(
                            p_conclusion); // ** POURRAIT ETRE LA FONCTION ajouterFaitsSE MAIS PEUT-ÊTRE DERVRA ETRE MODIFIÉ
                    advance(it, 1);
                    p_fait = *it;
                }
            }

            // option 3 - si la conclusion de la règle précédente et le fait pointé par l'itérateur sur la base de Faits sont
            //            inclus dans la prémisse de la règle en évaluation et que la conclusion est le premier élément de la
            //            prémisse et qu'il y a plus de 2 éléments dans cette prémisse.
            //              1-) incrémenter le compteur de faits de 1
            //              2-) tant que le compteur de ligne != le nombre de ligne dans la premisse de la règle en évaluation
            //                      on passe à l'évaluation du fait suivant dans cette règle. Si le compte est bon
            //                  1-) assigner la conclusion à la variable de la conclusion
            //                  2-) copier la règle dans le vecteur passer par référence en paramêtre
            //                  3-) ajouter la conclusion dans la liste de la base de Faits de l'objet courant (se2)
            //                  4-) passer à l'évaluation du fait suivant.
            //

            if (nbreLignesPremisse > 2 &&
                conclusionEstPremierElementDansPremisse(p_conclusionRegleValidee, p_premisse)) {
                std::cout << "L'Option 3 est utilisée pour valider cette prémisse" << std::endl;
                compteur = 2;
                while (compteur <= nbreLignesPremisse - 1) {
                    std::cout << "Le fait en évaluation dans l'option 3 au début de la boucle 'while' est : " << p_fait
                              << std::endl;
                    if (faitEstDansPremisse(p_fait, p_premisse)) {
                        advance(it, 1);
                        p_fait = *it;
                        std::cout << "Le fait en évaluation dans l'option 3 est : " << p_fait << std::endl;
                        compteur += 1;
                        std::cout << "Le compteur est à la valeur : " << compteur << std::endl;
                    }
                }
                if (compteur == nbreLignesPremisse) {
                    std::cout << "La règle de l'option 3 est validée et la conclusion est : " << p_conclusion
                              << std::endl;
                    p_conclusionRegleValidee = p_conclusion;
                    er.push_back(
                            baseRegles[i]); // ** POURRAIT ETRE LA FONCTION ajouterReglesSE MAIS DERVRA ETRE MODIFIÉ
                    baseFaits.push_back(
                            p_conclusion); // ** POURRAIT ETRE LA FONCTION ajouterFaitsSE MAIS PEUT-ÊTRE DERVRA ETRE MODIFIÉ
                    advance(it, 1);
                    p_fait = *it;
                }
            }
            std::cout << std::endl;
        }
    }

    /**
     *
     * \fn                  chainageArriere(const TypeFait &hypothese, bool &demontre)
     * \brief               méthode récursive qui permet de valider une hypothèse par chainage arrière.
     * @param[in] hypothese TypeFait (string) qui contient l'hypothèse.
     * @param[in] demontre  booléen qui valide l'hypothèse.
     * @return              un vecteur contenant les règles.
     *
     *      La méthode chainageArriere est une fonction récursive qui permet de démontrer
     *      la véracité du fait hypothese en se basant sur les faits et les règles du système expert.
     *      Si celui-ci est démontré, la valeur VRAI est retournée dans demontre, FAUX sinon.
     *      Les règles qui ont permis de déduire de nouveaux faits sont retournées dans l’ensemble de règles.
    */
    std::vector<Regle> SystemeExpert::chainageArriere(const TypeFait &hypothese, bool &demontre)
    {
        std::vector<Regle> regles;
        //demontre = false; // ?????

        while((m_conclusionTronquee != hypothese) || (compteur -1 > baseFaits.size()))
        {
        std::cout<<std::endl;
        std::cout << "L'hypothèse est : " << hypothese << std::endl;
        std::cout << "L'hypothèse est démontrée? " << demontre << std::endl;
        //std::cout <<"La taille de la base de faits est : " << baseFaits.size() << std::endl;
        std::cout <<"Le compteur est à la valeur : " << compteur << std::endl;

        // 1-)  Chercher le premier élément de la liste de faits de l'objet (mémoriser sont emplacement dans une variable)
        //      et ensuite l'assigner à une variable de TypeFait 'p_vFaitsTampon' qui contiendra le(s) faits à évaluer dans
        //      les premisses d'une règle.
        pl_FaitsTampon.clear();
        std::list<TypeFait>::iterator it_faits = baseFaits.begin();
        advance(it_faits, compteur);
        std::cout << "La valeur à la position de l'itérateur est : " << *it_faits << std::endl;
        if (compteur == 0)
        {
            pl_FaitsTampon.push_back(*it_faits);
        }
        else
        {
            pl_FaitsTampon.push_back(m_conclusion);
            pl_FaitsTampon.push_back(*it_faits);
        }
        compteur += 1;

        // *** À ENLEVER DANS LE CODE FINAL ***
        std::list<TypeFait>::iterator it_print;
        std::cout << "La conclusion précédente et le fait en évaluation sont : " << std::endl;
        for (it_print = pl_FaitsTampon.begin(); it_print != pl_FaitsTampon.end(); ++it_print) {
            std::cout << *it_print << std::endl;
        }

        // 2-)  Vérifier si cet élément fait partie d'une prémisse d'une règle.

        std::vector<Regle>::iterator it_regles = baseRegles.begin();
        std::list<TypeFait> p_listePremissesTampon = baseRegles.begin()->GetPremisses();
        std::list<TypeFait>::iterator it_listeFaits = p_listePremissesTampon.begin();

        it_print = pl_FaitsTampon.begin();
        TypeFait faitFait = *it_print;

        for(int i = 0; i < baseRegles.size(); ++i)
        {
            std::list<TypeFait> p_listePremissesTampon = baseRegles[i].GetPremisses();
            std::list<TypeFait>::iterator it_lFaitsPremisses;
            TypeFait faitPremisse;
            TypeFait faitConclusion;

            std::vector<TypeFait> pv_faitsPremissesIndividuels;
            for(it_lFaitsPremisses = p_listePremissesTampon.begin(); it_lFaitsPremisses != p_listePremissesTampon.end(); ++it_lFaitsPremisses)
            {
                TypeFait test2 = *it_lFaitsPremisses;
                pv_faitsPremissesIndividuels.push_back(test2);
            }

            std::list<TypeFait>::iterator it = pl_FaitsTampon.begin();
            std::vector<TypeFait> pv_faitsVecteurTampon;
            for(it = pl_FaitsTampon.begin(); it != pl_FaitsTampon.end(); ++it)
            {
                TypeFait test3 = *it;
                pv_faitsVecteurTampon.push_back(*it);
            }
            while(pv_faitsPremissesIndividuels.size() > pv_faitsVecteurTampon.size())
            {
                pv_faitsPremissesIndividuels.pop_back();
            }

            for(it_lFaitsPremisses = p_listePremissesTampon.begin(); it_lFaitsPremisses != p_listePremissesTampon.end(); ++it_lFaitsPremisses)
            {
                if(pv_faitsPremissesIndividuels == pv_faitsVecteurTampon)
                {
                    std::list<TypeFait> p_listeConclusionTampon = baseRegles[i].GetConclusions();
                    std::list<TypeFait>::iterator it_FaitsConclusion = p_listeConclusionTampon.begin();
                    m_conclusion = *it_FaitsConclusion;
                    // 3-)  Si cet élément se retrouve dans une prémisse d'une règle ajouter la conclusion de cette règle dans le
                    //      vecteur règles.
                    regles.push_back(baseRegles[i]);
                    m_conclusionTronquee = m_conclusion;
                    m_conclusionTronquee.erase(m_conclusionTronquee.begin() + (m_conclusionTronquee.size() -1));
                    if(m_conclusionTronquee == hypothese)
                    {
                        demontre = true;
                        return regles;
                    }
                    chainageArriere(hypothese, demontre);
                }
                if ((pv_faitsPremissesIndividuels != pv_faitsVecteurTampon) && (compteur > baseFaits.size()))
                {
                    demontre = false;
                }
            }
        }
        }
        return regles;
    }
    /**
     *
     * \fn                      copierConteneursDeDonnees
     * \brief                   méthode qui copie un objet de la classe SE
     * @param[in] p_objetACopie objet de la classe SystèmeExpert
     */
    void SystemeExpert::copierConteneursDeDonnees(const SystemeExpert &p_objetACopie)
    {
        this->baseRegles.clear();
        this->baseFaits.clear();

        for (auto it_tf = p_objetACopie.baseRegles.begin(); it_tf != p_objetACopie.baseRegles.end(); ++it_tf) {
            this->baseRegles.push_back(*it_tf);
        }
        for (auto it_tf = p_objetACopie.baseFaits.begin(); it_tf != p_objetACopie.baseFaits.end(); ++it_tf) {
            this->baseFaits.push_back(*it_tf);
        }
    }

    /**
     *
     * \fn                  compteurLignesTxt
     * \brief               méthode qui compte les lignes dans un texte
     * @param[in] p_Texte   TypeFait (string), qui contient le texte
     * @return              un entier qui contient le nombre de lignes
     */
    int SystemeExpert::compteurLignesTxt(const TypeFait p_Texte) const
    {
        //std::cout<< "Le paramètre de la méthode compteurLignesTxt contient la valeur : " << p_Texte << std::endl;
        return count(p_Texte.begin(), p_Texte.end(), '\n');
    }

    /**
     * \fn                      conclusionEstPremierElementDansPremisse
     * \brief                   méthode qui valide que la conclusion est le premier élément dans une prémisse d'une règle
     * @param[in] p_Conclusion  TypeFait (string) qui contient la conclusion d'une règle
     * @param[in] p_Premisse    TypeFait (string) qui contient la prémisse d'une règle
     * @return                  booléen, vrai si la conclusion se retrouve dans une prémisse
     */
    bool SystemeExpert::conclusionEstPremierElementDansPremisse(const TypeFait p_Conclusion, const TypeFait p_Premisse) const
    {
        int taillePremisse = p_Premisse.size();
        size_t estInclus = p_Premisse.find(p_Conclusion);
        if (estInclus > taillePremisse)
        {
            return false;
        } else if (estInclus != 0)
        {
            return false;
        }
        return true;
    }

    /**
     * \fn                      faitEstDansPremisse
     * \brief                   méthode qui valide si un fait est dans une prémisse
     * @param[in] p_Fait        TypeFait (string) qui contient un fait à valider
     * @param[in] p_Premisse    TypeFait (string) qui contient la prémisse dans laquelle on veut valider si le fait est
     *                          présent
     * @return                  booléen, vrai si le fait est présent dans la prémisse
     */
    bool SystemeExpert::faitEstDansPremisse(const TypeFait p_Fait, const TypeFait p_Premisse) const {
        int taillePremisse = p_Premisse.size();
        size_t estInclus = p_Premisse.find(p_Fait);
        if (estInclus > taillePremisse)
        {
            return false;
        }
        return true;
    }

    /**
     * \fn                  concatenerPremisses
     * \brief               méthode qui enlève les sauts de lignes dans un texte
     * @param[in] p_liste   TypeFait (string) qui contient le texte à concatenner.
     * @return              TypeFait (string), qui contient la prémisse sans sauts de lignes
     */
    TypeFait SystemeExpert::concatenerPremisses(std::list<TypeFait> p_liste)
    {
        TypeFait premisse;
        std::list<TypeFait>::iterator it = p_liste.begin();
        for (it = p_liste.begin(); it != p_liste.end(); ++it)
        {
            premisse += *it + '\n';
        }
        return premisse;
    }

    /**
     * \fn                  concatenerConlusions
     * \brief               méthode qui enlève les sauts de lignes dans un texte.
     * @param[in] p_liste   TypeFait (string) qui contient le texte à concatenner.
     * @return              TypeFait (string), qui contient la conclusion sans sauts de lignes.
     */
    TypeFait SystemeExpert::concatenerConclusions(std::list<TypeFait> p_liste)
    {
        TypeFait conclusion;
        std::list<TypeFait>::iterator it = p_liste.begin();
        for (it = p_liste.begin(); it != p_liste.end(); ++it)
        {
            conclusion += *it;
        }
        return conclusion;
    }

}
