#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

void leerdatos(bool &ready); // Función que abre datos.csv y los guarda en una matriz.
void arreglo_final(); //Función que crea arreglo para dar paso a crear fórmulas
void regresion_lineal(); //Función que calcula formula de regresion lineal
void suavizamiento_exp(); //Funcion de suavizamiento exponencial de ventas

#endif /* FUNCIONES_H */