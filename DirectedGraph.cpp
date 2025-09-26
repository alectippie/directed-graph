#include "DirectedGraph.h"
#include <queue>
#include <stack>
#include <unordered_set>
#include <stdexcept>
#include <fstream>

DirectedGraph::DirectedGraph() : edgeCounter(0) {}


//functions for graph construction and editing 

void DirectedGraph::addNode(const std::string& id){
    if(!hasNode(id)){
        nodes[id] = std::make_shared<Node>(id);
    }
}

void DirectedGraph::removeNode(const std::string& id){
    if(!hasNode(id)) return;

    //remove this node from the other nodes neighbors
    for(auto it = nodes.begin(); it != nodes.end(); ++it) {
        it->second->removeNeighbor(id);
    }

    //remove outgoing edges
    edgeCounter -= nodes[id]->getNeighbors().size();

    //remove the node key
    nodes.erase(id);
}

bool DirectedGraph::hasNode(const std::string& id) const{
    return nodes.find(id) != nodes.end();
}

void DirectedGraph::addEdge(const std::string& from, const std::string& to){
    if (!hasNode(from) || !hasNode(to)) {
        throw std::invalid_argument("One or both nodes do not exist.");
    }

    auto fromNode = nodes[from];
    auto toNode = nodes[to];

    if(!fromNode->hasNeighbor(to)) {
        fromNode->addNeighbor(toNode);
        edgeCounter ++;
    }
}

bool DirectedGraph::hasEdge(const std::string& from, const std::string& to) const {
    if (!hasNode(from)) return false;
    return nodes.at(from)->hasNeighbor(to);
}

void DirectedGraph::removeEdge(const std::string& from, const std::string& to){
    if(!hasEdge(from, to)) return;

    auto fromNode = nodes[from];
    if(fromNode->hasNeighbor(to)) {
        fromNode->removeNeighbor(to);
        edgeCounter --;
    }
}   

std::shared_ptr<Node> DirectedGraph::getNode(const std::string& id) const{
    if(!hasNode(id)) return nullptr;
    return nodes.at(id);
}

std::vector<std::string> DirectedGraph::getNodeIds() const {
    std::vector<std::string> ids;
    for (const auto& [id, _] : nodes) {
        ids.push_back(id);
    }
    return ids;
}

size_t DirectedGraph::nodeCount() const {
    return nodes.size();
}

size_t DirectedGraph::edgeCount() const {
    return nodes.size();
}

//used to export the graph to a dot file to generate graph visual
void DirectedGraph::exportToDOT(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing DOT.");
    }

    file << "digraph G {\n";  // ✅ FIXED LINE

    // Write nodes
    for (const auto& [id, node] : nodes) {
        file << "    \"" << id << "\";\n";
    }

    // Write edges
    for (const auto& [id, node] : nodes) {
        for (const auto& neighbor : node->getNeighbors()) {
            file << "    \"" << id << "\" -> \"" << neighbor->getId() << "\";\n";
        }
    }

    file << "}\n";
    file.close();
}

//traversal functions

//BFS search
std::vector<std::string> DirectedGraph::bfs(const std::string startId) const {
    //vector that holds node ID ordered
    std::vector<std::string> result;
    //check if the start node id is in the graph
    if (!hasNode(startId)) return result;

    //set for visited and q for nodes that will be visited 
    std::unordered_set<std::string> visited;
    std::queue<std::shared_ptr<Node>> q;

    //push the pointers to the node objects to the q 
    q.push(nodes.at(startId));
    //add the start node to visited set
    visited.insert(startId);

    //repeat until q is emptied
    while(!q.empty()) {
        //current = q iterator 
        auto current = q.front(); q.pop();
        //push the current node id to result vecotr (added onto the back maintaining order)
        result.push_back(current->getId());

        //neighbor iterates through every neighbor of the current node 
        for(const auto& neighbor : current->getNeighbors()){
            //get the id of current neighbor
            const std::string& neighborId = neighbor->getId();
            //only add the neighbor to q and visited set if it has not already been visited
            if(visited.find(neighborId) == visited.end()){
                visited.insert(neighborId);
                q.push(neighbor);
            }
        }
    }
    return result;
}

//Deapth first search
std::vector<std::string> DirectedGraph::dfs(const std::string startId) const {
    std::vector<std::string> result;

    if (!hasNode(startId)) return result;

    std::unordered_set<std::string> visited;
    std::stack<std::shared_ptr<Node>> s;

    s.push(nodes.at(startId));

    while(!s.empty()) {
        auto current = s.top(); s.pop();
        const std::string& currentId = current->getId();
        
        if(visited.find(currentId) == visited.end()){
                
            result.push_back(currentId);
            visited.insert(currentId);
            
            //reversing neighbbors for consistent order with recursive dfs
            const auto& neighbors = current->getNeighbors();
            for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
                if (visited.find((*it)->getId()) == visited.end()) {
                    s.push(*it);
                }
            }

        }
    }
    return result;
}