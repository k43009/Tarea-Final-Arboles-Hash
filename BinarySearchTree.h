#pragma once
#include <iostream>
using namespace std;
#include<vector> // Recuerden, "vector" es el nombre del DynamicArray en c++ STL.
#include<stack>  // <-- agregado para la versión iterativa de Post-order
#include<stdexcept> // <-- por invalid_argument en BorrarPorValor
#include <utility>

template <typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{
		root = nullptr;
	}

	// A�ade un elemento de tipo T al �rbol.
	void Add(T value)
	{
		// Si no hay nodo ra�z... 
		if (root == nullptr)
		{
			// entonces este valor se va a convertir en el nodo ra�z.
			root = new Node(value);
			return; // y nos salimos porque ya lo insertamos.
		}

		// Se mueve por el �rbol usando izquierda-derecha hasta encontrar un lugar en el �rbol que est� vac�o.
		// Necesitamos una variable que representa el nodo contra el cual se est� comparando value en cada iteraci�n
		Node* nodoActual = root;
		// while(true) es que se ejecute infinitamente,
		// entonces DEBE haber algo dentro del while que nos permita salir de �l.
		while (true) 
		{
			// Si me tengo que ir a la derecha Y el hijo derecho del NodoActual es nullptr...
			// si el valor de value es mayor que el del nodo actual...
			if (value > nodoActual->value)
			{
				// ... entonces me tengo que ir a la derecha, 
				// PERO primero checo si el nodo a la derecha del actual NO es nullptr
				if (nodoActual->rightChild != nullptr)
				{
					nodoActual = nodoActual->rightChild;
					continue; // continue te devuelve al inicio del while.
				}
				else // si no tiene hijo derecho...
				{
					// ... entonces value se convierte en el hijo derecho del nodo actual.
					Node* nodoConNuevoValor = new Node(value);
					nodoActual->rightChild = nodoConNuevoValor;
					// El nuevo nodo ahora apunta al nodo actual como su padre
					nodoConNuevoValor->parent = nodoActual;
					// Ya que metimos el nuevo nodo, ya acabamos la funci�n y nos salimos.
					return;
				}
			}
			// NOTA 2: Su compa�ero Juan Alexis se lleva 5 puntos extras en el parcial final por haber notado el problema con anticipaci�n.
			// NOTA: PARA EL CASO DE LA CLASE, ESTE �RBOL VA A TRATAR A LOS VALORES IGUALES MAND�NDOLOS A LA IZQUIERDA
			// VA A HABER OCASIONES EN LAS QUE LOS �RBOLES NO PERMITAN REPETIDOS.
			else if (value <= nodoActual->value) // si fuimos menores O IGUALES ... 
			{
				// ... entonces nos tenemos que ir a la izquierda
				// PERO primero checo si el nodo a la izquierda del actual NO es nullptr
				if (nodoActual->leftChild != nullptr)
				{
					// entonces S� tiene un hijo izquierdo
					nodoActual = nodoActual->leftChild;
					continue; // continue te devuelve al inicio del while.
				}
				else // si no tiene hijo izquierdo...
				{
					// ... entonces value se covierte en el hijo izquierdo del nodo actual.
					Node* nodoConNuevoValor = new Node(value);
					nodoActual->leftChild = nodoConNuevoValor;
					// El nuevo nodo ahora apunta al nodo actual como su padre
					nodoConNuevoValor->parent = nodoActual;
					// Ya que metimos el nuevo nodo, ya acabamos la funci�n y nos salimos.
					return;
				}
			}
		}
	}


	// Buscar elemento
	bool Find(T value)
	{
		Node* resultado = FindNode(value);
		if (resultado == nullptr)
			return false; // no se encontr�.
		return true; // s� se encontr�
	}

	/****************** NUEVO: Search iterativo (público) ******************/
	// 1) Implementar la funci�n "Search" del Binary Search Tree de manera iterativa (10 puntos).
	bool Search(T value)
	{
		// Checar que la ra�z sea v�lida
		if (root == nullptr)
			return false; //si la ra�z es inv�lida, cualquier b�squeda dar� falso.

		// puntero auxiliar hacia el nodo que actualmente estamos checando en el �rbol.
		Node* nodoActual = root;
		// Mientras este nodo actual siga siendo un nodo v�lido...
		while (nodoActual != nullptr)
		{
			// checamos si el nodo actual tiene el valor igual al que estamos buscando.
			if (nodoActual->value == value)
				return true; // encontrado

			// decidir a qué hijo avanzar
			if (value > nodoActual->value)
				nodoActual = nodoActual->rightChild;
			else
				nodoActual = nodoActual->leftChild;
		}
		// no se encontró
		return false;
	}
	/**********************************************************************/


	// borrar elemento

	// Retorna el valor m�s alto en el �rbol.
	T MaxValue()
	{
		// Es solamente irse por los hijos derechos hasta que ya no haya m�s.
		// Checar que la ra�z sea v�lida
		if (root == nullptr)
		{
			cerr << "Error, se llam� la funci�n MaxValue pero el �rbol est� vac�o." << endl;
			return T{}; // regresamos un valor por defecto.
		}

		// puntero auxiliar hacia el nodo que actualmente estamos checando en el �rbol.
		Node* nodoActual = root;
		// Mientras el hijo derecho de este nodo actual siga siendo un nodo v�lido...
		while (nodoActual->rightChild != nullptr)
		{
			nodoActual = nodoActual->rightChild;
		}
		// Retornamos el valor del nodo actual, ya que es el valor m�s alto.
		return nodoActual->value;
	}

	// Retorna el valor m�s bajo en el �rbol.
	T MinValue()
	{
		// Es solamente irse por los hijos izquierdos hasta que ya no haya m�s.
		// Checar que la ra�z sea v�lida
		if (root == nullptr)
		{
			cerr << "Error, se llam� la funci�n MinValue pero el �rbol est� vac�o." << endl;
			return T{}; // regresamos un valor por defecto.
		}

		// puntero auxiliar hacia el nodo que actualmente estamos checando en el �rbol.
		Node* nodoActual = root;
		// Mientras el hijo izquierdo de este nodo actual siga siendo un nodo v�lido...
		while (nodoActual->leftChild != nullptr)
		{
			nodoActual = nodoActual->leftChild;
		}
		// Retornamos el valor del nodo actual, ya que es el valor m�s bajo.
		return nodoActual->value;
	}

	T Siguiente(T value)
	{
		// Checamos que el valor value est� presente en el �rbol y obtenemos dicho nodo
		Node* nodoConValue = FindNode(value);
		if (nodoConValue == nullptr)
		{
			// Imprimimos un error y regresamos un error por defecto.
			cerr << "ERROR, no existe un nodo con valor: " << value << " en este �rbol, no hay sucesor para �l" << endl;
			return T{};
		}

		// SI s� existe, mandamos a llamar la de sucesor
		// pero tenemos que checar que s� haya un sucesor
		Node* sucesor = Sucesor(nodoConValue);
		if (sucesor == nullptr)
		{
			cout << "No hay sucesor para el nodo con valor: " << value << " en este �rbol" << endl;
			return T{};
		}
		return sucesor->value;
	}

	T Anterior(T value)
	{
		// Checamos que el valor value est� presente en el �rbol y obtenemos dicho nodo
		Node* nodoConValue = FindNode(value);
		if (nodoConValue == nullptr)
		{
			// Imprimimos un error y regresamos un error por defecto.
			cerr << "ERROR, no existe un nodo con valor: " << value << " en este �rbol, no hay predecesor para �l" << endl;
			return T{};
		}

		// SI s� existe, mandamos a llamar la de predecesor
		// pero tenemos que checar que s� haya un predecesor
		Node* predecesor = Predecesor(nodoConValue);
		if (predecesor == nullptr)
		{
			cout << "No hay predecesor para el nodo con valor: " << value << " en este �rbol" << endl;
			return T{};
		}
		return predecesor->value;
	}

	// Borra el primer nodo encontrado que tenga dicho valor
	bool BorrarPorValor(T valor)
	{
		// como siempre en �rboles, empezamos desde la ra�z.
		if (root == nullptr)
		{
			// sin el try-catch, porque esto es un error grave.
			throw invalid_argument("Este �rbol est� vac�o");
			return false; // por si le quieren seguir depurando incluso tras este error.
		}
		// Primero que todo, hay que encontrar si est� un nodo con dicho valor.
		Node* nodoABorrar = FindNode(valor);
		// Si el nodo A Borrar es nullptr, entonces no existe un nodo con dicho valor
		if (nodoABorrar == nullptr)
		{
			// sin el try-catch, porque esto es un error grave.
			throw invalid_argument("No hay nodo con dicho valor en este �rbol");
			return false; // por si le quieren seguir depurando incluso tras este error.
		}

		// Si s� hay dicho nodo, checamos en cu�l de los 3 casos de Borrado cae:
		/* 1) Si X no tiene hijos (si su left y su right son nullptr),
		haces que el puntero a hijo de su padre que apunta a este
		nodo sea null y luego borras este nodo. No requieres reconexiones. */
		if (nodoABorrar->leftChild == nullptr && nodoABorrar->rightChild == nullptr)
		{
			// Entonces estamos en el caso 1, que es el m�s f�cil.
			DeleteCaso1(nodoABorrar);
			return true;;
		}
		// Aqu� quiere decir que tiene al menos un hijo. 
		// Checamos si tiene solo 1 de los 2 hijos.
		if (nodoABorrar->leftChild == nullptr && !(nodoABorrar->rightChild == nullptr) ||
			!(nodoABorrar->leftChild == nullptr) && nodoABorrar->rightChild == nullptr)
		{
			// Entonces estamos en el caso #2:
			DeleteCaso2(nodoABorrar);
			return true;
		}

		// Si lleg� hasta esta parte del c�digo, entonces estamos en el Caso #3,
		// el nodo a borrar tiene sus dos hijos.
		// 1. Encontrar sucesor 'Y' del nodo a Borrar 'X'
		Node* nodoSucesor = Sucesor(nodoABorrar);
		Node* hijoDerechoDelSucesor = nodoSucesor->rightChild;
		Node* padreDelSucesor = nodoSucesor->parent;


		// El resto del sub�rbol derecho de X se vuelve el sub�rbol derecho de �Y�.
		// En pocas palabras: el sucesor ahora apunta hacia donde antes apuntaba el nodo a borrar
		nodoSucesor->leftChild = nodoABorrar->leftChild;
		// Necesitamos asegurarnos de que el sucesor NO es el mismo hijo derecho del nodo a borrar
		if(nodoSucesor != nodoABorrar->rightChild)
			nodoSucesor->rightChild = nodoABorrar->rightChild;

		nodoSucesor->leftChild->parent = nodoSucesor;
		
		if (nodoSucesor->rightChild != nullptr) // tenemos que asegurarnos de que no es nulo.
		{
			nodoSucesor->rightChild->parent = nodoSucesor;
		}

		// Ahora hacemos la conexi�n del sucesor con el padre del nodo que se va a borrar.
		nodoSucesor->parent = nodoABorrar->parent;
		// Primero checamos que el parent no sea nullptr (el caso donde se est� borrando al nodo Ra�z)
		if (nodoABorrar->parent != nullptr)
		{
			// Necesitamos saber si el nodo a borrar era hijo izquierdo o derecho de su padre
			if (nodoABorrar->parent->leftChild == nodoABorrar)
				nodoSucesor->parent->leftChild = nodoSucesor;
			else
				nodoSucesor->parent->rightChild = nodoSucesor;
		}
		else // si entra a este else, se est� borrando al nodo ra�z
		{
			// tenemos que actualizar el puntero a la ra�z
			root = nodoSucesor;
		}

		// NOTA: Seg�n yo, a fuerzas es el hijo izquierdo, porque sino no ser�a el sucesor.
		if (padreDelSucesor != nullptr)
			padreDelSucesor->leftChild = hijoDerechoDelSucesor;

		// SOLO SI EL SUCESOR TIENE HIJO DERECHO
		if (hijoDerechoDelSucesor != nullptr)
		{
			// El hijo derecho de �Y� antes de moverlo se recorre a la posici�n donde estaba 'Y'
			// Reconectar al pap� de Y con el hijo derecho de Y y viceversa
			hijoDerechoDelSucesor->parent = padreDelSucesor;
		}


		delete nodoABorrar;
		return true;
	}


	// Es la versi�n p�blica de la funci�n, que un usuario puede utilizar.
	// La otra de InOrderRecursivo NO es p�blica porque los usuarios no deben manipular nodos del �rbol 
	// directamente nunca.
	void InOrderRecursivo()
	{
		cout << "In order Recursivo: ";
		InOrderRecursivo(root);
		cout << endl;
	}

	void PreOrderRecursivo()
	{
		cout << "Pre order Recursivo: ";
		PreOrderRecursivo(root);
		cout << endl;
	}

	void PostOrderRecursivo()
	{
		cout << "Post order Recursivo: ";
		PostOrderRecursivo(root);
		cout << endl;
	}

	/****************** NUEVO: Post-order iterativo ******************/
	// 3) Implementar la funci�n Post-order del Binary Search Tree de manera iterativa. (10 puntos).
	void PostOrderIterativo()
	{
		cout << "Post order Iterativo: ";
		Node* nodoActual = root;
		stack<Node*> pila;
		Node* ultimoVisitado = nullptr;

		while (nodoActual != nullptr || !pila.empty())
		{
			if (nodoActual != nullptr)
			{
				pila.push(nodoActual);
				nodoActual = nodoActual->leftChild;
			}
			else
			{
				Node* tope = pila.top();
				// si hay hijo derecho NO visitado, ve a �l
				if (tope->rightChild != nullptr && ultimoVisitado != tope->rightChild)
				{
					nodoActual = tope->rightChild;
				}
				else
				{
					cout << tope->value << ", ";
					ultimoVisitado = tope;
					pila.pop();
				}
			}
		}
		cout << endl;
	}
	/*****************************************************************/

	pair<T, T> ObtenerMinimoYMaximo()
	{
		T max = MaxValue();
		T min = MinValue();
		return pair<T, T>(min, max);
	}

	T* ObtenerRaizMinimoYMaximo()
	{
		T* resultado = new T[3];
		resultado[0] = root->value;
		resultado[1] = MinValue();
		resultado[2] = MaxValue();
		return resultado;
	}

	vector<T> ObtenerRaizMinimoYMaximoConVector()
	{
		vector<T> resultado;
		resultado.push_back(root->value);
		resultado.push_back(MinValue());
		resultado.push_back(MaxValue());
		return resultado;
	}

	/****************** NUEVO: Borrar subárbol en postorden (recursivo) ******************/
	/*
	2) Implementar una funci�n de la clase Binary Search Tree una funci�n que haga:
		1.Viaja al sub-�rbol izquierdo de este nodo, recursivamente.
		2.Viaja al sub-�rbol derecho de este nodo, recursivamente.
		3.borra el nodo actual.
	Puede ser recursiva (20 puntos) o iterativa (30 puntos). D�nle un nombre apropiado.
	*/
	// Wrapper p�blico que borra TODO el �rbol en post-orden y deja root = nullptr.
	void BorrarTodoPostOrdenRecursivo()
	{
		BorrarSubarbolPostOrdenRecursivo(root);
		root = nullptr;
	}
	/****************************************************************************************/

	/****************** NUEVO: Versión ITERATIVA (30 pts) de borrar todo ******************/
	// Misma lógica (post-orden) pero sin recursión, usando una pila y control de "último visitado".
	void BorrarTodoPostOrdenIterativo()
	{
		if (root == nullptr) return;

		stack<Node*> pila;
		Node* nodoActual = root;
		Node* ultimoVisitado = nullptr;

		while (nodoActual != nullptr || !pila.empty())
		{
			if (nodoActual != nullptr)
			{
				pila.push(nodoActual);
				nodoActual = nodoActual->leftChild;
			}
			else
			{
				Node* tope = pila.top();
				// si existe hijo derecho no visitado, primero baja a él
				if (tope->rightChild != nullptr && ultimoVisitado != tope->rightChild)
				{
					nodoActual = tope->rightChild;
				}
				else
				{
					// Post-orden: izquierda, derecha y AHORA el nodo actual -> se borra
					ultimoVisitado = tope;
					pila.pop();
					delete tope;
				}
			}
		}
		root = nullptr;
	}
	/****************************************************************************************/

