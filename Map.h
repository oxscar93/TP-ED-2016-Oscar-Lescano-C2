#include <iostream>
#include <stdlib.h>
#include "Cliente.h"
#include "ArrayList.h"

using namespace std;

///INV REP:
/// height representa la altura del arbol, es 0 para un arbol vacio y mayor a 0 si tiene elementos
/// un cliente aparece solo una vez en el map

struct AVLNode {
    int height;
    AVLNode* left;
    AVLNode* right;
    Cliente kv;
};

typedef AVLNode* AVL;

typedef AVL Map;

/// Prop.: crea un Map vacio
///O(1)
Map emptyM();

/// Prop.: asocia un cuit con un cliente
///O(log n)
void addM(Map& m, Cliente c);

/// Prop.: devuelve un cliente dado un cuit
///O(log n)
Cliente lookupM(Map& m, string cuit);

/// Prop.: indica si la respuesta del lookup es válida
///O(1)
bool isNothing(Cliente c);

/// Prop.: elimina un cliente dado un cuit
///O(log n)
void removeM(Map& m, string cuit);

/// Prop.: devuelve la lista de claves de un Map
///O(n)
ArrayList domM(Map& m);

/// Prop.: imprime un Map
///O(n)
void printMap(Map m);

/// Prop.: libera la memoria de un Map
///O(n)
void destroyM(Map& m);
