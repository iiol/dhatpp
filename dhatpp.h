#ifndef DHATPP_H
#define DHATPP_H

#include <iostream>
#include <vector>
#include <tuple>

namespace dhatpp {

using namespace std;

template <typename T>
class HashTable {
    float factor;
    unsigned int maxdepth;
    vector<vector<tuple<string, T>>> ht;

    unsigned long gethash_djb2(const string &s) const;
    HashTable<T> *rebuild(unsigned int new_size) const;
    T &force_get(const string &key);

public:
    HashTable(float f, unsigned int max, unsigned int sz = 1) {
        if (f <= 0)
            throw runtime_error("HashTable::HashTable(float, unsigned int, unsigned int): "
                                "factor can't be less than or equal to zero");
        else if (!max)
            throw runtime_error("HashTable::HashTable(float, unsigned int, unsigned int): "
                                "max depth can't be zero");
        else if (!sz)
            throw runtime_error("HashTable::HashTable(float, unsigned int, unsigned int): "
                                "hash table size can't be zero");

        factor = f;
        maxdepth = max;
        ht.resize(sz);
    }

    T &operator[](const string &key);
    T &operator[](const char *key);

    template<typename U>
    friend ostream &operator<<(ostream &out, HashTable<U> &this_ht);

    void put(const string &key, const T &value);
    bool check(const string &key) const;
    T &get(const string &key);

    size_t size(void) const;
};

template<typename T>
HashTable<T> *HashTable<T>::rebuild(unsigned int new_size) const {
    HashTable *newht = new HashTable(factor, maxdepth, new_size);
    clog << "Creating new hash table: 0x" << newht << endl;
    clog << "Size: " << size() << "->" << new_size << endl;

    for (auto &entry : ht) {
        for (auto &[k, v] : entry) {
            newht->put(k, v);
        }
    }

    return newht;
}

template<typename T>
unsigned long HashTable<T>::gethash_djb2(const string &s) const {
    unsigned int hash = 5381;
    for (char c : s)
        hash += (hash << 5) + uint8_t(c);
    return hash % ht.size();
}

template<typename T>
T &HashTable<T>::force_get(const string &key) {
    for (auto &[k, v] : this->ht[this->gethash_djb2(key)]) {
        if (k == key)
            return v;
    }

    this->put(key, T{});
    return this->get(key);
}

template<typename T>
T &HashTable<T>::operator[](const string &key) {
    return this->force_get(key);
}

template<typename T>
T &HashTable<T>::operator[](const char *key) {
    return this->force_get(string(key));
}

template<typename T>
ostream &operator<<(ostream &out, HashTable<T> &this_ht) {
    int i = 0;

    for (auto &entry : this_ht.ht) {
        out << i++ << ")";

        for (auto &[k, v] : entry)
            out << " (\"" << k << "\", " << v << ")";

        out << endl;
    }

    return out;
}

template<typename T>
void HashTable<T>::put(const string &key, const T &value) {
    auto hash = gethash_djb2(key);

    for (auto &[k, _] : this->ht[hash]) {
        if (k == key)
            return;
    }

    this->ht[hash].push_back(tuple<string, T>{key, value});

    if (this->ht[hash].size() > maxdepth) {
        HashTable *newht = rebuild(unsigned((float(this->ht.size()) * factor)));

        this->ht = newht->ht;
        clog << "Removing new hash table: 0x" << newht << endl;

        delete newht;
    }
}

template<typename T>
bool HashTable<T>::check(const string &key) const {
    for (auto &[k, _] : this->ht[gethash_djb2(key)]) {
        if (k == key)
            return true;
    }

    return false;
}

template<typename T>
T &HashTable<T>::get(const string &key) {
    for (auto &[k, v] : this->ht[gethash_djb2(key)]) {
        if (k == key)
            return v;
    }

    throw runtime_error("HashTable::get(string): Can't find entry by key");
}

template<typename T>
size_t HashTable<T>::size(void) const {
    return this->ht.size();
}

}

#endif // DHATPP_H
