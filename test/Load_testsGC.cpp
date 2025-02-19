#include <iostream>
#include <chrono>
#include <cassert>
#include "../memory/Graph.h"
#include "../memory/GarbageCollector_t.h"
#include "Load_testsGC.h"

void stressTestAddRemoveVertices() {
    std::cout << "----- Running stressTestAddRemoveVertices -----" << std::endl;

    OrientedGraph<int> graph(1001); 

    const int numVertices = 10000;              
    const int numEdges = 20000;

    for (int i = 1; i <= numVertices; ++i) {
        graph.addVertex(i, i);
    }

    for (int i = 1; i < numVertices; ++i) {
        graph.addEdge(i, i + 1);
    }

    GarbageCollector<int> gc;

    auto start = std::chrono::high_resolution_clock::now();
    gc.garbageCollect(graph);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Garbage collection completed in " << duration.count() << " seconds." << std::endl;

    std::cout << "Stress test passed!" << std::endl;
}

void stressTestCycleGraph() {
    std::cout << "----- Running stressTestCycleGraph -----" << std::endl;

    OrientedGraph<int> graph(2002);

    const int numVertices = 10000;

    for (int i = 1; i <= numVertices; ++i) {
        graph.addVertex(i, i);
    }

    for (int i = 1; i < numVertices; ++i) {
        graph.addEdge(i, i + 1);
    }
    graph.addEdge(numVertices, 1);

    graph.addRootVertex(1);

    GarbageCollector<int> gc;

    auto start = std::chrono::high_resolution_clock::now();
    gc.garbageCollect(graph);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Garbage collection completed in " << duration.count() << " seconds." << std::endl;

    std::cout << "Stress test passed!" << std::endl;
}


void runLoadTests() {
    try {
        stressTestAddRemoveVertices();
        stressTestCycleGraph();
        std::cout << "Load tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test failed: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Test failed due to an unknown error." << std::endl;
    }
}