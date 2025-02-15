//
// Created by akvat
//

#ifndef GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_GARBAGECOLLECTOR_H

#include "Graph.h"
#include <stack>

//перегрузить операторы new and delete, для взаимодействия с умными указателями

template <class T>
class GarbageCollector {
private:
    OrientedGraph<T>* graph;
    DynamicArray<size_t> rootIds;

public:
    GarbageCollector(OrientedGraph<T>* graph) : graph(graph) {}

    void allocate(size_t rootId) {
        if (!graph->hasVertex(rootId)) {
            throw std::invalid_argument("Vertex with ID " + std::to_string(rootId) + " does not exist!");
        }
        rootIds.add(rootId);
    }

    void mark() {
        std::stack<Vertex<T>*> toVisit;

        for (size_t i = 0; i < rootIds.size(); ++i) {
            size_t rootId = rootIds.get(i);
            if (graph->hasVertex(rootId)) {
                Vertex<T>* root = &graph->getVertex(rootId); // Исправлено
                if (!root->marked) {
                    toVisit.push(root);
                    root->mark();
                }
            }
        }

        while (!toVisit.empty()) {
            Vertex<T>* current = toVisit.top();
            toVisit.pop();

            for (size_t i = 0; i < current->neighbours.size(); ++i) {
                Vertex<T>* neighbour = current->neighbours.get(i);
                if (!neighbour->marked) {
                    neighbour->mark();
                    toVisit.push(neighbour);
                }
            }
        }
    }


    void sweep() {
        DynamicArray<size_t> keys = graph->getVertexIds();
        for (size_t i = 0; i < keys.size(); ++i) {
            size_t vertexId = keys.get(i);
            Vertex<T>& vertex = graph->getVertex(vertexId);
            if (!vertex.marked) {
                graph->deleteVertex(vertexId);
            } else {
                vertex.unmark();
            }
        }
    }

    void garbageCollect() {
        mark();
        sweep();
    }

    const DynamicArray<size_t>& getRoots() const {
        return rootIds;
    }
};


#endif //GARBAGECOLLECTOR_GARBAGECOLLECTOR_H
