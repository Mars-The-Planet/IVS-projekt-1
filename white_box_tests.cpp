//======= Copyright (c) 2026, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     MATĚJ RŮŽIČKA <xruzicm00@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author MATĚJ RŮŽIČKA
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"
#include <iostream>
//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

class EmptyAutomaton : public ::testing::Test {
    protected:
        SuffixAutomaton emptyAutomaton;
};

class NonEmptyAutomaton : public ::testing::Test {
    protected:
        SuffixAutomaton nonEmptyAutomaton;

    virtual void SetUp() {
        nonEmptyAutomaton.add_sequence("abcdabc");
    }
};

TEST_F(EmptyAutomaton, step) {
    size_t next;
    EXPECT_THROW(emptyAutomaton.step(1, 'a', next), std::out_of_range);
}

TEST_F(NonEmptyAutomaton, step) {
    size_t next;
    EXPECT_TRUE(nonEmptyAutomaton.step(0, 'a', next));
    EXPECT_NE(next, 0);

    EXPECT_FALSE(nonEmptyAutomaton.step(0, 'e', next));

    EXPECT_THROW(nonEmptyAutomaton.step(24, 'a', next), std::out_of_range);
}

TEST_F(EmptyAutomaton, next) {
    size_t next;
    EXPECT_THROW(emptyAutomaton.next(1), std::out_of_range);
}

TEST_F(NonEmptyAutomaton, next) {
    size_t next;
    EXPECT_THROW(nonEmptyAutomaton.next(42), std::out_of_range);
}

TEST_F(EmptyAutomaton, contains) {
    size_t next;
    EXPECT_THROW(emptyAutomaton.next(1), std::out_of_range);
}

TEST_F(NonEmptyAutomaton, contains) {
    size_t next;
    EXPECT_THROW(nonEmptyAutomaton.next(42), std::out_of_range);
    std::unordered_map<char, size_t> map = nonEmptyAutomaton.next(0);
    EXPECT_TRUE(map.count('a'));
    EXPECT_FALSE(map.count('e'));
}

TEST_F(EmptyAutomaton, get_state) {
    EXPECT_THROW(emptyAutomaton.get_state(1), std::out_of_range);
}

TEST_F(NonEmptyAutomaton, get_state) {
    State state = nonEmptyAutomaton.get_state(0);
    EXPECT_EQ(state.len, 0);
    state = nonEmptyAutomaton.get_state(1);
    EXPECT_EQ(state.len, 1);

    EXPECT_THROW(nonEmptyAutomaton.get_state(77), std::out_of_range);
}

TEST_F(EmptyAutomaton, topological_sort) {
    std::vector<size_t> sorted = emptyAutomaton.topological_sort();
    EXPECT_EQ(sorted.size(), 0);
}

TEST_F(NonEmptyAutomaton, topological_sort) {
    std::vector<size_t> sorted = nonEmptyAutomaton.topological_sort();

    // tady to vypada jakoby nastala chyba v implementaci 
    // prece jenom by nemeli mizet hodnoty z pole pri jejich trizeni
    EXPECT_EQ(sorted.size(), nonEmptyAutomaton.size());

    // kontrola serazeni 
    EXPECT_EQ(nonEmptyAutomaton.get_state(sorted[0]).len, 0);
    for (size_t i = 1; i < sorted.size(); ++i) {
        EXPECT_GE(nonEmptyAutomaton.get_state(sorted[i]).len, nonEmptyAutomaton.get_state(sorted[i-1]).len);
    }
}

TEST_F(EmptyAutomaton, longest_direct_continuation) {
    EXPECT_THROW(emptyAutomaton.longest_direct_continuation(1), std::out_of_range);
}

TEST_F(NonEmptyAutomaton, longest_direct_continuation) {
    // tady zase asi mela vypada implemantace jinak
    // protoze nejdelsi prime pokracovani muze vzniknout pouze ze stavu ktere maji pouze jeden prechod
    EXPECT_EQ(nonEmptyAutomaton.longest_direct_continuation(0), "");
    EXPECT_EQ(nonEmptyAutomaton.longest_direct_continuation(1), "bcdabc");
}

/*** Konec souboru white_box_tests.cpp ***/
