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
    DynamicArray<Vertex<T>*> neighbours;
    bool marked;
    //вынести вне определения вершины
    Vertex() : id(0), value(T()), neighbours(), marked(false) {}

    Vertex(size_t id, const T& value)
            : id(id), value(value), neighbours(), marked(false) {}

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

public:
    OrientedGraph() = default;

    bool hasVertex(size_t id) const {
        return data.containsKey(id);
    }

    Vertex<T>& getVertex(size_t id) {
        return data.get(id);
    }

    const Vertex<T>& getVertex(size_t id) const {
        return data.get(id);
    }

    // Метод для получения списка ID всех вершин
    DynamicArray<size_t> getVertexIds() const {
        return data.getKeys();
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
        DynamicArray<size_t> keys = data.getKeys();
        for (size_t i = 0; i < keys.size(); ++i) {
            data.get(keys[i]).removeNeighbour(&data.get(id));
        }
        data.remove(id);
    }

    void addVertex(size_t id, const T& value) {
        if (hasVertex(id)) {
            throw std::invalid_argument("Vertex with ID " + std::to_string(id) + " already exists!");
        }
        Vertex<T> new_vertex(id, value);
        data.put(id, new_vertex);
    }



    void setVertexData(size_t id, T newData) {
        if (hasVertex(id)) {
            data.get(id).value = newData;
        } else {
            throw std::runtime_error("Vertex not found");
        }
    }


    DynamicArray<Vertex<T>> getAllVertices() const{
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


#endif //GARBAGECOLLECTOR_GRAPH_H
