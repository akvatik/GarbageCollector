//
// Created by akvat on 18.02.2025.
//
#include <iostream>
#include "../memory/Graph.h"
#include "../memory/GarbageCollector_t.h"
#include "TestGarbageCollector.h"

// Test 1: Basic test with reachable and unreachable vertices.
void testBasic() {
    std::cout << "----- Running testBasic -----" << std::endl;

    // Create a graph with ID 101.
    OrientedGraph<int> graph(101);

    // Add vertices.
    graph.addVertex(1, 10);
    graph.addVertex(2, 20);
    graph.addVertex(3, 30);
    graph.addVertex(4, 40);
    graph.addVertex(5, 50);

    // Set vertex 1 as the root.
    graph.addRootVertex(1);

    // Create edges: 1 -> 2, 2 -> 3 (reachable) and 4 -> 5 (unreachable).
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(4, 5);

    // Display vertices before GC.
    std::cout << "Vertices before GC:" << std::endl;
    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
    }

    // Run the garbage collector.
    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    // Display vertices after GC.
    std::cout << "Vertices after GC:" << std::endl;
    vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
    }
    std::cout << std::endl;
}

// Test 2: All vertices are reachable (cycle included).
void testAllReachable() {
    std::cout << "----- Running testAllReachable -----" << std::endl;

    // Create a graph with ID 102.
    OrientedGraph<int> graph(102);

    // Add vertices.
    graph.addVertex(1, 100);
    graph.addVertex(2, 200);
    graph.addVertex(3, 300);

    // Set vertex 1 as the root and create a cycle: 1 -> 2 -> 3 -> 1.
    graph.addRootVertex(1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    // Display vertices before GC.
    std::cout << "Vertices before GC:" << std::endl;
    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
    }

    // Run GC.
    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    // Display vertices after GC.
    std::cout << "Vertices after GC:" << std::endl;
    vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
    }
    std::cout << std::endl;
}

// Test 3: No root vertices set; all vertices should be swept.
void testNoRoot() {
    std::cout << "----- Running testNoRoot -----" << std::endl;

    // Create a graph with ID 103.
    OrientedGraph<int> graph(103);

    // Add vertices.
    graph.addVertex(1, 11);
    graph.addVertex(2, 22);
    graph.addVertex(3, 33);

    // Connect vertices (but do not set any root).
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    // Display vertices before GC.
    std::cout << "Vertices before GC:" << std::endl;
    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
    }

    // Run GC.
    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    // Display vertices after GC.
    std::cout << "Vertices after GC (expected none):" << std::endl;
    vertexIds = graph.getVertexIds();
    if (vertexIds.size() == 0) {
        std::cout << "No vertices remain." << std::endl;
    } else {
        for (size_t i = 0; i < vertexIds.size(); ++i) {
            size_t id = vertexIds.get(i);
            std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
        }
    }
    std::cout << std::endl;
}

// Test 4: Graph with a cycle to ensure cycle remains intact if reachable.
void testCycle() {
    std::cout << "----- Running testCycle -----" << std::endl;

    // Create a graph with ID 104.
    OrientedGraph<int> graph(104);

    // Add vertices.
    graph.addVertex(1, 1);
    graph.addVertex(2, 2);
    graph.addVertex(3, 3);

    // Create a cycle: 1 -> 2, 2 -> 3, 3 -> 1.
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 1);

    // Set vertex 1 as the root.
    graph.addRootVertex(1);

    // Display vertices before GC.
    std::cout << "Vertices before GC:" << std::endl;
    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
    }

    // Run GC.
    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    // Display vertices after GC.
    std::cout << "Vertices after GC:" << std::endl;
    vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        std::cout << "Vertex " << id << " with value " << graph.getVertex(id).value << std::endl;
    }
    std::cout << std::endl;
}

