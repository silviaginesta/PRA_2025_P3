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

    // Busca TableEntry con esa key; devuelve puntero al valor o nullptr
    const V* search_entry(const std::string& key) const {
        // Recorremos el BST manualmente porque BSTree<T> solo expone insert/search/remove por valor,
        // y el criterio de orden tiene que ser por clave.
        BSNode<TableEntry<V>>* node = tree_root(); // veremos cómo acceder
        while (node != nullptr) {
            if (key < node->data.key) {
                node = node->left;
            } else if (key > node->data.key) {
                node = node->right;
            } else {
                return &node->data.value;
            }
        }
        return nullptr;
    }

    // NECESARIO: acceso de BSTreeDict al root de BSTree
    BSNode<TableEntry<V>>* tree_root() const {
        // truco: como no definimos get_root() en BSTree, convertimos BSTreeDict en friend de BSTree,
        // o añadimos un método público en BSTree. Para no tocar BSTree, vamos a modificar BSTree
        // para que exponga un método get_root() const.
        return tree.get_root();
    }

public:
    BSTreeDict() = default;

    void insert(std::string key, V value) override {
        TableEntry<V> te(key, value);
        tree.insert(te); // BSTree debe ordenar TableEntry por key
    }

    V search(std::string key) override {
        TableEntry<V> te(key);
        if (!tree.search(te)) {
            throw std::runtime_error("Key not found");
        }
        // Para obtener el valor necesitamos algún tipo de búsqueda que devuelva el nodo;
        // solución limpia: añadir a BSTree<T> un método T get(const T& value) const que
        // busque y devuelva el dato almacenado. Lo implementamos así:

        return tree.get(te).value;
    }

    V remove(std::string key) override {
        TableEntry<V> te(key);
        if (!tree.search(te)) {
            throw std::runtime_error("Key not found");
        }
        // Igual que search: primero obtenemos el TableEntry completo, luego lo borramos.
        TableEntry<V> stored = tree.get(te);
        tree.remove(te);
        return stored.value;
    }

    int entries() override {
        return tree.size();
    }

    // Operador [] para acceder como diccionario[key]
    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& dict) {
        out << dict.tree;
        return out;
    }
};

#endif

