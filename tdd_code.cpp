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
        nodes.push_back(pair.second);
    }

    return nodes;
}

std::vector<Edge> Graph::edges() const{
    std::vector<Edge> edges;

    for (const auto& pair : neighbors) {
        for (size_t y : pair.second) {
            printf("node: %lu, %lu \n", pair.first, y);
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

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for (Edge edge : edges) {
        addNode(edge.a);
        addNode(edge.b);
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
    if (neighbors.find(edge.a) == neighbors.end())
        return false;
    
    std::vector<size_t> a_neighbors = neighbors.at(edge.a);
    if (std::count(a_neighbors.begin(), a_neighbors.end(), edge.b)) 
        return true;

    return false;
}

void Graph::removeNode(size_t nodeId){
    if (map_nodes.find(nodeId) == map_nodes.end())
        return;

    free(map_nodes.at(nodeId));

    map_nodes.erase(nodeId);
    neighbors.erase(nodeId);
}

void Graph::removeEdge(const Edge& edge){
    if (map_nodes.find(edge.a) == map_nodes.end())
        return;
    
    std::vector<size_t> a_neighbors = neighbors.at(edge.a);
    std::vector<size_t> b_neighbors = neighbors.at(edge.b);

    auto ia = std::find(a_neighbors.begin(), a_neighbors.end(), edge.b);
    a_neighbors.erase(ia);

    auto ib = std::find(a_neighbors.begin(), a_neighbors.end(), edge.b);
    a_neighbors.erase(ib);

    neighbors.at(edge.a) = a_neighbors;
    neighbors.at(edge.b) = b_neighbors;
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
