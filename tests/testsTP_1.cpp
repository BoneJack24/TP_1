//
// Created by etudiant on 23-02-08.
//

#include <iostream>
#include "Regle.h"
#include "SystemeExpert.h"
#include "gtest/gtest.h"

using namespace std;
using namespace tp1;

TEST(Regle, constructeurCopie)
{
    Regle rA;
    rA.GetPremisses().push_back("Hello");
    rA.GetConclusions().push_back("World");
    Regle rB(rA);
    EXPECT_EQ(rB.GetPremisses(), rA.GetPremisses());
    EXPECT_EQ(rB.GetConclusions(), rA.GetConclusions());
    EXPECT_NE(rB.GetPremisses(), rA.GetConclusions());
    EXPECT_NE(rB.GetConclusions(), rA.GetPremisses());
}


TEST(Regle, surchargeOperateurEgal)
{
    Regle rA;
    rA.GetPremisses().push_back("Hello");
    rA.GetConclusions().push_back("World");
    Regle rB;
    rB.GetPremisses().push_back("World");
    rB.GetConclusions().push_back("Hello");
    rA = rB;
    EXPECT_EQ(rB.GetPremisses(), rA.GetPremisses());
    EXPECT_EQ(rB.GetConclusions(), rA.GetConclusions());
    EXPECT_NE(rB.GetPremisses(), rA.GetConclusions());
    EXPECT_NE(rB.GetConclusions(), rA.GetPremisses());
}

TEST(Regle, surchargeOperateurEgalEgal)
{
    Regle rA;
    rA.GetPremisses().push_back("Hello");
    rA.GetConclusions().push_back("World");
    Regle rB;
    rB.GetPremisses().push_back("World");
    rB.GetConclusions().push_back("Hello");
    rA = rB;
    EXPECT_TRUE(rA == rB);
    EXPECT_FALSE(rA != rB);
}

TEST(Regle, surchargeOperateurNeEgalPas)
{
    Regle rA;
    rA.GetPremisses().push_back("Hello");
    rA.GetConclusions().push_back("World");
    Regle rB;
    rB.GetPremisses().push_back("World");
    rB.GetConclusions().push_back("Hello");

    EXPECT_FALSE(rA == rB);
    EXPECT_TRUE(rA != rB);
}

TEST(Regle, copierListesPremissesConclusions)
{
    Regle rA;
    rA.GetPremisses().push_back("Hello");
    rA.GetConclusions().push_back("World");
    Regle rB;
    rB.GetPremisses().push_back("World");
    rB.GetConclusions().push_back("Hello");

    rA.copierListesPremissesConclusions(rB);

    EXPECT_EQ(rB.GetPremisses(), rA.GetPremisses());
    EXPECT_EQ(rB.GetConclusions(), rA.GetConclusions());
    EXPECT_NE(rB.GetPremisses(), rA.GetConclusions());
    EXPECT_NE(rB.GetConclusions(), rA.GetPremisses());
    EXPECT_TRUE(rA == rB);
    EXPECT_FALSE(rA != rB);
}

TEST(SystemeExpert, methodeCompteurLignesTxtVrai)
{
    SystemeExpert se;
    tp1::TypeFait multiLignes = "a de la barbe\na de la peau\na des bras\na des jambes";
    EXPECT_EQ(3, se.compteurLignesTxt(multiLignes));
}

TEST(SystemeExpert, methodeCompteurLignesTxtFaux)
{
    SystemeExpert se;
    tp1::TypeFait multiLignes = "a de la barbe\na de la peau\na des bras\na des jambes";
    EXPECT_NE(4, se.compteurLignesTxt(multiLignes));
}

TEST(SystemeExpert, methodeFaitEstDansPremisseVrai)
{
    SystemeExpert se;
    tp1::TypeFait p_Premisse = "a de la barbe\na de la peau\na des bras\na des jambes";
    tp1::TypeFait p_Fait = "a de la peau";
    EXPECT_TRUE(se.faitEstDansPremisse(p_Fait, p_Premisse));
}

TEST(SystemeExpert, methodeFaitEstDansPremisseVraiChariotSautDeLigne)
{
    SystemeExpert se;
    tp1::TypeFait p_Premisse = "a de la barbe\na de la peau\na des bras\na des jambes";
    tp1::TypeFait p_Fait = "a de la peau\n";
    EXPECT_TRUE(se.faitEstDansPremisse(p_Fait, p_Premisse));
}

TEST(SystemeExpert, methodeFaitEstDansPremisseFaux)
{
    SystemeExpert se;
    tp1::TypeFait p_Premisse = "a de la barbe\na de la peau\na des bras\na des jambes";
    tp1::TypeFait p_Fait = "a de la peau ";
    EXPECT_FALSE(se.faitEstDansPremisse(p_Fait, p_Premisse));
}

TEST(SystemeExpert, methodeConclusionEstPremierElementDansPremisseVrai)
{
    SystemeExpert se;
    tp1::TypeFait p_Premisse = "a de la barbe\na de la peau\na des bras\na des jambes";
    tp1::TypeFait p_Conclusion = "a de la barbe";
    EXPECT_TRUE(se.conclusionEstPremierElementDansPremisse(p_Conclusion, p_Premisse));
}

TEST(SystemeExpert, methodeConclusionEstPremierElementDansPremisseFaux)
{
    SystemeExpert se;
    tp1::TypeFait p_Premisse = "a de la barbe\na de la peau\na des bras\na des jambes";
    tp1::TypeFait p_Conclusion = "a des bras";
    EXPECT_FALSE(se.conclusionEstPremierElementDansPremisse(p_Conclusion, p_Premisse));
}

TEST(SystemeExpert, methodeGetConclusionRegle)
{
    SystemeExpert se;
    tp1::Regle reTestConc;
    reTestConc.GetPremisses().push_back("a des bras");
    reTestConc.GetConclusions().push_back("est un humain");
    se.ajouterRegleSE(reTestConc);
    EXPECT_EQ("est un humain", se.getConclusionRegle(0));
}


