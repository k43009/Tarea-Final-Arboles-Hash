#include "HashSet.h"
#include <iostream>
using namespace std;

void DemostracionHashSet()
{
    cout << "\n--- DEMO HashSet (10 pts, composición) ---\n";
    HashSet<int> hs(4);

    // Inserciones
    hs.Add(39);   // lista 3 (con tu hash)
    hs.Add(252);  // lista 0
    hs.Add(40);   // colisión con 252

    // Duplicado (forma 1: no lanzar)
    bool ok = hs.TryAdd(252);
    cout << "TryAdd(252) -> " << (ok ? "insertado" : "ya existía") << "\n";

    // Duplicado (forma 2: lanzar excepción)
    try {
        hs.Add(252);
    } catch (const exception& e) {
        cout << "Add(252) lanzó: " << e.what() << "\n";
    }

    cout << "Contenido actual:\n";
    hs.Print();

    cout << "Contains(40)? " << (hs.Contains(40) ? "sí" : "no") << "\n";
    cout << "Remove(252) -> " << (hs.Remove(252) ? "ok" : "no estaba") << "\n";

    cout << "Después de remover 252:\n";
    hs.Print();

    // También funciona con strings (27 cubetas para A..Z…)
    HashSet<string> hsStr(27);
    hsStr.Add("Hola");
    hsStr.TryAdd("Hola"); // ignorado
    hsStr.Add("Mundo");
    cout << "\nHashSet<string>:\n";
    hsStr.Print();
}
