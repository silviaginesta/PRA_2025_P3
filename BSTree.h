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

    BSNode<T>* insert_rec(BSNode<T>* node, const T& value) {
        if (node == nullptr) {
            return new BSNode<T>(value);
        }
        if (value < node->data) {
            node->left = insert_rec(node->left, value);
        } else if (value > node->data) {
            node->right = insert_rec(node->right, value);
        } else {
            throw std::runtime_error("Value already exists in BSTree");
        }
        return node;
    }

    bool search_rec(BSNode<T>* node, const T& value) const {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return search_rec(node->left, value);
        return search_rec(node->right, value);
    }

    BSNode<T>* find_min(BSNode<T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }

    BSNode<T>* remove_rec(BSNode<T>* node, const T& value) {
        if (node == nullptr) {
            throw std::runtime_error("Value not found in BSTree");
        }
        if (value < node->data) {
            node->left = remove_rec(node->left, value);
        } else if (value > node->data) {
            node->right = remove_rec(node->right, value);
        } else {
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
                BSNode<T>* minNode = find_min(node->right);
                node->data = minNode->data;
                node->right = remove_rec(node->right, minNode->data);
            }
        }
        return node;
    }

    void inorder_rec(std::ostream& out, BSNode<T>* node) const {
        if (node == nullptr) return;
        inorder_rec(out, node->left);
        out << node->data << " ";
        inorder_rec(out, node->right);
    }

public:
    BSTree() : root(nullptr), n(0) {}

    int size() const {
        return n;
    }

    bool empty() const {
        return n == 0;
    }

    void insert(const T& value) {
        root = insert_rec(root, value);
        n++;
    }

    bool search(const T& value) const {
        return search_rec(root, value);
    }

    void remove(const T& value) {
        root = remove_rec(root, value);
        n--;
    }

    // >>> MÉTODO NUEVO QUE NECESITA BSTreeDict <<<
    T get(const T& value) const {
        BSNode<T>* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return current->data;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        throw std::runtime_error("Value not found in BSTree");
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& tree) {
        tree.inorder_rec(out, tree.root);
        return out;
    }
};

#endif

