#include <iostream>
#include "funciones.h"

using namespace std;

/**
*   TALLER 02 - COMPUTACIÓN PARALELA Y DISTRIBUIDA
*
 */

int main()
{
	bool ready;
    leerdatos(ready);
	if(ready) {
		arreglo_final();
		suavizamiento_exp();
		regresion_lineal(); 
	}
    return 0;
}