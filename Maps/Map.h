#pragma once
#include <ostream>
#include "Collection.h"

template <typename K, typename V>
struct MapEntry
{
    K key;
    V value;
};

template <typename K, typename V>
std::ostream& operator << (std::ostream& out, const MapEntry <K, V> & entry)
{
    out << "{" << entry.key << ", " << entry.value << "}";
    return out;
}

template <typename K, typename V>
class Map : public Collection<const MapEntry<K, V>>
{
public:
    virtual ~Map() { }

    virtual const V& operator[] (const K& key) const = 0;
    virtual V& operator[] (const K& key) = 0;

    //virtual const V* search(const K& key) const = 0;
    //virtual V* search(const K& key) = 0;

    virtual void remove(const K& key) = 0;
    virtual void clear() = 0;
};