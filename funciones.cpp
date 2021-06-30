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
#define MAX 35


using namespace std;

int length;

struct prod {
    string created;
    string sku;
    int quantity;
    int amount;
    string name;
};

struct finalData {
	string fecha;
	int ventas;
};

/* Se crean los arreglos de struct */
struct prod productos[MAX];
struct finalData DatosVentas[MAX];

/* Funciones */
void leerdatos() {
    ifstream archivo(ARCHIVO);
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
	length = i; // Obtener la cantidad de datos
    archivo.close();
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
			contVentas++; // Contador de ventas del día
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
	for(int x = 0; x < j; x++) {
		cout << "====[Dato " << x << "]====" << endl;
		cout << "Fecha: " << DatosVentas[x].fecha << endl;
		cout << "Ventas por fecha: " << DatosVentas[x].ventas << endl;
		cout << "=======================" << endl << endl;
	}
}