#pragma once
#include "HashTableChaining.h"
#include <stdexcept>
#include <iostream>
using namespace std;

/*
   PUNTO 6 – Versión de 10 puntos (por composición)
   HashSet usa internamente un HashTableChaining<T> pero NO permite repetidos.
   - Add(value)  -> lanza excepción si el elemento ya existe.
   - TryAdd(value) -> devuelve false si ya existía (no lanza).
   - Remove(value) -> borra por valor.
   - Contains(value) -> true si existe.
   - Print() -> imprime usando la tabla interna.
*/

template <typename T>
class HashSet
{
private:
    HashTableChaining<T> data; // composición: el set contiene una hash

public:
    // Crea el set con N listas/cubetas internamente
    explicit HashSet(size_t numeroDeListas)
        : data(numeroDeListas) {}

    // Inserta SIN permitir duplicados (lanza si ya existe)
    void Add(const T& value)
    {
        if (data.Encontrar(value))
            throw invalid_argument("HashSet: elemento repetido, no se permite.");
        data.Add(value);
    }

    // Inserta si no existe. Devuelve true si se insertó; false si ya estaba.
    bool TryAdd(const T& value)
    {
        if (data.Encontrar(value))
            return false;
        data.Add(value);
        return true;
    }

    // Elimina por valor (true si se borró)
    bool Remove(const T& value)
    {
        return data.BorrarValor(value);
    }

    // ¿Existe?
    bool Contains(const T& value)
    {
        return data.Encontrar(value);
    }

    // Imprime el contenido
    void Print()
    {
        data.Imprimir();
    }

    // Inserta varios, ignorando duplicados (no lanza)
    void AddRange(const T* values, size_t count)
    {
        for (size_t i = 0; i < count; ++i)
            TryAdd(values[i]);
    }
};

// Demo opcional
void DemostracionHashSet();
