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
        BinaryTree emptyTree;
};

TEST_F(EmptyTree, InsertNode) {
    int key = 77;
    std::pair<bool, Node_t *> pair = emptyTree.InsertNode(key);

    ASSERT_TRUE(pair.first);

    Node_t* root = emptyTree.GetRoot();

    EXPECT_NE(root, nullptr);
    EXPECT_EQ(root, pair.second);
    EXPECT_EQ(root->key, key);
    EXPECT_EQ(root->color, 1);
}

TEST_F(EmptyTree, DeleteNode) {
    ASSERT_FALSE(emptyTree.DeleteNode(24));
}

TEST_F(EmptyTree, FindNode) {
    ASSERT_EQ(emptyTree.FindNode(2), nullptr);
}


class NonEmptyTree : public ::testing::Test {
    protected:
        BinaryTree nonEmptyTree;

    virtual void SetUp() {
        nonEmptyTree.InsertNode(2);
        nonEmptyTree.InsertNode(4);
    }
};

TEST_F(NonEmptyTree, InsertNode_Unique) {
    int key = 1;
    std::pair<bool, Node_t *> pair = nonEmptyTree.InsertNode(key);
    Node_t* root = nonEmptyTree.GetRoot();

    // doslo k pridani node
    ASSERT_TRUE(pair.first);
    ASSERT_EQ(pair.second->key, key);
    ASSERT_EQ(pair.second->color, 0);

    // struktura zustala stejna
    EXPECT_EQ(root->key, 2);
    EXPECT_EQ(root->pRight->key, 4);
    EXPECT_EQ(root->pLeft->key, key);
    EXPECT_EQ(pair.second, root->pLeft);
}

TEST_F(NonEmptyTree, InsertNode_UniqueRestructure) {
    int key = 8;
    std::pair<bool, Node_t *> pair = nonEmptyTree.InsertNode(key);
    Node_t* root = nonEmptyTree.GetRoot();

    // doslo k pridani node
    ASSERT_TRUE(pair.first);
    ASSERT_EQ(pair.second->key, key);
    ASSERT_EQ(pair.second->color, 0);

    // struktura se zmenila podle ocekavani
    EXPECT_EQ(root->key, 4);
    EXPECT_EQ(root->pLeft->key, 2);
    EXPECT_EQ(root->pRight->key, key);
    EXPECT_EQ(pair.second, root->pRight);
}

TEST_F(NonEmptyTree, InsertNode_Duplicate) {
    int key = 2;
    std::pair<bool, Node_t *> pair = nonEmptyTree.InsertNode(key);
    Node_t* root = nonEmptyTree.GetRoot();

    // nedoslo k pridani node
    ASSERT_FALSE(pair.first);

    // struktura zustala stejna
    EXPECT_EQ(root->key, 2);
    EXPECT_EQ(root->pRight->key, 4);
    EXPECT_EQ(root->pLeft->key, 0);
}

TEST_F(NonEmptyTree, DeleteNode_Restructure) {
    int key = 2;
    Node_t* root = nonEmptyTree.GetRoot();

    bool result = nonEmptyTree.DeleteNode(key);
    ASSERT_TRUE(result);
    EXPECT_EQ(nonEmptyTree.FindNode(key), nullptr);

    // struktura stromu se zmenila podle ocekevani
    root = nonEmptyTree.GetRoot();
    EXPECT_EQ(root->key, 4);
}

TEST_F(NonEmptyTree, DeleteNode_UnusedValue) {
    int key = 1;
    Node_t* root = nonEmptyTree.GetRoot();

    bool result = nonEmptyTree.DeleteNode(key);
    ASSERT_FALSE(result);
}

TEST_F(NonEmptyTree, DeleteNode_LastNode) {
    int key = 4;
    Node_t* root = nonEmptyTree.GetRoot();

    bool result = nonEmptyTree.DeleteNode(key);
    ASSERT_TRUE(result);
    EXPECT_EQ(nonEmptyTree.FindNode(key), nullptr);
    root = nonEmptyTree.GetRoot();
    EXPECT_EQ(root->pRight->key, 0);
}

TEST_F(NonEmptyTree, FindNode_UsedValue) {
    int key = 2;
    Node_t* node = nonEmptyTree.FindNode(key);
    Node_t* root = nonEmptyTree.GetRoot();

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node, root);
}

TEST_F(NonEmptyTree, FindNode_UnusedValue) {
    int key = 1;
    Node_t* node = nonEmptyTree.FindNode(key);

    ASSERT_EQ(node, nullptr);
}

class TreeAxioms : public ::testing::Test {
    protected:
        BinaryTree treeAxioms;

    virtual void SetUp() {
        for (int i = 1; i < 10; i++) {
            treeAxioms.InsertNode(i);
        }
    }
};

TEST_F(TreeAxioms, Axiom1) {
    std::vector<Node_t *> leafs;
    treeAxioms.GetLeafNodes(leafs);

    for (Node_t* leaf : leafs) {
        EXPECT_EQ(leaf->color, 1);
    }
}

TEST_F(TreeAxioms, Axiom2) {
    std::vector<Node_t *> nodes;
    treeAxioms.GetNonLeafNodes(nodes);

    for (Node_t* node : nodes) {
        // jestli je node cervena
        if (!node->color) {
            EXPECT_EQ(node->pLeft->color, 1);
            EXPECT_EQ(node->pRight->color, 1);
        }
    }
}

TEST_F(TreeAxioms, Axiom3) {
    std::vector<Node_t *> leafs;
    treeAxioms.GetLeafNodes(leafs);
    Node_t* root = treeAxioms.GetRoot();

    int first_height = 0;
    Node_t* currentNode = leafs[0];
    while (currentNode != root)
    {
        currentNode = currentNode->pParent;
        // jestli je node cerna
        if (currentNode->color)
            first_height++;
    }


    for (Node_t* leaf : leafs) {
        int height = 0;
        currentNode = leaf;
        while (currentNode != root)
        {
            currentNode = currentNode->pParent;
            if (currentNode->color)
                height++;
        }
        EXPECT_EQ(height, first_height);
    }
}

/*** Konec souboru black_box_tests.cpp ***/
