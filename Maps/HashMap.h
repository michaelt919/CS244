#pragma once
#include <functional>
#include <stdexcept>
#include "Map.h"

template <typename K, typename V>
struct HashMapEntry
{
    MapEntry<K, V> data;
    bool used = false;
};


template <typename K, typename V, typename H = std::hash<K>, typename E = std::equal_to<K>>
class HashMap : public Map<K, V>
{
public:
    HashMap(unsigned int capacity = 16, H hash = std::hash<K>{}, E equals = std::equal_to<K>{}, V defaultValue = V {});
    HashMap(const HashMap<K, V, H, E>& original);
    ~HashMap();
    HashMap<K, V, H, E>& operator= (const Map<K, V>& original);
    HashMap<K, V, H, E>& operator= (const HashMap<K, V, H, E>& original);

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
    HashMapEntry<K, V>* table;
    unsigned int capacity;
    unsigned int size { 0 };
    const H hash;
    const E equals;
    const V defaultValue;

    void rehash(unsigned int newCapacity);
    unsigned int hashSearch(HashMapEntry<K, V>* table, unsigned int capacity, const K& key) const;
};

template<typename K, typename V, typename H, typename E>
HashMap<K, V, H, E>::HashMap(unsigned int capacity, H hash, E equals, V defaultValue)
    :   capacity{ capacity },
        table{ new HashMapEntry<K, V>[capacity] {} },
        hash{ hash },
        equals{ equals },
        defaultValue{ defaultValue }
{
}

template<typename K, typename V, typename H, typename E>
HashMap<K, V, H, E>::HashMap(const HashMap<K, V, H, E>& original)
    : HashMap { original.getSize() * 4, original.hash, original.equals, original.defaultValue }
{
    size = original.getSize();

    original.forEach([&](MapEntry<K, V> entry)
    {
        unsigned int index = hashSearch(table, capacity, entry.key);
        table[index] = HashMapEntry<K, V> { entry, true };
    });
}

template<typename K, typename V, typename H, typename E>
HashMap<K, V, H, E>::~HashMap()
{
    delete[] table;
}

template<typename K, typename V, typename H, typename E>
HashMap<K, V, H, E>& HashMap<K, V, H, E>::operator=(const Map<K, V>& original)
{
    clear();

    if (2 * original.getSize() >= capacity)
    {
        rehash(4 * original.getSize());
    }

    size = original.getSize();

    original.forEach([&](MapEntry<K, V> entry)
    {
        unsigned int index = hashSearch(table, capacity, entry.key);
        table[index] = HashMapEntry<K, V>{ entry, true };
    });

    return *this;
}

template<typename K, typename V, typename H, typename E>
HashMap<K, V, H, E>& HashMap<K, V, H, E>::operator=(const HashMap<K, V, H, E>& original)
{
    return *this = static_cast<const Map<K, V>&>(original);
}

template<typename K, typename V, typename H, typename E>
unsigned int HashMap<K, V, H, E>::getSize() const
{
    return size;
}

template<typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::forEach(const std::function<void(const MapEntry<K, V>&)>& accept) const
{
    if (size > 0)
    {
        for (unsigned int i = 0; i < capacity; i++)
        {
            const HashMapEntry <K, V>& entry = table[i];
            if (entry.used)
            {
                accept(entry.data);
            }
        }
    }
}

template<typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::forEach(const std::function<void(const MapEntry<K, V>&)>& accept)
{
    if (size > 0)
    {
        for (unsigned int i = 0; i < capacity; i++)
        {
            const HashMapEntry <K, V>& entry = table[i];
            if (entry.used)
            {
                accept(entry.data);
            }
        }
    }
}

template<typename K, typename V, typename H, typename E>
const V& HashMap<K, V, H, E>::operator[](const K& key) const
{
    unsigned int index = hashSearch(table, capacity, key);
    const HashMapEntry <K, V>& entry = table[index];
    if (entry.used)
    {
        return entry.data.value;
    }
    else
    {
        return defaultValue;
    }
}

template<typename K, typename V, typename H, typename E>
V& HashMap<K, V, H, E>::operator[](const K& key)
{
    unsigned int index = hashSearch(table, capacity, key);

    if (!table[index].used)
    {
        if (2 * size >= capacity)
        {
            rehash(4 * size);
            index = hashSearch(table, capacity, key);
        }

        table[index] = HashMapEntry<K, V>{ MapEntry<K, V> { key, defaultValue }, true };
        size++;
    }

    return table[index].data.value;
}

template<typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::remove(const K& key)
{
    throw logic_error("not implemented");
}

template<typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::clear()
{
    for (unsigned i = 0; i < capacity; i++)
    {
        table[i].used = false;
    }

    size = 0;
}

template<typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::rehash(unsigned int newCapacity)
{
    HashMapEntry<K, V>* newTable = new HashMapEntry<K, V>[newCapacity] { };

    forEach([&](const MapEntry<K, V>& entry)
    {
        unsigned int index = hashSearch(newTable, newCapacity, entry.key);
        newTable[index] = HashMapEntry<K, V> { entry, true };
    });

    delete[] table;
    table = newTable;
    capacity = newCapacity;
}

template<typename K, typename V, typename H, typename E>
unsigned int HashMap<K, V, H, E>::hashSearch(HashMapEntry<K, V>* table, unsigned int capacity, const K& key) const
{
    // Transform hash code into a legal array index
    unsigned int i = hash(key) % capacity;

    // Linear probing
    while (table[i].used && !equals(table[i].data.key, key))
    {
        i++;

        if (i == capacity)
        {
            i = 0;
        }
    }

    return i;
}
