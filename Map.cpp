#include "Map.h"

///////////////////////////////////////////////
/// OPERACIONES SOBRE AVL
///////////////////////////////////////////////

// Prop.: crea una hoja con determinado cliente
AVL leafAVL(Cliente c) {
    AVLNode* node = new AVLNode;
    node->height = 1;
    node->left   = NULL;
    node->right  = NULL;
    node->kv     = c;
    return node;
}

// Prop.: devuelve la altura de un AVL
int heightAVL(AVL t) {
    return t == NULL ? 0 : t->height;
}

// Prop.: hace una rotaci�n simple
AVL sJoinAVL(Cliente kv, AVL ti, AVL td) {
    AVL node      = leafAVL(kv);
    node->height  = 1 + max(heightAVL(ti), heightAVL(td));
    node->left    = ti;
    node->right   = td;
    return node;
}

/// PRECOND: ti es dos m�s profundo que td (y por lo tanto es no vacio)
// Prop.: realiza una rotaci�n a izquierda
AVL lJoinAVL(Cliente kv, AVL ti, AVL td) {
    Cliente kvi = ti->kv;
    AVL tii     = ti->left;
    AVL tid     = ti->right;
    int hii     = heightAVL(tii);
    int hid     = heightAVL(tid);
    if (hii >= hid) {
        return sJoinAVL(kvi, tii, sJoinAVL(kv, tid, td));
    }

    Cliente kvid = tid->kv;
    AVL tidi     = tid->left;
    AVL tidd     = tid->right;
    return sJoinAVL(kvid, sJoinAVL(kvi, tii, tidi), sJoinAVL(kv, tidd, td));
}

/// PRECOND: td es dos m�s profundo que ti (y por lo tanto es no vacio)
// Prop.: realiza una rotaci�n a derecha
AVL rJoinAVL(Cliente kv, AVL ti, AVL td) {
    Cliente kvd = td->kv;
    AVL tdi     = td->left;
    AVL tdd     = td->right;
    int hdi = heightAVL(tdi);
    int hdd = heightAVL(tdd);
    if (hdi <= hdd) {
        return sJoinAVL(kvd, sJoinAVL(kv, ti, tdi), tdd);
    }

    Cliente kvdi = tdi->kv;
    AVL tdii = tdi->left;
    AVL tdid = tdi->right;
    return sJoinAVL(kvdi, sJoinAVL(kv, ti, tdii), sJoinAVL(kvd, tdid, tdd));
}

/**
PRECOND:
  * ti y td son BSTs
  * las claves de ti son menores que kv
  * las claves de td son mayores que kv
  * ti y td son AVLs
  * PERO ti y td pueden tener mas altura que lo necesario!!! (pero no deben!)
     (ojo: ti dos mas que td, o td dos mas que ti, pues antes eran AVLs...)
**/
// Prop.: realiza una rotaci�n en base a las alturas
AVL joinAVL(Cliente c, AVL ti, AVL td) {
    int hi = heightAVL(ti);
    int hd = heightAVL(td);
    if (abs(hi-hd) <= 1) {
        return sJoinAVL(c, ti, td);
    } else if (hi == hd + 2) {
        return lJoinAVL(c, ti, td);
    } else if (hd == hi + 2) {
        return rJoinAVL(c, ti, td);
    }
    // nunca puede darse otro caso
    cout << "Se viola el invariante de representaci�n!" << endl;
}

/// PRECOND: el AVL no est� vac�o
// Prop.: asigna el minimo al primer parametro y devuelve "t" sin ese minimo
AVL splitMaxAVL(Cliente& c, AVL t) {
    if(t->right == NULL) {
        Cliente cliente = t->kv;
        AVL left        = t->left;
        delete t->right;
        delete t;
        c  = cliente;
        return left;
    } else {
        AVL td = splitMaxAVL(c, t->right);
        return joinAVL(t->kv, t->left, td);
    }
}
///////////////////////////////////////////////
/// INTERFAZ DE MAP Y AUXILIARES
///////////////////////////////////////////////

///Prop.: crea un Map vacio
///O(1) debido a que solo se retorna NULL
Map emptyM() {
    return NULL;
}

///Prop: chequea si un map esta vacio
///O(1) debido a que solo se hace una comparacion con NULL
bool isEmptyM(Map m){
    return m == NULL;
}

