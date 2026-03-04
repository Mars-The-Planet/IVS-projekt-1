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

Graph::~Graph(){
    clear();
}

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
            Edge edge = {pair.first, y};
            Edge edge_twist = {y, pair.first};
            
            if (std::find(edges.begin(), edges.end(), edge_twist) == edges.end()) {
                edges.push_back(edge);
            }
        }
    }

    return edges;
}

Node* Graph::addNode(size_t nodeId) {
    if (map_nodes.count(nodeId)) return nullptr;

    Node* node = new Node();
    node->id = nodeId;
    node->color = 0;
    node->colored = false;

    map_nodes[nodeId] = node;
    neighbors[nodeId] = std::vector<size_t>{};

    return node;
}

bool Graph::addEdge(const Edge& edge){
    addNode(edge.a);
    addNode(edge.b);

    std::vector<size_t> a_edges = neighbors.at(edge.a);
    std::vector<size_t> b_edges = neighbors.at(edge.b);

    if (edge.a == edge.b ||
        std::count(a_edges.begin(), a_edges.end(), edge.b) ||
        std::count(b_edges.begin(), b_edges.end(), edge.a)) {
            return false;
    }
        
    a_edges.push_back(edge.b);
    b_edges.push_back(edge.a);

    neighbors[edge.a] = a_edges;
    neighbors[edge.b] = b_edges;

    return true;
}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for (Edge edge : edges) {
        addEdge(edge);
    }
}

Node* Graph::getNode(size_t nodeId){
    if (!map_nodes.count(nodeId)) 
        return nullptr;

    return map_nodes.at(nodeId);
}

bool Graph::containsEdge(const Edge& edge) const{
    if (!map_nodes.count(edge.a) || !map_nodes.count(edge.b))
        return false;
    
    std::vector<size_t> a_neighbors = neighbors.at(edge.a);
    if (std::count(a_neighbors.begin(), a_neighbors.end(), edge.b)) 
        return true;

    return false;
}

void Graph::removeNode(size_t nodeId){
    if (!map_nodes.count(nodeId))
        throw std::out_of_range("Node does not exist\n");

    for (auto& pair : neighbors) {
        auto& nodes = pair.second; 
        auto it = std::find(nodes.begin(), nodes.end(), nodeId);
        
        if (it != nodes.end()) {
            nodes.erase(it); 
        }
    }

    delete map_nodes.at(nodeId);

    map_nodes.erase(nodeId);
    neighbors.erase(nodeId);
}

void Graph::removeEdge(const Edge& edge){
    if (!map_nodes.count(edge.a) || !map_nodes.count(edge.b))
        throw std::out_of_range("Edge does not exist\n");
    
    std::vector<size_t> a_neighbors = neighbors.at(edge.a);
    std::vector<size_t> b_neighbors = neighbors.at(edge.b);

    auto ia = std::find(a_neighbors.begin(), a_neighbors.end(), edge.b);
    auto ib = std::find(b_neighbors.begin(), b_neighbors.end(), edge.a);

    if (ia == a_neighbors.end() || ib == b_neighbors.end())
        throw std::out_of_range("Edge does not exist\n");

    a_neighbors.erase(ia);
    b_neighbors.erase(ib);

    neighbors.at(edge.a) = a_neighbors;
    neighbors.at(edge.b) = b_neighbors;
}

size_t Graph::nodeCount() const{
    return map_nodes.size();
}

size_t Graph::edgeCount() const{
    return edges().size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    if (neighbors.find(nodeId) == neighbors.end())
        throw std::out_of_range("Node does not exist\n");

    std::vector<size_t> edges = neighbors.at(nodeId);
    return edges.size();
}

size_t Graph::graphDegree() const{
    size_t max_degree = 0;
    for (const auto& pair : neighbors) {
        if (pair.second.size() > max_degree)
            max_degree = pair.second.size();
    }

    return max_degree;
}

void Graph::coloring(){
    for (const auto& pair : map_nodes) {
        pair.second->color = 0;
    }

    
}

void Graph::clear() {
    neighbors.clear();

    for (const auto& pair : map_nodes) {
        delete pair.second;
    }
    
    map_nodes.clear();
}

/*** Konec souboru tdd_code.cpp ***/
