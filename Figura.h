#pragma once
#include<iostream>
#include<stdexcept>
#include<numeric>
#include<cmath>        // <-- para std::tan
using namespace std;

class Figura
{
public:
    virtual ~Figura() = default;              // <-- destructor virtual para evitar UB al borrar por puntero base
    virtual float CalcularArea() = 0;
    virtual float CalcularPerimetro() = 0;
};

class Circulo : public Figura
{
    float radio;

public:
    explicit Circulo(float radio)             // <-- explicit para evitar conversiones implícitas accidentales
    {
        this->radio = radio;
    }

    float CalcularArea() override
    {
        return 3.1416f * radio * radio;
    }

    float CalcularPerimetro() override
    {
        return 3.1416f * 2 * radio;
    }
};

class Cuadrado : public Figura
{
protected:
    float lado;
public:
    // Explicit es una cosa medio peculiar.
    // explicit quiere decir que no se puede hacer implícito, tienes que poner tal cual el nombre del 
    // constructor para poder instanciar un objeto de esta clase.
    explicit Cuadrado(float lado)
    {
        this->lado= lado;
    }

    // no sirve para constructores que reciben dos parámetros o más que no son por defecto.
    // aquí sí sirve porque solo lado1 no es por defecto.
    //Cuadrado(float lado1, float lado2 = 10) // recordatorio, los parámetros por defecto deben ir más a la derecha que los otros.
    //{
    //	this->lado = lado1;
    //}

    // Sin virtual explícito
    float CalcularArea() override
    {
        return lado * lado;
    }

    // Con virtual explícito
    virtual float CalcularPerimetro() override
    {
        return lado * 4;
    }
};

class Cubo : public Cuadrado
{
public:
    using Cuadrado::Cuadrado;                 // <-- heredar ctor para poder construir Cubo(lado)

    // Sin importar si en Cuadrado es virtual explícitamente, todavía se le puede hacer override.
    float CalcularArea() override
    {
        return lado * lado * 6.0f;
    }

    // Con virtual explícito
    float CalcularPerimetro() override
    {
        return lado * 12.0f;
    }
};

class FiguraNLados : public Figura
{
    int numeroDeLados;
    float tamanoLados;
public:
    FiguraNLados(int numLados, float tamLados)
    {
        // Los bloques try-throw-catch son súper comunes en cosas de web, como servidores.
        try
        {
            if (numLados < 3)
            {
                // Entonces no es una figura de N lados (3 sería al menos un triángulo)
                throw invalid_argument("Numero de lados es menor 3 en la figura de N lados. Debe ser al menos 3");
            }
            if (tamLados <= 0)
            {
                throw invalid_argument("el lado es 0 o menor, por lo que la figura de N lados no sería válida");
            }

            numeroDeLados = numLados;
            tamanoLados = tamLados;
        }
        catch(const invalid_argument& e)
        {
            cerr << e.what() << endl;
            // además de imprimir el programa, podemos hacer otras cosas para manejar ese error
            // Por ejemplo, ponerles valor por defecto
            numeroDeLados = 3;
            tamanoLados = 1;
        }
    }

    float CalcularArea() override
    {
        // Área polígono regular: A = (n * s^2) / (4 * tan(pi/n))
        return (numeroDeLados * tamanoLados* tamanoLados) / (4.0f * std::tan(3.1416f / (numeroDeLados))); // <-- std::tan
    }

    float CalcularPerimetro() override
    {
        // Área polígono regular: A = (n * s^2) / (4 * tan(pi/n))
        return numeroDeLados * tamanoLados;
    }
};

class Linea : public Figura
{
    float* segmentos; // arreglo de las medidas de cada segmento
    int numSegmentos;
public:
    Linea(float* arraySegmentos, int numeroSegmentos)
    {
        try
        {
            if (arraySegmentos == nullptr)
            {
                throw invalid_argument("array de segmentos en nullptr");
            }
            if (numeroSegmentos <= 0) // <-- usar el parámetro, no la variable miembro aún no inicializada
            {
                throw invalid_argument("numero de segmentos no puede ser 0 o menor");
            }
            numSegmentos = numeroSegmentos;
            segmentos = new float[numSegmentos];
            for (int i = 0; i < numSegmentos; i++)
            {
                segmentos[i] = arraySegmentos[i];
            }

        }
        catch (const invalid_argument& e)
        {
            cerr << e.what() << endl;
            // asignamos valores por defecto que sean seguros a nuestras vriables
            numSegmentos = 0;                 // <-- 0 en lugar de -1 para bucles seguros
            segmentos = nullptr;
        }
    }

    ~Linea() override
    {
        delete[] segmentos;                   // <-- liberar memoria
    }

    float CalcularArea() override
    {
        // Área polígono regular: A = (n * s^2) / (4 * tan(pi/n))
        return 0;
    }

    float CalcularPerimetro() override
    {
        if (segmentos == nullptr || numSegmentos <= 0) // <-- guardas
            return 0.0f;

        float total = 0;

        // no jaló, pero la idea es que el for sencillito tradicional de abajo hace lo mismo.
        // total = accumulate(segmentos[0], segmentos[numSegmentos - 1], 0.0f);

        for (int i = 0; i < numSegmentos; i++)
        {
            total += segmentos[i];
        }
        return total;
    }
};

void DemostracionFiguras();
