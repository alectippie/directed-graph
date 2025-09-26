#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "Node.h"  // Includes definition for Node

class DirectedGraph {

    private:

    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
    size_t edgeCounter;

    public:

    DirectedGraph();

    //node operations
    void addNode(const std::string& id);
    void removeNode(const std::string& id);
    bool hasNode(const std::string& id) const;

    //Edge operations
    void addEdge(const std::string& from, const std::string& to);
    void removeEdge(const std::string& from, const std::string& to);
    bool hasEdge(const std::string& from, const std::string& to) const;

    //Accessors
    std::shared_ptr<Node> getNode(const std::string& id) const;
    std::vector<std::string> getNodeIds() const;
    size_t nodeCount() const;
    size_t edgeCount() const;

    //dotfile export
    void exportToDOT(const std::string& filename) const;

    //traversal functions

    std::vector<std::string> bfs(const std::string startId) const;

    std::vector<std::string> dfs(const std::string startId) const;
    
};