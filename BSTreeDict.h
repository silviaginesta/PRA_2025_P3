#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>> tree;

public:
    BSTreeDict() = default;

    void insert(std::string key, V value) override {
        TableEntry<V> te(key, value);
        tree.insert(te);
    }

    V search(std::string key) override {
        TableEntry<V> te(key);
        if (!tree.search(te)) {
            throw std::runtime_error("Key not found");
        }
        return tree.get(te).value;
    }

    V remove(std::string key) override {
        TableEntry<V> te(key);
        if (!tree.search(te)) {
            throw std::runtime_error("Key not found");
        }
        TableEntry<V> stored = tree.get(te);
        tree.remove(te);
        return stored.value;
    }

    int entries() override {
        return tree.size();
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& dict) {
        out << dict.tree;
        return out;
    }
};

#endif

