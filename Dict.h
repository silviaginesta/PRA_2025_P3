#ifndef DICT_H
#define DICT_H

#include <string>

template <typename V>
class Dict {
public:
    virtual ~Dict() = default;

    // Inserta key->value; lanza std::runtime_error si key ya existe
    virtual void insert(std::string key, V value) = 0;

    // Busca el valor de key; lanza std::runtime_error si no existe
    virtual V search(std::string key) = 0;

    // Elimina y devuelve el valor de key; lanza std::runtime_error si no existe
    virtual V remove(std::string key) = 0;

    // Número de elementos en el diccionario
    virtual int entries() = 0;
};

#endif

