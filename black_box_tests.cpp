//======= Copyright (c) 2025, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     MATĚJ RŮŽIČKA <xruzicm00@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author MATĚJ RŮŽIČKA
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test {
    protected:
        BinaryTree empty_tree;
};

TEST_F(EmptyTree, InsertNode) {
    int key = 77;
    std::pair<bool, Node_t *> pair = empty_tree.InsertNode(key);

    ASSERT_TRUE(pair.first);

    Node_t *root = empty_tree.GetRoot();

    ASSERT_TRUE(root != nullptr);
    ASSERT_EQ(root, pair.second);
    ASSERT_EQ(root->key, key);
}

TEST_F(EmptyTree, DeleteNode) {
    ASSERT_FALSE(empty_tree.DeleteNode(24));
}

TEST_F(EmptyTree, FindNode) {
    ASSERT_EQ(empty_tree.FindNode(2), nullptr);
}


class NonEmptyTree : public ::testing::Test {
    protected:
        BinaryTree non_empty_tree;

    virtual void SetUp() {
        for (int i = 0; i < 10; i++) {
            non_empty_tree.InsertNode(i);
        }
        
    }
};

TEST_F(NonEmptyTree, InsertNode) {
    
}

/*** Konec souboru black_box_tests.cpp ***/
