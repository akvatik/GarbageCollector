//
// Created by akvat
//

#ifndef GARBAGECOLLECTOR_ELEMENTUP_H
#define GARBAGECOLLECTOR_ELEMENTUP_H

#include "../pointer/ShrdPtr.h"

template<class T>
class ElementUP {
private:
    ShrdPtr<ElementUP<T>> _previous;
    ShrdPtr<ElementUP<T>> _next;
    T _value;

public:
    // Конструкторы
    explicit ElementUP(T value)
            : _value(value), _previous(nullptr), _next(nullptr) {}

    ElementUP(T value, const ShrdPtr<ElementUP<T>>& previous, const ShrdPtr<ElementUP<T>>& next)
            : _value(value), _previous(previous), _next(next) {}

    T get() const { return _value; }
    void set(T value) { _value = value; }

    ShrdPtr<ElementUP<T>> getPrevious() const { return _previous; }
    ShrdPtr<ElementUP<T>> getNext() const { return _next; }

    void setPrevious(const ShrdPtr<ElementUP<T>>& previous) { _previous = previous; }
    void setNext(const ShrdPtr<ElementUP<T>>& next) { _next = next; }
};

#endif //GARBAGECOLLECTOR_ELEMENTUP_H

