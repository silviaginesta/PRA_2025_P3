#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "../../practica1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;   // nº de elementos almacenados
    int max; // nº de cubetas
    ListLinked<TableEntry<V>>* table; // array de listas

    // Función hash: suma ASCII % max
    int h(std::string key) const {
        int sum = 0;
        for (std::size_t i = 0; i < key.size(); ++i) {
            sum += static_cast<unsigned char>(key.at(i));
        }
        return sum % max;
    }

public:
    // Constructor
    HashTable(int size) : n(0), max(size), table(nullptr) {
        if (size <= 0) {
            throw std::invalid_argument("HashTable size must be > 0");
        }
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() override {
        delete[] table;
    }

    // Implementación de Dict<V>

    void insert(std::string key, V value) override {
        int idx = h(key);
        TableEntry<V> probe(key);
        int pos = table[idx].search(probe);
        if (pos != -1) {
            throw std::runtime_error("Key already exists");
        }
        table[idx].append(TableEntry<V>(key, value));
        ++n;
    }

    V search(std::string key) override {
        int idx = h(key);
        TableEntry<V> probe(key);
        int pos = table[idx].search(probe);
        if (pos == -1) {
            throw std::runtime_error("Key not found");
        }
        return table[idx].get(pos).value;
    }

    V remove(std::string key) override {
        int idx = h(key);
        TableEntry<V> probe(key);
        int pos = table[idx].search(probe);
        if (pos == -1) {
            throw std::runtime_error("Key not found");
        }
        TableEntry<V> removed = table[idx].remove(pos);
        --n;
        return removed.value;
    }

    int entries() override {
        return n;
    }

    // Métodos propios

    int capacity() {
        return max;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const HashTable<V>& ht) {
        for (int i = 0; i < ht.max; ++i) {
            out << i << ": ";
            // imprime la lista de esa cubeta
            out << ht.table[i] << "\n";
        }
        return out;
    }
};

#endif

