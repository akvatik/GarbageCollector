#include "memory/Graph.h"

#include "memory/GarbageCollector.h"

// Создаём граф
int main() {
    OrientedGraph<int> graph;

    graph.addVertex(1, 10);
    graph.addVertex(2, 20);
    graph.addVertex(3, 30);

    GarbageCollector<int> gc(&graph);

    gc.allocate(1);
    gc.allocate(2);

    gc.garbageCollect();

    return 0;
}






