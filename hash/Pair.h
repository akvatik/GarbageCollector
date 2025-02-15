//
// Created by akvat
//

#ifndef GARBAGECOLLECTOR_PAIR_H
#define GARBAGECOLLECTOR_PAIR_H

#include <typeindex>

template <class K, class V>
class Pair {
private:
    K _key;
    V _value;
public:
    Pair(const K &key, const V &value): _key(key), _value(value) {}

    K getKey() const {
        return _key;
    }

    V& getValue() {
        return _value;
    }

    const V& getValue() const {
        return _value;
    }

    Pair<K, V> copy(const V& value) const {
        return Pair(_key, value);
    }

    bool equal(const Pair<K, V>& other) const {
        return _key == other._key && _value == other._value;
    }

    bool operator==(const Pair<K, V>& other) {
        return equal(other);
    }
};
#endif //GARBAGECOLLECTOR_PAIR_H