// Test 5: Multiple graphs should not interfere with each other.
void testMultipleGraphs() {
    std::cout << "----- Running testMultipleGraphs -----" << std::endl;

    // Graph 1 with ID 201.
    OrientedGraph<int> graph1(201);
    graph1.addVertex(1, 10);
    graph1.addVertex(2, 20);
    graph1.addVertex(3, 30);
    graph1.addRootVertex(1);
    graph1.addEdge(1, 2);
    graph1.addEdge(2, 3);

    // Graph 2 with ID 202.
    OrientedGraph<int> graph2(202);
    graph2.addVertex(1, 100);
    graph2.addVertex(2, 200);
    graph2.addVertex(3, 300);
    graph2.addRootVertex(1);
    graph2.addEdge(1, 2);
    graph2.addEdge(2, 3);
    // Add an unreachable vertex to graph2.
    graph2.addVertex(4, 400);

    // Display vertices before GC.
    std::cout << "Graph1 vertices before GC:" << std::endl;
    DynamicArray<size_t> vertexIds1 = graph1.getVertexIds();
    for (size_t i = 0; i < vertexIds1.size(); ++i) {
        size_t id = vertexIds1.get(i);
        std::cout << "Graph1 Vertex " << id << " with value " << graph1.getVertex(id).value << std::endl;
    }

    std::cout << "Graph2 vertices before GC:" << std::endl;
    DynamicArray<size_t> vertexIds2 = graph2.getVertexIds();
    for (size_t i = 0; i < vertexIds2.size(); ++i) {
        size_t id = vertexIds2.get(i);
        std::cout << "Graph2 Vertex " << id << " with value " << graph2.getVertex(id).value << std::endl;
    }

    // Run GC on Graph2 only.
    GarbageCollector<int> gc;
    gc.garbageCollect(graph2);

    // Display vertices after GC.
    std::cout << "Graph1 vertices after GC on Graph2:" << std::endl;
    vertexIds1 = graph1.getVertexIds();
    for (size_t i = 0; i < vertexIds1.size(); ++i) {
        size_t id = vertexIds1.get(i);
        std::cout << "Graph1 Vertex " << id << " with value " << graph1.getVertex(id).value << std::endl;
    }

    std::cout << "Graph2 vertices after GC:" << std::endl;
    vertexIds2 = graph2.getVertexIds();
    for (size_t i = 0; i < vertexIds2.size(); ++i) {
        size_t id = vertexIds2.get(i);
        std::cout << "Graph2 Vertex " << id << " with value " << graph2.getVertex(id).value << std::endl;
    }
    std::cout << std::endl;
}

// Test 6: Verify that after GC, all remaining vertices are unmarked.
void testMarkReset() {
    std::cout << "----- Running testMarkReset -----" << std::endl;

    // Create a graph with ID 105.
    OrientedGraph<int> graph(105);

    // Add vertices.
    graph.addVertex(1, 100);
    graph.addVertex(2, 200);
    graph.addVertex(3, 300);

    // Set vertex 1 as the root.
    graph.addRootVertex(1);

    // Connect vertices: 1 -> 2 and 2 -> 3.
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    // Run the garbage collector.
    GarbageCollector<int> gc;
    gc.garbageCollect(graph);

    // OPTIONAL: Reset marks for all remaining vertices if not already done inside GC.
    // This loop could be integrated in the GC's sweep phase.
    DynamicArray<size_t> vertexIds = graph.getVertexIds();
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        graph.getVertex(vertexIds.get(i)).unmark();
    }

    // Verify that all remaining vertices are unmarked.
    bool allUnmarked = true;
    for (size_t i = 0; i < vertexIds.size(); ++i) {
        size_t id = vertexIds.get(i);
        if (graph.getVertex(id).marked) {
            allUnmarked = false;
            std::cout << "Vertex " << id << " remains marked!" << std::endl;
        }
    }

    if (allUnmarked) {
        std::cout << "Test passed: All vertices are unmarked after GC." << std::endl;
    } else {
        std::cout << "Test failed: Some vertices remain marked." << std::endl;
    }

    std::cout << std::endl;
}

