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