//
// Created by akvat
//

#ifndef GARBAGECOLLECTOR_GRAPH_H
#define GARBAGECOLLECTOR_GRAPH_H
#include "../hash/HashMap.h"
#include "../hash/Pair.h"
#include "../collections/DynamicArray.h"
#include <stdexcept>
#include <iostream>

template <class T>
class Vertex {
public:
    size_t id;
    T value;
    size_t graphId;
    DynamicArray<Vertex<T>*> neighbours;
    bool marked;

    Vertex()
            : id(0), value(T()), graphId(0), neighbours(), marked(false) {}

    Vertex(size_t id, const T& value)
            : id(id), value(value), graphId(0), neighbours(), marked(false) {}

    void addNeighbour(Vertex<T>* neighbour) {
        neighbours.add(neighbour);
    }

    void removeNeighbour(Vertex<T>* neighbour) {
        for (size_t i = 0; i < neighbours.size(); ++i) {
            if (neighbours.get(i) == neighbour) {
                neighbours.removeAt(i);
                return;
            }
        }
    }

    void mark() {
        marked = true;
    }

    void unmark() {
        marked = false;
    }
};

template <class T>
class OrientedGraph {
private:
    HashMap<size_t, Vertex<T>> data;
    size_t graphId;
    DynamicArray<size_t> rootVertexIds;

public:
    OrientedGraph(size_t id = 0) : data(), graphId(id), rootVertexIds() {}

    size_t getGraphId() const {
        return graphId;
    }

    bool hasVertex(size_t id) const {
        return data.containsKey(id);
    }

    Vertex<T>& getVertex(size_t id) {
        return data.get(id);
    }

    const Vertex<T>& getVertex(size_t id) const {
        return data.get(id);
    }

    DynamicArray<size_t> getVertexIds() const {
        return data.getKeys();
    }

    void addRootVertex(size_t id) {
        if (!hasVertex(id)) {
            throw std::runtime_error("Vertex with ID " + std::to_string(id) + " not found!");
        }
        rootVertexIds.add(id);
    }

    const DynamicArray<size_t>& getRootVertices() const {
        return rootVertexIds;
    }

    void addEdge(size_t from, size_t to) {
        Vertex<T>& fromVertex = data.get(from);
        Vertex<T>& toVertex = data.get(to);
        fromVertex.addNeighbour(&toVertex);
    }

    void deleteEdge(size_t from, size_t to) {
        Vertex<T>& fromVertex = data.get(from);
        Vertex<T>& toVertex = data.get(to);
        fromVertex.removeNeighbour(&toVertex);
    }

    void deleteVertex(size_t id) {
        if (!hasVertex(id)) {
            std::cout << "Vertex with ID " << id << " not found!" << std::endl;
            return;
        }
        DynamicArray<size_t> keys = data.getKeys();
        for (size_t i = 0; i < keys.size(); ++i) {
            Vertex<T>& vertex = data.get(keys.get(i));
            vertex.removeNeighbour(&data.get(id));
        }
        Vertex<T>* vertexToDelete = &data.get(id);

        GarbageCollector<T>::untrack(vertexToDelete);

        data.remove(id);
        std::cout << "Vertex with ID " << id << " deleted" << std::endl;
    }

    void addVertex(size_t id, const T& value) {
        if (hasVertex(id)) {
            throw std::invalid_argument("Vertex with ID " + std::to_string(id) + " already exists!");
        }
        Vertex<T> new_vertex(id, value);
        new_vertex.graphId = graphId;
        data.put(id, new_vertex);

        Vertex<T>* trackVertex = &data.get(id);
        GarbageCollector<T>::track(trackVertex);
    }

    void setVertexData(size_t id, T newData) {
        if (hasVertex(id)) {
            data.get(id).value = newData;
        } else {
            throw std::runtime_error("Vertex not found");
        }
    }

    DynamicArray<Vertex<T>> getAllVertices() const {
        DynamicArray<Vertex<T>> result;
        DynamicArray<size_t> keys = data.getKeys();
        for (size_t i = 0; i < keys.size(); ++i) {
            result.add(data.get(keys[i]));
        }
        return result;
    }

    DynamicArray<Vertex<T>*> getNeighbours(size_t from) {
        if (!hasVertex(from)) {
            throw std::logic_error("Vertex not found!");
        }
        return data.get(from).neighbours;
    }
};

#endif // GARBAGECOLLECTOR_GRAPH_H

