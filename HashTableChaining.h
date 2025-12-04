#pragma once

#include "LinkedList.h"

// ---- Añadidos mínimos para evitar errores/warnings:
#include <iostream>     // cout
#include <string>       // std::string
#include <type_traits>  // std::is_same_v
using namespace std;
// -----------------------------------------------

template <typename T>
class HashTableChaining
{
public:
	HashTableChaining(size_t _numeroDeListas)
	{
		numeroDeListas = _numeroDeListas;
		if (_numeroDeListas == 0)
		{
			arrayDeListasLigadas = nullptr;
			return;
		}

		arrayDeListasLigadas = new LinkedList<T>[numeroDeListas];
	}

	~HashTableChaining()
	{
		if (arrayDeListasLigadas != nullptr)
		{
			delete[] arrayDeListasLigadas;
		}
	}

	void Add(T value)
	{
		// Inserta el elemento con valor 'value' en el índice que nos dice la función hash.
		size_t indice = FuncionHash(value);
		arrayDeListasLigadas[indice].PushBack(value);
	}

	bool BorrarValor(T value)
	{
		size_t indice = FuncionHash(value);
		return arrayDeListasLigadas[indice].BorrarNodoPorValor(value);
	}

	bool Encontrar(T value)
	{
		size_t indice = FuncionHash(value);
		return arrayDeListasLigadas[indice].Encontrar(value);
	}

	void Imprimir()
	{
		// Por cada cubeta
		for (size_t i = 0; i < numeroDeListas; i++) // <-- i ahora es size_t para evitar warning signed/unsigned
		{
			if (arrayDeListasLigadas[i].GetCount() == 0)
			{
				cout << "vacia" << endl;
			}
			else
				arrayDeListasLigadas[i].Print();
		}
	}

private:

	// Recibe una llave (del tipo de dato 'T' que almacena esta tabla) y 
	// retorna un entero que es el índice de en qué espacio de arrayDeListasLigadas debe estar.
	size_t FuncionHash(T llave)
	{
		// Guard para evitar división entre cero si alguien usa la tabla con 0 cubetas.
		if (numeroDeListas == 0) 
			return 0;

		if constexpr (is_same_v<T, string>)
		{
			// entonces sí es una string.
			string llaveString = static_cast<string>(llave);
			// Si la cadena está vacía, mándala a la cubeta 0.
			if (llaveString.empty())
				return 0;
			return ((size_t)llaveString[0] - 65); // 65 es el código de la A mayúscula en ASCII
		}
		else
		{
			// NOTA: esto (en teoría) solo debería funcionar para valores numéricos, no para otros tipos de dato.
			return (size_t)llave % numeroDeListas;
		}
	}

	// Dijimos que tiene N índices, y en cada uno de esos índices tiene un contenedor,
	// en este caso, una lista ligada (linkedList)
	LinkedList<T>* arrayDeListasLigadas;
	// Normalmente a esos N índices les llaman "buckets" o cubetas.

	// Variable que nos dice cuántos índices tiene esta hash table. Para saber hasta dónde se puede acceder 
	// con el puntero de arrayDeListasLigadas.
	size_t numeroDeListas;

};

void DemostracionHashTableChaining();
