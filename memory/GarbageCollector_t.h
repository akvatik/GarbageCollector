//
// Created by akvat
//

#ifndef GARBAGECOLLECTOR_GARBAGECOLLECTOR_T_H
#define GARBAGECOLLECTOR_GARBAGECOLLECTOR_T_H
#include "Graph.h"
#include "../hash/HashMap.h"
#include <stack>

template <class K, class V>
class HashMap;

template <class K, class V>
class Node;

static DynamicArray<void*> trackedObjects;

template <class T>
class GarbageCollector {
public:
    static void track(void* ptr) {
        if (ptr != nullptr) {
            trackedObjects.add(ptr);
        }
    }

    static void untrack(void* ptr) {
        for (size_t i = 0; i < trackedObjects.size(); ++i) {
            if (trackedObjects.get(i) == ptr) {
                trackedObjects.removeAt(i);
                return;
            }
        }
    }

    void mark(OrientedGraph<T>& graph) {
        std::stack<void*> toVisit;

        std::cout << "Marking reachable objects..." << std::endl;

        const DynamicArray<size_t>& roots = graph.getRootVertices();
        for (size_t i = 0; i < roots.size(); ++i) {
            size_t rootId = roots.get(i);
            Vertex<T>* vertex = &graph.getVertex(rootId);
            if (vertex && !vertex->marked) {
                toVisit.push(vertex);
                vertex->mark();
                std::cout << "Marked root vertex with ID: " << vertex->id << std::endl;
            }
        }

        while (!toVisit.empty()) {
            void* currentObject = toVisit.top();
            toVisit.pop();

            Vertex<T>* currentVertex = static_cast<Vertex<T>*>(currentObject);
            std::cout << "Visiting vertex ID: " << currentVertex->id << std::endl;

            for (size_t i = 0; i < currentVertex->neighbours.size(); ++i) {
                Vertex<T>* neighbour = currentVertex->neighbours.get(i);
                if (!neighbour->marked) {
                    neighbour->mark();
                    toVisit.push(neighbour);
                    std::cout << "Marked neighbour vertex ID: " << neighbour->id << std::endl;
                }
            }
        }
    }

    void sweep(OrientedGraph<T>& graph) {
        std::cout << "Sweeping unreachable objects..." << std::endl;

        size_t trackedSize = trackedObjects.size();
        DynamicArray<Vertex<T>*> toDelete;

        for (size_t i = 0; i < trackedSize; ++i) {
            void* object = trackedObjects.get(i);
            Vertex<T>* vertex = static_cast<Vertex<T>*>(object);
            if (vertex != nullptr &&
                vertex->graphId == graph.getGraphId() &&
                !vertex->marked) {
                toDelete.add(vertex);
            }
        }

        for (size_t i = 0; i < toDelete.size(); ++i) {
            Vertex<T>* vertex = toDelete.get(i);
            std::cout << "Deleting vertex with ID: " << vertex->id << std::endl;
            graph.deleteVertex(vertex->id);

            size_t indexToRemove = static_cast<size_t>(-1);
            for (size_t j = 0; j < trackedObjects.size(); ++j) {
                if (trackedObjects.get(j) == vertex) {
                    indexToRemove = j;
                    break;
                }
            }
            if (indexToRemove != static_cast<size_t>(-1)) {
                trackedObjects.removeAt(indexToRemove);
            }
            std::cout << "Size of tracked objects after deletion: " << trackedObjects.size() << std::endl;
        }
        DynamicArray<size_t> remainingVertices = graph.getVertexIds();
        for (size_t i = 0; i < remainingVertices.size(); ++i) {
            graph.getVertex(remainingVertices.get(i)).unmark();
        }
    }

    void garbageCollect(OrientedGraph<T>& graph) {
        mark(graph);
        sweep(graph);
    }
};

#endif // GARBAGECOLLECTOR_GARBAGECOLLECTOR_T_H



