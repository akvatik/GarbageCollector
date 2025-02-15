//
// Created by akvat
//

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <iostream>
#include <algorithm>
#include <functional>
#include <utility>
#include "../pointer/UnqPtr.h"

template<class T>
class DynamicArray {
private:
    size_t _capacity;
    size_t _size;
    UnqPtr<T[]> _items;

    void ensureCapacity(size_t minCapacity) {
        if (_capacity < minCapacity) {
            size_t newCapacity = std::max(minCapacity, _capacity * 2);
            resize(newCapacity); // Удвоение емкости для эффективного роста
        }
    }

public:
    DynamicArray() : _capacity(1), _size(0), _items(UnqPtr<T[]>(new T[1])) {}

    DynamicArray(size_t count, const T *items)
            : _capacity(count), _size(count), _items(UnqPtr<T[]>(new T[count])) {
        std::copy(items, items + count, _items.getValue());
    }

    explicit DynamicArray(size_t size)
            : _capacity(size), _size(size), _items(UnqPtr<T[]>(new T[size])) {}


    DynamicArray(const DynamicArray<T> &other)
            : _capacity(other._capacity), _size(other._size), _items(UnqPtr<T[]>(new T[other._capacity])) {
        for (size_t i = 0; i < _size; ++i) {
            _items.getValue()[i] = std::move(other._items.getValue()[i]);
        }
    }


    DynamicArray(DynamicArray<T> &&other) noexcept
            : _capacity(other._capacity), _size(other._size), _items(std::move(other._items)) {
        other._capacity = 0;
        other._size = 0;
    }

    DynamicArray(std::initializer_list<T> initList)
            : _capacity(initList.size()), _size(initList.size()), _items(UnqPtr<T[]>(new T[initList.size()])) {
        std::copy(initList.begin(), initList.end(), _items.getValue());
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &other) {
        if (this != &other) {
            _capacity = other._capacity;
            _size = other._size;
            _items = UnqPtr<T[]>(new T[other._capacity]);
            std::copy(other._items.getValue(), other._items.getValue() + other._size, _items.getValue());
        }
        return *this;
    }

    DynamicArray<T> &operator=(DynamicArray<T> &&other) noexcept {
        if (this != &other) {
            _capacity = other._capacity;
            _size = other._size;
            _items = std::move(other._items);
            other._capacity = 0;
            other._size = 0;
        }
        return *this;
    }

    size_t size() const {
        return _size;
    }

    void resize(size_t newSize) {
        UnqPtr < T[] > newItems(new T[newSize]);
        if (_size > newSize) {
            _size = newSize;
        }
        std::move(_items.getValue(), _items.getValue() + _size, newItems.getValue());
        _items = std::move(newItems);
        _capacity = newSize;
    }


    void setSize(size_t newSize) {
        if (newSize > _capacity) {
            throw std::invalid_argument("New size should not exceed capacity");
        }
        _size = newSize;
    }


    size_t capacity() const {
        return _capacity;
    }

    bool isEmpty() const {
        return _size == 0;
    }

    const T &get(size_t index) const {
        if (index >= _size) throw std::runtime_error("Error");
        return _items.getValue()[index];
    }

    T &operator[](size_t index) {
        if (index >= _size) throw std::runtime_error("Error");
        return _items.getValue()[index];
    }

    const T &operator[](size_t index) const {
        if (index >= _size) throw std::runtime_error("Error");
        return _items.getValue()[index];
    }

    void set(size_t index, T value) {
        if (index >= _size) throw std::runtime_error("Error");
        _items.getValue()[index] = std::move(value);
    }

    void add(T value) {
        ensureCapacity(_size + 1);
        _items.getValue()[_size++] = std::move(value);
    }

    void prepend(T value) {
        ensureCapacity(_size + 1);
        std::move_backward(_items.getValue(), _items.getValue() + _size, _items.getValue() + _size + 1);
        _items.getValue()[0] = std::move(value);
        ++_size;
    }

    void insertAt(size_t index, T value) {
        if (index > _size) throw std::runtime_error("Error");
        ensureCapacity(_size + 1);
        if (index < _size) {
            std::move_backward(_items.getValue() + index, _items.getValue() + _size, _items.getValue() + _size + 1);
        }
        _items.getValue()[index] = std::move(value);
        ++_size;
    }


    void shrink_to_fit() {
        if (_capacity > _size) {
            resize(_size);
        }
    }

    T *getRawPointer() {
        return _items.getValue();
    }

    const T *getRawPointer() const {
        return _items.getValue();
    }


    void removeAt(size_t index) {
        if (index >= this->size()) {
            throw std::runtime_error("Error");
        }
        for (size_t i = index; i < this->size() - 1; ++i) {
            _items.getValue()[i] = std::move(_items.getValue()[i + 1]);
        }
        --_size;
    }


    bool contains(const T &value) const {
        for (size_t i = 0; i < _size; ++i) {
            if (_items.getValue()[i] == value) {
                return true;
            }
        }
        return false;
    }


    void clear() {
        _size = 0;
    }

    void print() const {
        for (size_t i = 0; i < _size; ++i) {
            std::cout << _items.getValue()[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif // DYNAMICARRAY_H



