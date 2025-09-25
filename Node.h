#pragma once

#include <vector>
#include <string>
#include <memory>

class Node {
public:
    explicit Node(const std::string& id);

    const std::string& getId() const;

    void addNeighbor(std::shared_ptr<Node> neighbor);
    void removeNeighbor(const std::string& neighborId);
    const std::vector<std::shared_ptr<Node>>& getNeighbors() const;

    bool hasNeighbor(const std::string& neighborId) const;

private:
    std::string id;
    std::vector<std::shared_ptr<Node>> neighbors;
};