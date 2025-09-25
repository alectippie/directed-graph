#include "Node.h"
#include "algorithm"

Node::Node(const std::string& id) : id(id) {}

const std::string& Node::getId() const {
    return id;
}

//adds the pointer to the neighbor vector if it is not already a neighbor
void Node::addNeighbor(std::shared_ptr<Node> neighbor){
    if(!hasNeighbor(neighbor->getId())) {
        neighbors.push_back(neighbor);
    }
}

//remove neighbor of specified id
void Node::removeNeighbor(const std::string& neighborId) {
    neighbors.erase(
        std::remove_if(neighbors.begin(), neighbors.end(),
                       [&](const std::shared_ptr<Node>& n) {
                           return n->getId() == neighborId;
                       }),
        neighbors.end()
    );
}

const std::vector<std::shared_ptr<Node>>& Node::getNeighbors() const {
    return neighbors;
}

//checks if the argument pointer to a node is in the neighbor vector
bool Node::hasNeighbor(const std::string& neighborId) const{
    for (const auto& neighbor : neighbors) {
        if (neighbor->getId() == neighborId) {
            return true;
        }
    }
    return false;
}