private:
	// Cada nodo pesa 3 punteros (8 bytes por puntero en un sistema operativo de 64 bits)
	// m�s los bytes que pese T. Entonces los �rboles gastan  mucha m�s memoria que los arrays.
	class Node
	{
	public:
		Node(T _value)
		{
			value = _value;
			parent = nullptr;
			rightChild = nullptr;
			leftChild = nullptr;
		}

		T value;
		// Puntero hacia el Nodo padre. 
		Node* parent;
		// Puntero hacia el hijo derecho
		Node* rightChild;
		// puntero hacia el hijo izquierdo
		Node* leftChild;
	};


	void DeleteCaso1(Node* nodoABorrar)
	{
		// primero tenemos que checar que este nodo S� tenga un padre,
		if (nodoABorrar->parent == nullptr)
		{
			// si no tiene padre, entonces este nodo a borrar es la ra�z :D y simplemente se borra
			delete nodoABorrar;
			root = nullptr;
			return;
		}
		// nodoABorrar checa si es el hijo izquierdo O derecho de su padre 
		if (nodoABorrar->parent->leftChild == nodoABorrar) // checamos si nodo a borrar es hijo izquierdo
		{
			// entonces s� es el hijo izquierdo
			nodoABorrar->parent->leftChild = nullptr; // le dice a su pap� que ya no tiene hijo izquierdo
		}
		else
		{
			// si no, nodo a borrar es el hijo derecho
			nodoABorrar->parent->rightChild = nullptr; // le dice a su pap� que ya no tiene hijo derecho
		}

		// sin importar si es hijo derecho o izquierdo, pues se borra este nodo.
		delete nodoABorrar;
	}

	void DeleteCaso2(Node* nodoABorrar)
	{
		// Si X solo tiene un hijo, haces que dicho hijo tome el lugar de X en el �rbol y
		// luego borramos X. Requiere 2 reconexiones (del padre de X al hijo de X y viceversa).
		// Que el parent del hijo de X ahora sea el parent de X
		Node* hijoDeNodoABorrar = nullptr;

		if (nodoABorrar->leftChild == nullptr) // si el izquierdo es nullptr, el derecho es el hijo v�lido
			hijoDeNodoABorrar = nodoABorrar->rightChild;
		else
			hijoDeNodoABorrar = nodoABorrar->leftChild; // y si no, entonces el izquierdo es el v�lido


		hijoDeNodoABorrar->parent = nodoABorrar->parent;

		// tenemos que checar que no sea la ra�z:
		if (nodoABorrar == root)
		{
			root = hijoDeNodoABorrar;
		}
		// checamos si el nodo a borrar es el hijo izquierdo o derecho de su padre para conectar al 
		// abuelo con su nieto
		else if (nodoABorrar->parent->leftChild == nodoABorrar)
			nodoABorrar->parent->leftChild = hijoDeNodoABorrar;
		else
			nodoABorrar->parent->rightChild = hijoDeNodoABorrar;

		// y por �ltimo borramos al nodo a borrar
		delete nodoABorrar;
	}


	// Buscar elemento
	Node* FindNode(T value)
	{
		// Checar que la ra�z sea v�lida
		if (root == nullptr)
			return nullptr; //si la ra�z es inv�lida, cualquier b�squeda dar� falso.

		// puntero auxiliar hacia el nodo que actualmente estamos checando en el �rbol.
		Node* nodoActual = root;
		// Mientras este nodo actual siga siendo un nodo v�lido...
		while (nodoActual != nullptr)
		{
			// checamos si el nodo actual tiene el valor igual al que estamos buscando.
			if (nodoActual->value == value)
				return nodoActual; // si s� es igual, ya lo encontramos.

			// Si no tiene el valor buscado, tenemos que ver si ahora el actual va a ser su hijo derecho o izquierdo
			// Si value es mayor que el valor del nodo actual...
			if (value > nodoActual->value)
			{
				// ... entonces el nodo actual ahora avanza a su hijo derecho
				nodoActual = nodoActual->rightChild;
			}
			else
			{
				// ... y si no, entonces el nodo actual ahora avanza a su hijo izquierdo 
				nodoActual = nodoActual->leftChild;
			}
		}
		// este while se rompe cuando se llega a la posici�n donde deber�a estar value, pero en su lugar hay nullptr.
		// entonces, en este punto ya no se encontr� value, y regresamos false.
		return nullptr;
	}

	Node* Sucesor(Node* node)
	{
		// Caso 1: El nodo s� tiene un hijo derecho
		if (node->rightChild != nullptr)
		{
			// Paso 1: Dar un paso a la derecha
			Node* nodoActual = node->rightChild; // este nodo auxiliar es como el "nodoActual" que usamos en otras funciones.

			// Paso 2: irte lo m�s a la izquierda que se pueda desde ah�.
			while (nodoActual->leftChild != nullptr)
				nodoActual = nodoActual->leftChild;

			// El while se rompe cuando el nodo actual ya no tiene hijo izquierdo, y entonces ya encontramos al sucesor
			return nodoActual;
		}
		// Caso 2: El nodo NO tiene un hijo derecho.
		// Preguntar al parent del nodo actual si el nodo actual es su hijo izquierdo
		Node* nodoActual = node;
		Node* padreNodoActual = nodoActual->parent;
		// Si subiste hasta el padre de la ra�z (el cual es nullptr) entonces no habr� un sucesor.
		while(nodoActual->parent != nullptr)
		{
			// Si el nodo actual es igual al hijo izquierdo de su padre
			if (nodoActual == padreNodoActual->leftChild)
			{
				// ... entonces el padre es el sucesor
				return padreNodoActual;
			}
			// Si no, el nodo actual ahora apunta al padre, y se repite el proceso.
			nodoActual = padreNodoActual;
			padreNodoActual = padreNodoActual->parent;
		}

		// si te sales de este while, entonces no hay sucesor
		return nullptr;
	}

	Node* Predecesor(Node* node)
	{
		// Caso 1: El nodo s� tiene un hijo izquierdo
		if (node->leftChild != nullptr)
		{
			// Paso 1: Dar un paso a la derecha
			Node* nodoActual = node->leftChild; // este nodo auxiliar es como el "nodoActual" que usamos en otras funciones.

			// Paso 2: irte lo m�s a la derecha que se pueda desde ah�.
			while (nodoActual->rightChild != nullptr)
				nodoActual = nodoActual->rightChild;

			// El while se rompe cuando el nodo actual ya no tiene hijo derecho, y entonces ya encontramos al predecesor
			return nodoActual;
		}
		// Caso 2: El nodo NO tiene un hijo izquierdo.
		// Preguntar al parent del nodo actual si el nodo actual es su hijo derecho
		Node* nodoActual = node;
		Node* padreNodoActual = nodoActual->parent;
		// Si subiste hasta el padre de la ra�z (el cual es nullptr) entonces no habr� un predecesor.
		while (nodoActual->parent != nullptr)
		{
			// Si el nodo actual es igual al hijo izquierdo de su padre
			if (nodoActual == padreNodoActual->rightChild)
			{
				// ... entonces el padre es el predecesor
				return padreNodoActual;
			}
			// Si no, el nodo actual ahora apunta al padre, y se repite el proceso.
			nodoActual = padreNodoActual;
			padreNodoActual = padreNodoActual->parent;
		}

		// si te sales de este while, entonces no hay predecesor
		return nullptr;
	}

	void InOrderRecursivo(Node* nodoActual)
	{
		// Si el nodo actual no es nullptr ...
		if (nodoActual != nullptr)
		{
			// ... entonces mandamos a llamar esta misma funci�n pero con el hijo izquierdo del actual
			InOrderRecursivo(nodoActual->leftChild);
			// Visitamos al nodo actual (en este caso visitar significa imprimir su valor)
			cout << nodoActual->value << ", ";
			// mandamos a llamar esta misma funci�n pero con el hijo derecho del actual
			InOrderRecursivo(nodoActual->rightChild);
		}
	}

	void PreOrderRecursivo(Node* nodoActual)
	{
		// Si el nodo actual no es nullptr ...
		if (nodoActual != nullptr)
		{
			// ... entonces 
			// Visitamos al nodo actual (en este caso visitar significa imprimir su valor)
			cout << nodoActual->value << ", ";

			//mandamos a llamar esta misma funci�n pero con el hijo izquierdo del actual
			PreOrderRecursivo(nodoActual->leftChild);

			// mandamos a llamar esta misma funci�n pero con el hijo derecho del actual
			PreOrderRecursivo(nodoActual->rightChild);
		}
	}

	void PostOrderRecursivo(Node* nodoActual)
	{
		// Si el nodo actual no es nullptr ...
		if (nodoActual != nullptr)
		{
			// ... entonces mandamos a llamar esta misma funci�n pero con el hijo izquierdo del actual
			PostOrderRecursivo(nodoActual->leftChild);
			// mandamos a llamar esta misma funci�n pero con el hijo derecho del actual
			PostOrderRecursivo(nodoActual->rightChild);
			// Visitamos al nodo actual (en este caso visitar significa imprimir su valor)
			cout << nodoActual->value << ", ";
		}
	}

	/*********** NUEVO: helper recursivo para borrar subárbol en post-orden ***********/
	void BorrarSubarbolPostOrdenRecursivo(Node* nodoActual)
	{
		if (nodoActual == nullptr)
			return;

		// 1) Viaja al sub-árbol izquierdo recursivamente
		BorrarSubarbolPostOrdenRecursivo(nodoActual->leftChild);
		// 2) Viaja al sub-árbol derecho recursivamente
		BorrarSubarbolPostOrdenRecursivo(nodoActual->rightChild);
		// 3) Borra el nodo actual
		delete nodoActual;
	}
	/**********************************************************************************/


	/********************************************************/
	/*
	1) Implementar la funci�n "Search" del Binary Search Tree de manera iterativa (10 puntos).

	2) Implementar una funci�n de la clase Binary Search Tree una funci�n que haga:
		1.Viaja al sub-�rbol izquierdo de este nodo, recursivamente.
		2.Viaja al sub-�rbol derecho de este nodo, recursivamente.
		3.borra el nodo actual.
	Puede ser recursiva (20 puntos) o iterativa (30 puntos). D�nle un nombre apropiado.

	3) Implementar la funci�n Post-order del Binary Search Tree de manera iterativa. (10 puntos). 

	*/

	/********************************************************/



	// Puntero al nodo ra�z de este �rbol
	Node* root;
	// int count;

};

void DemostracionBinarySearchTree();
