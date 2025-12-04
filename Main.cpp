// Incluye el código necesario
#include <iostream>
using namespace std;

#include "HashTableChaining.h"
#include "HashSet.h"

#include "CosasViejasDelMain.h"
#include "ArchivosEjemplo.h"
#include "ArchivoEjemplo2.h"
#include "TareaEjemplo.h"

#include "WebPacket.h"
#include "EjerciciosMemoriaDinamica.h"
#include "ClaseConstructoresYDestructores.h"

#include "ExplicacionIfndef.h" // ← ya trae su propio include guard

#include "ParametrosPorReferenciaComoSalidaDeFuncion.h"

#include "ExplicacionTemplates.h"
#include "DynamicArray.h"
#include "Stack.h"

#include "StackComposicion.h"
#include "Queue.h"

#include "ExplicacionStatic.h"
#include "LinkedList.h"
#include "SentinelLinkedList.h"

#include "ExplicacionDirectivasDePreprocesador.h"

#include "Perro.h"
#include "Gato.h"
#include "Humano.h"

#include "UsuarioProfesor.h"
#include "Vector2D.h"

#include "BinarySearchTree.h"
#include "Figura.h"

#define TAMANO_EJEMPLO_CUADRATICO 2

int main()
{
    DemostracionHashTableChaining();
    DemostracionFiguras();
    DemostracionBinarySearchTree();
    DemostracionSentinelLinkedList();
    DemostracionLinkedList();
    DemostracionSobrecargaDeOperadores();
    DemostracionHerenciaDeClases();
    DemostracionDirectivasDePreprocesador();

    int cuadratico[TAMANO_EJEMPLO_CUADRATICO][TAMANO_EJEMPLO_CUADRATICO];
    int contadorDePrints = 0;
    for (size_t y = 0; y < TAMANO_EJEMPLO_CUADRATICO; y++)
    {
        for (size_t x = 0; x < TAMANO_EJEMPLO_CUADRATICO; x++)
        {
            cout << "X:" << x << " Y:" << y << ", ";
            contadorDePrints++;
        }
        cout << "Contador de prints fue " << contadorDePrints
             << " después del for interno número: " << y << endl;
    }
    cout << endl;

    MainExplicacionStatic();
    MainQueues();
    MainParametrosPorReferenciaComoSalidaDeFuncion();

    DemostracionDynamicArray();

    Stack myStack = Stack(5);
    for (int i = 0; i < 6; i++) myStack.Push(i);
    myStack.PrintStack();
    myStack.Pop();

    int myArrayForTemplate[10];
    ImprimirArrayTemplate(myArrayForTemplate, 10);

    float myFloatArrayForTemplate[10];
    ImprimirArrayTemplate(myFloatArrayForTemplate, 10);

    Triangle myTriangleArrayForTemplate[10];
    ImprimirArrayTemplate(myTriangleArrayForTemplate, 10);

    char myCharArrayForTemplate[10];
    ImprimirArrayTemplate(myCharArrayForTemplate, 10);

    Triangle myTriangle;
    myTriangle.ImprimirTriangulo();

    Triangle myDefaultTriangle = Triangle();
    Triangle myNonDefaultTriangle = Triangle(5, 2);
    Triangle creadoPorFuncionEnVezDeConstructor = GenerarTriangulo(5, 2);

    Triangle* ptrTriangle = new Triangle();
    delete ptrTriangle;

    int dia = 0;
    if (dia == 0) { ImprimirEsLunes(); }

    void* myCastedVoidPtr = (void*)&creadoPorFuncionEnVezDeConstructor;
    int myCastedInt = static_cast<int>(7.77);

    cout << "hola mundo \n hola mundo 2 \n";
    cout << "Suma(1, -2) es: " << Suma(1, -2) << endl;
    cout << "Multiplicacion(2, 4) es: " << Multiplicacion(2, 4) << endl;
    cout << "Division(2, 4) es: " << Division(2, 4) << endl;

    TipoDeUsuario tipoDeUsuario = TipoDeUsuario::Alumno;
    switch (tipoDeUsuario)
    {
    case Alumno:
        cout << "switch es alumno " << endl;
        tipoDeUsuario = TipoDeUsuario::Profesor;
        break;
    case Profesor:
        cout << "switch es profe " << endl;
        break;
    case Admin:
        cout << "switch es admin " << endl;
        break;
    default:
        cout << "ERROR O WARNING: switch cayó en default." << endl;
    }

    int tamanioDelEjeX = 10, tamanioDelEjeY = 10;
    int valorDeYQueHaraContinue = 4, valorDeYQueHaraBreak = 5;

    for (int x = 0; x < tamanioDelEjeX; x++)
    {
        cout << "antes del for de Y" << endl;
        for (int y = 0; y < tamanioDelEjeY; y++)
        {
            if (y < valorDeYQueHaraContinue) continue;
            cout << "antes del break dentro del for de Y, y es: " << y << endl;
            if (y == valorDeYQueHaraBreak) { break; }
            cout << "después del break dentro del for de Y, y es: " << y << endl;
        }
        cout << "después del for de Y" << endl;
    }

    FuncionPila1();

    Rectangulo myRectangulo;
    myRectangulo.alto = 5.0f;
    cout << "el alto de myRectangulo es: " << myRectangulo.alto << endl;
    myRectangulo.ancho = 3.0f;

    Rectangulo* myRectanguloPointer = &myRectangulo;
    (*myRectanguloPointer).alto = 10.0f;
    myRectanguloPointer->alto = 10.0f;

    Rectangulo myOtherRectangulo = Rectangulo();
    cout << "el alto de myOtherRectangulo es: " << myOtherRectangulo.alto << endl;

    RectanguloClase myRectanguloClase;
    myRectanguloClase.alto = 5.0f;
    myRectanguloClase.ancho = 5.0f;
    myRectanguloClase.ObtenerArea();

    MainEjemplosMemoriaDinamica();
    MainTareaEjemplo();
    MainWebPacket();

    return 0;
}
