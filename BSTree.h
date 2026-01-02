#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    BSNode<T>* root;
    int n;

    // Inserta recursivo, devuelve nueva raíz de ese subárbol
    BSNode<T>* insert_rec(BSNode<T>* node, const T& value) {
        if (node == nullptr) {
            return new BSNode<T>(value);
        }
        if (value < node->data) {
            node->left = insert_rec(node->left, value);
        } else if (value > node->data) {
            node->right = insert_rec(node->right, value);
        } else {
            // valor duplicado: lanza o ignora según quieras; aquí lanzamos
            throw std::runtime_error("Value already exists in BSTree");
        }
        return node;
    }

    // Busca recursivo
    bool search_rec(BSNode<T>* node, const T& value) const {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return search_rec(node->left, value);
        return search_rec(node->right, value);
    }

    // Encuentra el mínimo (más a la izquierda)
    BSNode<T>* find_min(BSNode<T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // Elimina recursivo, devuelve nueva raíz del subárbol
    BSNode<T>* remove_rec(BSNode<T>* node, const T& value) {
        if (node == nullptr) {
            throw std::runtime_error("Value not found in BSTree");
        }
        if (value < node->data) {
            node->left = remove_rec(node->left, value);
        } else if (value > node->data) {
            node->right = remove_rec(node->right, value);
        } else {
            // nodo encontrado: 0, 1 o 2 hijos
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                BSNode<T>* tmp = node->right;
                delete node;
                return tmp;
            } else if (node->right == nullptr) {
                BSNode<T>* tmp = node->left;
                delete node;
                return tmp;
            } else {
                // 2 hijos: usar sucesor en inorder (mínimo del subárbol derecho)
                BSNode<T>* succ = find_min(node->right);
                node->data = succ->data;
                node->right = remove_rec(node->right, succ->data);
            }
        }
        return node;
    }

    // Borra todo el árbol
    void clear_rec(BSNode<T>* node) {
        if (node == nullptr) return;
        clear_rec(node->left);
        clear_rec(node->right);
        delete node;
    }

    // Imprime inorden en un stream
    void inorder_rec(std::ostream& out, BSNode<T>* node) const {
        if (node == nullptr) return;
        inorder_rec(out, node->left);
        out << node->data << " ";
        inorder_rec(out, node->right);
    }

public:
    BSTree() : root(nullptr), n(0) {}

    ~BSTree() {
        clear_rec(root);
        root = nullptr;
        n = 0;
    }

    bool empty() const { return root == nullptr; }

    int size() const { return n; }

    // Inserta un valor
    void insert(const T& value) {
        root = insert_rec(root, value);
        ++n;
    }

    // Devuelve true si el valor está en el árbol
    bool search(const T& value) const {
        return search_rec(root, value);
    }

    // Elimina un valor, lanza si no está
    void remove(const T& value) {
        root = remove_rec(root, value);
        --n;
    }

    // Imprime el árbol inorden en un ostream
    void print_inorder(std::ostream& out = std::cout) const {
        inorder_rec(out, root);
    }

    // Para que testBSTree pueda hacer std::cout << tree;
    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& tree) {
        tree.inorder_rec(out, tree.root);
        return out;
    }
};

#endif

