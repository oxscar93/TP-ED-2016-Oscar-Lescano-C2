#include <iostream>

using namespace std;

///INV REP:
/// cliente tiene cuit y nombre != NULL
/// cuit contiene numeros o letras


struct ClienteSt {
    string cuit;
    string nombre;
};

typedef ClienteSt* Cliente;

/// Prop.: crea un cliente dado un cuit y un nombre
/// O(1)
Cliente crearCliente(string cuit, string nombre);

/// O(1)
/// Prop.: devuelve el cuit de un cliente
string getCuit(Cliente c);

/// O(1)
/// Prop.: devuelve el nombre de un cliente
string getNombre(Cliente c);

/// O(1)
/// Prop.: libera la memoria de un cliente
void destroyCliente(Cliente& c);

/// O(1)
/// Prop.: imprime a un cliente
void printCliente(Cliente c);


