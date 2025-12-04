#include "Figura.h"

void DemostracionFiguras()
{
	FiguraNLados pentagono = FiguraNLados(5, 1);

	// Debe lanzar una excepción
	FiguraNLados figura0Lados = FiguraNLados(0, 1);
	FiguraNLados figura0DeLongitud = FiguraNLados(5, -1);


	// 	Circulo myCirculo = Circulo(5);
	// PARA MOTIVOS DE ESTA CLASE, NO USEN CONSTRUCCIONES IMPLÍCITAS
	Circulo myCirculo = 5; // Construcción IMPLÍCITA

	// No te deja construir de manera implícita, necesitas poner el nombre del constructor explícitamente.
	// Cuadrado myCuadrado = 5.0f; // requiere construcción EXPLÍCITA.

	// sí nos deja hacer esto porque el constructor recibe 2 parámetros, pero solo 1 no tiene valor por defecto.
	// entonces, este 5 de abajo se le asigna el parámetro del constructor que NO es por defecto (lado1).
	// Cuadrado myCuadradoDosParametros = 5;

	float segmentos[4] = {1, 2, 3, 4};
	int numSegmentos = 4;
	Linea myLinea = Linea(segmentos, numSegmentos);
	myLinea.CalcularPerimetro();
}
