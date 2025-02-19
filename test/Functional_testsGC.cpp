//
// Created by akvat
//
#include <iostream>
#include <cassert>
#include "../memory/Graph.h"
#include "../memory/GarbageCollector_t.h"
#include "Functional_testsGC.h"

// Test 1: Basic test with reachable and unreachable vertices.
void testBasic() {
    std::cout << "----- Running testBasic -----" << std::endl;

    OrientedGraph<int> graph(101);

    graph.addVertex(1, 10);
    graph.addVertex(2, 20);
    graph.addVertex(3, 30);
    graph.addVertex(4, 40);
    graph.addVertex(5, 50);

    graph.addRootVertex(1);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(4, 5);

    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    assert(vertexIds.size() == 3);
    bool found1 = false, found2 = false, found3 = false;
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        if (id == 1) found1 = true;
        if (id == 2) found2 = true;
        if (id == 3) found3 = true;
    }
    assert(found1);
    assert(found2);
    assert(found3);

    trackedObjects.clear();

    std::cout << "Test passed!" << std::endl;
}

// Test 2: All vertices are reachable (cycle included).
void testAllReachable() {
    std::cout << "----- Running testAllReachable -----" << std::endl;

    OrientedGraph<int> graph(102);

    graph.addVertex(1, 100);
    graph.addVertex(2, 200);
    graph.addVertex(3, 300);

    graph.addRootVertex(1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    assert(vertexIds.size() == 3);
    bool found1 = false, found2 = false, found3 = false;
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        if (id == 1) found1 = true;
        if (id == 2) found2 = true;
        if (id == 3) found3 = true;
    }
    assert(found1);
    assert(found2);
    assert(found3);

    trackedObjects.clear();
    
    std::cout << "Test passed!" << std::endl;
}

// Test 3: No root vertices set; all vertices should be swept.
void testNoRoot() {
    std::cout << "----- Running testNoRoot -----" << std::endl;

    OrientedGraph<int> graph(103);

    graph.addVertex(1, 11);
    graph.addVertex(2, 22);
    graph.addVertex(3, 33);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    DynamicArray<size_t> vertexIds = graph.getVertexIds();

    assert(graph.getVertexIds().size() == 0);

    trackedObjects.clear();

    std::cout << "Test passed!" << std::endl;
}

// Test 4: Graph with a cycle to ensure cycle remains intact if reachable.
void testCycle() {
    std::cout << "----- Running testCycle -----" << std::endl;

    OrientedGraph<int> graph(104);

    graph.addVertex(1, 1);
    graph.addVertex(2, 2);
    graph.addVertex(3, 3);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    graph.addRootVertex(1);

    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    assert(vertexIds.size() == 3);
    bool found1 = false, found2 = false, found3 = false;
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        if (id == 1) found1 = true;
        if (id == 2) found2 = true;
        if (id == 3) found3 = true;
    }
    assert(found1);
    assert(found2);
    assert(found3);

    trackedObjects.clear();

    std::cout << "Test passed!" << std::endl;
}

// Test 5: Multiple graphs should not interfere with each other.
void testMultipleGraphs() {
    std::cout << "----- Running testMultipleGraphs -----" << std::endl;

    OrientedGraph<int> graph1(201);
    graph1.addVertex(1, 10);
    graph1.addVertex(2, 20);
    graph1.addVertex(3, 30);
    graph1.addRootVertex(1);
    graph1.addEdge(1, 2);
    graph1.addEdge(2, 3);

    OrientedGraph<int> graph2(202);
    graph2.addVertex(1, 100);
    graph2.addVertex(2, 200);
    graph2.addVertex(3, 300);
    graph2.addRootVertex(1);
    graph2.addEdge(1, 2);
    graph2.addEdge(2, 3);
    graph2.addVertex(4, 400);

    GarbageCollector<int> gc;
    gc.garbageCollect(graph2);

    DynamicArray<size_t> vertexIds1 = graph1.getVertexIds();
    assert(vertexIds1.size() == 3);
    bool found1 = false, found2 = false, found3 = false;
    for (size_t i = 0; i < vertexIds1.size(); ++i) {
        size_t id = vertexIds1.get(i);
        if (id == 1) found1 = true;
        if (id == 2) found2 = true;
        if (id == 3) found3 = true;
    }
    assert(found1);
    assert(found2);
    assert(found3);

    DynamicArray<size_t> vertexIds2 = graph2.getVertexIds();
    assert(vertexIds2.size() == 3);
    found1 = found2 = found3 = false;
    for (size_t i = 0; i < vertexIds2.size(); ++i) {
        size_t id = vertexIds2.get(i);
        if (id == 1) found1 = true;
        if (id == 2) found2 = true;
        if (id == 3) found3 = true;
    }
    assert(found1);
    assert(found2);
    assert(found3);

    trackedObjects.clear();

    std::cout << "Test passed!" << std::endl;
}

void testMarkReset() {
    std::cout << "----- Running testMarkReset -----" << std::endl;

    OrientedGraph<int> graph(105);

    graph.addVertex(1, 100);
    graph.addVertex(2, 200);
    graph.addVertex(3, 300);

    graph.addRootVertex(1);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        graph.getVertex(vertexIds.get(i)).unmark();
    }

    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        assert(!graph.getVertex(id).marked);
    }

    trackedObjects.clear();

    std::cout << "Test passed!" << std::endl;
}

void runFunctionalTests() {
    try {
        testBasic();
        testAllReachable();
        testNoRoot();
        testCycle();
        testMultipleGraphs();
        testMarkReset();
        std::cout << "Functional tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test failed: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Test failed due to an unknown error." << std::endl;
    }
}