/// Prop.: devuelve un value dado una key
/// Prep: el arbol debe ser BST
///O(log n) en peor caso debido a que se realiza un recorrido logaritmico sobre un arbol BST
Cliente lookupM(Map& m, string key) {

    if (isEmptyM(m)){
        return NULL;
    }
    else if(getCuit(m->kv) == key){
         return m->kv;
    }
    else if(key > getCuit(m->kv)){
        return lookupM(m->right, key);
    }
    else if(key < getCuit(m->kv)){
        return lookupM(m->left, key);
    }
}

/// Prop.: asocia un key con un value
/// Prep: el arbol debe ser BST
/// O(log n) en peor caso debido a que se realiza un recorrido logaritmico sobre un arbol BST
void addM(Map& m, Cliente cliente) {

    if (isEmptyM(m)){
        m = leafAVL(cliente);
    }
    else if(cliente->cuit == m->kv->cuit){
        m ->kv = cliente;
    }
    else if(getCuit(cliente) > getCuit(m->kv)){
        addM(m->right, cliente);
    }
    else if(getCuit(cliente) < getCuit(m->kv)){
        addM(m->left, cliente);
    }

    m = joinAVL(m->kv, m->left, m->right);
}

/// Prop.: indica si la respuesta del lookup es v�lida
/// O(1) debido a que solo se hace una comparacion con NULL
bool isNothing(Cliente c) {
    return c == NULL;
}

/// Prop.: elimina un value dado una key
/// Prep: el arbol debe ser BST
/// O(log n) en peor caso debido a que se realiza un recorrido logaritmico sobre un arbol BST
void removeM(Map& m, string key) {
    if(m == NULL) {
        return;
    }

    if(getCuit(m->kv) == key) {
       if(m->left == NULL) {
         AVL temp = m;
         m = m->right;
         delete temp;
         return;
       } else {
          m->left = splitMaxAVL(m->kv, m->left);
       }
    } else if(getCuit(m->kv) > key) {
        removeM(m->left,key);
    } else if(getCuit(m->kv) < key) {
        removeM(m->right, key);
    }

    m = joinAVL(m->kv, m->left, m->right);
}
///Prop : devuelve la lista de claves de un map recorriendolo completamente
///O(n) + O(n) debido a que recorro izquierda y luego derecha para poder recorrer el arbol
///Por otro lado, add es O(1) amortizado, cuando necesita agrandar el array es 0(n).
///Al agrandar cada vez mas el array, me alejo mas de tener que hacerlo y como agregar el elemento es O(1)
///son mas los casos que es O(1) que O(n)

void domMAux(Map& m, ArrayList xs){
    if (!isEmptyM(m)){
        add(xs, m->kv->cuit);
        domMAux(m->left, xs);
        domMAux(m->right, xs);
    }
}
/// Prop.: devuelve la lista de claves de un Map
///O(n) debido a que en el peor caso domMAux me cuesta O(n).
ArrayList domM(Map& m) {
    ArrayList listaClaves = crearArrayList();
    domMAux(m, listaClaves);
    return listaClaves;
}

/// Prop.: libera la memoria de un Map
///O(n) + O(n) debido a que recorro izquierda y luego derecha para poder borrar el arbol
void destroyM(Map& m) {
     if (!isEmptyM(m)){
        destroyM(m->left);
        destroyM(m->right);
        delete m;
        m= NULL;
    }
}
///////////////////////////////////////////////
/// PRINT DEL MAP (para ver AVL como usuario)
/// NOTAR QUE ROMPE ENCAPSULAMIENTO
/// PERO AYUDA A VER EL ARBOL HASTA TENER
/// BIEN LA IMPLEMENTACION
///////////////////////////////////////////////

void emptySpace(int i) {
    for(; i > 0; i--) {
        cout << "-";
    }
}

void printMapAux(Map m, int i) {
    if(m == NULL) {
        emptySpace(i);
        cout << "NULL";
        return;
    }

    emptySpace(i);
    cout << "ROOT ";
    cout << getCuit(m->kv) << endl;

    emptySpace(i);
    printMapAux(m->left, i+1);
    cout << endl;

    emptySpace(i);
    printMapAux(m->right, i+1);
    cout << endl;
}

void printMap(Map m) {
     printMapAux(m, 0);
}
