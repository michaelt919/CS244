#pragma once
#include <functional>
#include "Map.h"
#include "ArrayList.h"

template <typename K, typename V, typename C = std::less<K>>
class SortedArrayMap : public Map<K, V>
{
public:
    SortedArrayMap(unsigned int capacity, C compare = std::less<K>{}, V defaultValue = V {});

    virtual unsigned int getSize() const override;

    virtual void forEach(
        const std::function<void(const MapEntry<K, V>&)>& accept)
        const override;

    virtual void forEach(
        const std::function<void(const MapEntry<K, V>&)>& accept)
        override;

    virtual const V& operator[] (const K& key) const override;
    virtual V& operator[] (const K& key) override;

    virtual void remove(const K& key) override;
    virtual void clear() override;

private:
    ArrayList<MapEntry<K, V>> base;
    V defaultValue;
    C compare;

    int binarySearch(const K& key, int start, int end) const;
};

template<typename K, typename V, typename C>
SortedArrayMap<K, V, C>::SortedArrayMap(unsigned int capacity, C compare, V defaultValue)
    : base{ capacity }, compare{ compare }, defaultValue { defaultValue }
{
}

template<typename K, typename V, typename C>
unsigned int SortedArrayMap<K, V, C>::getSize() const
{
    return base.getSize();
}

template<typename K, typename V, typename C>
void SortedArrayMap<K, V, C>::forEach(const std::function<void(const MapEntry<K, V>&)>& accept) const
{
    base.forEach(accept);
}

template<typename K, typename V, typename C>
void SortedArrayMap<K, V, C>::forEach(const std::function<void(const MapEntry<K, V>&)>& accept)
{
    const ArrayList<MapEntry<K, V>>& cbase { base };
    cbase.forEach(accept);
}

template<typename K, typename V, typename C>
const V& SortedArrayMap<K, V, C>::operator[](const K& key) const
{
    int index = binarySearch(key, 0, base.getSize() - 1);
    if (index == -1)
    {
        return defaultValue;
    }
    else
    {
        return base[index].value;
    }
}

template<typename K, typename V, typename C>
V& SortedArrayMap<K, V, C>::operator[](const K& key)
{
    int index = binarySearch(key, 0, base.getSize() - 1);
    if (index != -1)
    {
        return base[index].value;
    }
    else
    {
        base.add(MapEntry<K, V> { key, defaultValue }); // Extend the list by one element

        // Shift right until we find the right spot for the new item
        unsigned int i = base.getSize() - 1;
        while (i > 0 && compare(key, base[i - 1].key))
        {
            base[i] = base[i - 1];
            i--;
        }

        base[i] = MapEntry<K, V>{ key, defaultValue };
        return base[i].value;
    }
}

template<typename K, typename V, typename C>
void SortedArrayMap<K, V, C>::remove(const K& key)
{
    int index = binarySearch(key, 0, base.getSize() - 1);
    if (index != -1)
    {
        base.remove(index, 1);
    }
}

template<typename K, typename V, typename C>
void SortedArrayMap<K, V, C>::clear()
{
    base.remove(0, base.getSize());
}

template<typename K, typename V, typename C>
int SortedArrayMap<K, V, C>::binarySearch(const K& key, int start, int end) const
{
    if (start > end)
    {
        return -1;
    }
    else
    {
        int middle = (start + end) / 2;
        if (compare(key, base[middle].key))
        {
            return binarySearch(key,
                start, middle - 1);
        }
        else if (compare(base[middle].key, key))
        {
            return binarySearch(key,
                middle + 1, end);
        }
        else
        {
            return middle;
        }
    }
}
