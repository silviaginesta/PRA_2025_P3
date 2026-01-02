#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
public:
    T data;
    BSNode<T>* left;
    BSNode<T>* right;

    // Constructores
    BSNode(const T& d, BSNode<T>* l = nullptr, BSNode<T>* r = nullptr)
        : data(d), left(l), right(r) {}

    BSNode() : data(), left(nullptr), right(nullptr) {}
};

// Operador << para imprimir solo el dato del nodo
template <typename T>
std::ostream& operator<<(std::ostream& out, const BSNode<T>& node) {
    out << node.data;
    return out;
}

#endif

