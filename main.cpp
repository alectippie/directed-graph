#include <iostream>
#include "DirectedGraph.h"

int main() {
    DirectedGraph graph;

    // Add nodes
    for (char c = 'A'; c <= 'J'; ++c) {
        graph.addNode(std::string(1, c));
    }

    // Add edges (some arbitrary connections)
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("B", "E");
    graph.addEdge("C", "F");
    graph.addEdge("E", "G");
    graph.addEdge("F", "H");
    graph.addEdge("G", "I");
    graph.addEdge("H", "J");
    graph.addEdge("I", "J");
    graph.addEdge("J", "A"); 

    std::cout << "Nodes: " << graph.nodeCount() << std::endl;
    std::cout << "Edges: " << graph.edgeCount() << std::endl;

    // Run BFS starting from A
    std::cout << "\nBFS starting from node A:\n";
    std::vector<std::string> bfsResult = graph.bfs("A");

    for (const auto& nodeId : bfsResult) {
        std::cout << nodeId << " ";
    }
    std::cout << std::endl;

    // Export graph to DOT file
    try {
        graph.exportToDOT("graph.dot");
        std::cout << "\nGraph exported to 'graph.dot'." << std::endl;
        std::cout << "Use: dot -Tpng graph.dot -o graph.png to generate image." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to export graph: " << e.what() << std::endl;
    }

    return 0;
}
