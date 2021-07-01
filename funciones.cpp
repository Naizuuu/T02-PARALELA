#include "funciones.h"

/* 
    Se adjunta un archivo en texto plano, en formato CSV. El archivo tiene la siguiente estructura:

    ● Los datos están escapados usando comillas dobles.
    ● El separador de los campos es el carácter ‘;’ (punto y coma).
    ● La primera columna (“created”) corresponde a la fecha de una compra.
    ● La segunda columna (“sku”) indica un identificador de producto.
    ● La tercera columna (“quantity”) corresponde a la cantidad adquirida.
    ● La cuarta columna (“amount”) indica el valor de los productos adquiridos (en CLP).
    ● La quinta columna (“name”) indica el nombre del producto y sirve de descripción.

    Estos datos corresponde a la información de compras de una empresa de retail, se solicita a su
    grupo de trabajo desarrollar un programa que permita determinar una forma de predecir las
    ventas de un día:
    1. La idea es que puedan probar diferentes aproximaciones estadísticas en su programa y
    se muestren como resultado.
    2. Deben quedar en el código las diferentes aproximaciones.
    3. El resultado final es una ecuación.
 */


#define ARCHIVO "archivos/datos.csv"
#define MAX 300


using namespace std;

int length; // Guarda el tamaño del arreglo principal
int lengthDos; // Guarda el tamaño del arreglo DatosVentas

/* Se crean los arreglos de struct */
struct prod {
    string created;
    string sku;
    int quantity;
    int amount;
    string name;
} productos[MAX];

struct finalData {
	string fecha;
	int ventas;
} DatosVentas[MAX];

/* Funciones */
void leerdatos(bool &ready) {
    ifstream archivo(ARCHIVO);
	if(archivo.good()) {
		string linea;
		char delimitador = ';';
		int i = 0;

		getline(archivo, linea);

		while(getline(archivo, linea)) { // Entran así -> "created";"sku";"quantity";"[...]"
			stringstream stream(linea);  // Convertir cadena a stream
			string creado, identificador, cantidad, monto, nombre; // Variables para los datos del .csv

			// Obtener los datos del .csv
			getline(stream, creado, delimitador);
			getline(stream, identificador, delimitador);
			getline(stream, cantidad, delimitador);
			getline(stream, monto, delimitador);
			getline(stream, nombre, delimitador);

			// Eliminar las comillas
			creado.erase(remove(creado.begin(), creado.end(), '\"'), creado.end());
			identificador.erase(remove(identificador.begin(), identificador.end(), '\"'), identificador.end());
			cantidad.erase(remove(cantidad.begin(), cantidad.end(), '\"'), cantidad.end());
			monto.erase(remove(monto.begin(), monto.end(), '\"'), monto.end());
			nombre.erase(remove(nombre.begin(), nombre.end(), '\"'), nombre.end());

			// Ingresar datos en matriz
			productos[i].created = creado.substr(0,10);
			productos[i].sku = identificador;
			istringstream(cantidad) >> productos[i].quantity;
			istringstream(monto) >> productos[i].amount;
			productos[i].name = nombre;

			// DEBUG
			/* cout << "====[" << i << "]====" << endl;
			cout << "Fecha: " << productos[i].created << endl;
			cout << "SKU: " << productos[i].sku << endl;
			cout << "Cantidad: " << productos[i].quantity << endl;
			cout << "Monto: " << productos[i].amount << endl;
			cout << "Nombre: " << productos[i].name << endl;
			cout << "=======================" << endl << endl; */
			i++;
		}
		length = i; // Obtener la cantidad de datos, ya que "i" corresponde al tamaño
		ready = true;
		archivo.close();
	} else {
		cout << "=== Integrantes ===" << endl << endl;
		cout << "Axel Jerez" << endl;
		cout << "Sebastian Munoz" << endl;
		ready = false;
	}
}

void arreglo_final() {
	string fechaAux = productos[0].created;
	int contVentas = 0; // Inicializador de contador de ventas por dia
	int contAux = 0; // Contador que ayudará a cambiar la posición del arreglo para el cambio de fecha.
	int j = 0;
	DatosVentas[0].ventas = 0;
	DatosVentas[0].fecha = fechaAux;

	for (int i = 0; i < length; i++) { 
		if(fechaAux == productos[i].created) { 
			contVentas++; 
			contAux++;
		} else {
			DatosVentas[j].fecha = fechaAux; 
			fechaAux = productos[i].created;
			i = contAux-1;
			DatosVentas[j].ventas = contVentas;
			contVentas = 0;
			j++;
		}
	}
	/* ---------------------    DEBUG    ------------------------ */
	/* for(int x = 0; x < j; x++) {
		cout << "====[Dia " << x + 1 << "]====" << endl;
		cout << "Fecha: " << DatosVentas[x].fecha << endl;
		cout << "Ventas por fecha: " << DatosVentas[x].ventas << endl << endl;
	} */
	lengthDos = j; // Obtener la cantidad de datos, ya que "j" corresponde al tamaño
}

/* Suavizamiento exponencial de ventas*/
void suavizamiento_exp() {
	int pronInicial = 9; // Se ingresa un pronostico inicial del primer dia
	double pronFinal;
	float alpha = 0.5; // Factor de suavización
	for(int i = 0; i < lengthDos; i++) {
		if(i == 0) {
			pronFinal = pronInicial;
		} else {
			pronFinal = (alpha * DatosVentas[i-1].ventas) + ((1 - alpha) * pronFinal);
		}
	}
	cout << "Suavizamiento exponencial de ventas: " << endl;
	cout << "Pronostico = (" << alpha << " * {Demanda real dia anterior} + (1 - " << alpha << ") * {Pronostico del dia anterior})" << endl;
    cout << "Pronostico = (" << alpha << " * " << DatosVentas[lengthDos-1].ventas << " + (1 - " << alpha << ") * " << pronFinal << endl;
}

void regresion_lineal()
{
	int X[lengthDos];
	int sumaX = 0, sumaY = 0, sumaXX = 0, sumaXY = 0, sumaX2 = 0;
	int n = lengthDos + 1;
	double m, b, m1, m2, b1;
    /* double pronostico; */    // Variable pronostico
	for(int i = 0; i < lengthDos; i++) {
		X[i] = i + 1;
		sumaX = sumaX + X[i];
		sumaY = sumaY + DatosVentas[i].ventas;
		sumaXX = sumaXX + (X[i] * X[i]);
		sumaXY = sumaXY + (X[i] * DatosVentas[i].ventas);
	}
	sumaX2 = sumaX * sumaX;
	m1 = ((n-1) * sumaXY) - (sumaX * sumaY);
	m2 = ((n-1) * sumaXX) - sumaX2;	
	m = m1 / m2;
	b1 = sumaY - (m * sumaX);
	b = b1 / (n-1);
	/* pronostico = m * n + b; */   // Calcular pronostico
	cout << endl;
	cout << "Regresion lineal simple: " << endl;
	cout << "Pronostico = " << b << " + " << m << " * {Dia a predecir}" << endl;
}