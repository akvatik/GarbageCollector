//
// Created by akvat
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ElementUP.h"
#include "../pointer/ShrdPtr.h"
#include <stdexcept>

template<class T>
class LinkedListUP {
private:
    ShrdPtr<ElementUP<T>> _first;
    ShrdPtr<ElementUP<T>> _last;
    size_t _length;

public:
    LinkedListUP() : _first(nullptr), _last(nullptr), _length(0) {}

    void append(T value) {
        ShrdPtr<ElementUP<T>> newElement(new ElementUP<T>(value));
        if (_first.get() == nullptr) {
            _first = newElement;
            _last = newElement;
        } else {
            _last->setNext(newElement);
            newElement->setPrevious(_last);
            _last = newElement;
        }
        ++_length;
    }

    void prepend(T value) {
        ShrdPtr<ElementUP<T>> newElement(new ElementUP<T>(value));
        if (_first.get() == nullptr) {
            _first = newElement;
            _last = newElement;
        } else {
            newElement->setNext(_first);
            _first->setPrevious(newElement);
            _first = newElement;
        }
        ++_length;
    }

    void remove(size_t index) {
        if (index >= _length)
            throw std::out_of_range("Index out of range");

        ShrdPtr<ElementUP<T>> current = _first;
        for (size_t i = 0; i < index; ++i) {
            current = current->getNext();
        }

        ShrdPtr<ElementUP<T>> prev = current->getPrevious();
        ShrdPtr<ElementUP<T>> next = current->getNext();

        if (prev.get() != nullptr) {
            prev->setNext(next);
        } else {
            _first = next;
        }

        if (next.get() != nullptr) {
            next->setPrevious(prev);
        } else {
            _last = prev;
        }

        --_length;
    }

    T get(size_t index) const {
        if (index >= _length)
            throw std::out_of_range("Index out of range");

        ShrdPtr<ElementUP<T>> current = _first;
        for (size_t i = 0; i < index; ++i) {
            current = current->getNext();
        }
        return current->get();
    }

    void removeValue(const T& value) {
        size_t index = 0;
        ShrdPtr<ElementUP<T>> current = _first;
        while (current.get() != nullptr) {
            if (current->get() == value) {
                remove(index);
                return;
            }
            current = current->getNext();
            ++index;
        }
    }

    size_t size() const {
        return _length;
    }

    bool isEmpty() const {
        return _length == 0;
    }

    void clear() {
        _first.reset(nullptr);
        _last.reset(nullptr);
        _length = 0;
    }
};

#endif // LINKEDLIST_H



