//======= Copyright (c) 2025, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     MATĚJ RŮŽIČKA <xruzicm00@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 * @author Matěj Růžička
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"
#include <algorithm>

Graph::Graph(){}

Graph::~Graph(){}

std::vector<Node*> Graph::nodes() {
    std::vector<Node*> nodes;

    for (const auto& pair : map_nodes) {
        printf("NODE: %lu, %p, Size:  %lu \n", pair.first, pair.second, map_nodes.size());
        nodes.push_back(pair.second);
    }

    return nodes;
}

std::vector<Edge> Graph::edges() const{
    std::vector<Edge> edges;

    for (const auto& pair : neighbors) {
        for (size_t y : pair.second) {
            edges.push_back({pair.first, y});
        }
    }

    return edges;
}

Node* Graph::addNode(size_t nodeId) {
    if (neighbors.count(nodeId)) return nullptr;

    Node* node = new Node();
    node->id = nodeId;
    node->color = 0;

    map_nodes[nodeId] = node;
    neighbors[nodeId] = std::vector<size_t>{};

    printf("ADD NODE: %lu, %p \n", node->id, node);
    return node;
}

bool Graph::addEdge(const Edge& edge){
    if (map_nodes.find(edge.a) == map_nodes.end() || 
        map_nodes.find(edge.b) == map_nodes.end()) {
        return false; 
    }

    std::vector<size_t> a_edges = neighbors.at(edge.a);
    std::vector<size_t> b_edges = neighbors.at(edge.b);

    if (edge.a == edge.b ||
        std::count(a_edges.begin(), a_edges.end(), edge.b) ||
        std::count(b_edges.begin(), b_edges.end(), edge.a)) 
        return false;

    a_edges.push_back(edge.b);
    b_edges.push_back(edge.a);

    neighbors[edge.a] = a_edges;
    neighbors[edge.b] = b_edges;

    return true;
}

// TODO: vytvorit neexistujici hrany
void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for (Edge edge : edges) {
        addEdge(edge);
    }
}

Node* Graph::getNode(size_t nodeId){
    std::map<size_t, Node*>::iterator it = map_nodes.find(nodeId);

    if (it == map_nodes.end()) 
        return nullptr;

    return map_nodes.at(nodeId);
}

bool Graph::containsEdge(const Edge& edge) const{
    return false;
}

void Graph::removeNode(size_t nodeId){
}

void Graph::removeEdge(const Edge& edge){
}

size_t Graph::nodeCount() const{
    return 42;
}

size_t Graph::edgeCount() const{
    return 42;
}

size_t Graph::nodeDegree(size_t nodeId) const{
    return 42;
}

size_t Graph::graphDegree() const{
    return 42;
}

void Graph::coloring(){
    for (const auto& pair : map_nodes) {
        pair.second->color = 0;
    }
}

void Graph::clear() {


}

/*** Konec souboru tdd_code.cpp ***/
