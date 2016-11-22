#include "Cliente.h""

/// Crear un nuevo cliente y asignarle el nombre y el cuit cuesta 0(1)
Cliente crearCliente(string cuit, string nombre) {
     Cliente nuevoCliente = new ClienteSt;
     nuevoCliente->cuit = cuit;
     nuevoCliente->nombre= nombre;

     return nuevoCliente;
}

/// Devolver un cuit solo cuesta O(1) debido a que es un simple acceso a cliente
string getCuit(Cliente c) {
    return c->cuit;
}

/// Devolver un cuit solo cuesta O(1) debido a que es un simple acceso a cliente
string getNombre(Cliente c) {
    return c->nombre;
}

/// Devolver un cuit solo cuesta O(1) debido a que solo llamo una instruccion y asigno NULL a c
void destroyCliente(Cliente& c) {
    delete c;
    c = NULL;
}

/// Devolver un cuit solo cuesta O(1) debido a que imprimir cada campo de la estructura me cuesta O(1)
void printCliente(Cliente c) {
    cout << "Cliente {" << endl;
    cout << "  cuit: " << c->cuit << endl;
    cout << "  nombre: " << c->nombre << endl;
    cout << "}" << endl;
}

