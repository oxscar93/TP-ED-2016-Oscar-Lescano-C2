#include <iostream>
#include "Map.h"

using namespace std;

///Prop: muestra el cliente cubriendo el caso en que cliente sea NULL, en caso de que no
///usa printCliente provisto por el TAD de cliente
void mostrarCliente(Cliente c){

    if (isNothing(c))
    {
        cout << "NULL";
        return;
    }
    printCliente(c);
}

///Prop: arma un mapa de ejemplo
Map armarMap(){
    Cliente c = crearCliente("1", "roberto");
    Cliente c1 = crearCliente("2", "roberto");
    Cliente c2 = crearCliente("3", "roberto");
    Cliente c3 = crearCliente("4", "juan");
    Cliente c4 = crearCliente("5", "juan");
    Cliente c5 = crearCliente("6", "juan2");
    Cliente c6 = crearCliente("7", "juan");
    Cliente c7 = crearCliente("8", "juan");

    Map m = emptyM();

    addM(m, c);
    addM(m, c1);
    addM(m, c2);
    addM(m, c3);
    addM(m, c4);
    addM(m, c5);
    addM(m, c6);
    addM(m, c7);
    return m;
}

///Prop: prueba la funcion crear cliente y la muestra
void testCliente(){

    Cliente c = crearCliente("2323", "roberto");
    printCliente(c);
}

///Prop: arma un mapa y lo muestra
void testArmarMap(){
    Map m = armarMap();
    printMap(m);
}

///Prop : busca un cuit en el mapa y muestra cliente
void testBuscarEnMapa(string cuit){

    Map m = armarMap();
    mostrarCliente(lookupM(m, cuit));
}


///Prop: muestra un array de todas las claves del mapa
void testDomMDeUnMapa(){

    Map m = armarMap();
    ArrayList xs = domM(m);
    imprimirArrayList(xs);
}

///Prop: borra un cliente en base al cuit dado
void testRemoveDeUnMap(string cuit){

  Map m = armarMap();
  removeM(m, cuit);
  printMap(m);
}

///Prop: elimina el mapa de la memoria
void testDestroyMap()
{
     Map m = armarMap();
     destroyM(m);
     printMap(m);
}

int main()
{
    ///Descomentar cualquiera de las siguientes funciones para probar los TADS

    ///PROBAR INTERFAZ DE CLIENTE
    ///testCliente();

    ///PROBAR INTERFAZ DE MAP

    ///testArmarMap();
    ///testBuscarEnMapa("7");
    ///testDestroyMap();
    ///testDomMDeUnMapa();
    ///testRemoveDeUnMap("4");
    return 0;
}
