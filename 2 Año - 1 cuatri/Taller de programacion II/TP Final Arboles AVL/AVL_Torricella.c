#include <stdio.h>
#include <stdlib.h>

// Estructura de los nodos AVL
typedef struct Nodo {
    int dato;              
    int altura;            
    struct Nodo *h_izq;    
    struct Nodo *h_der;    
} Nodo;

// Funcion para crear un nuevo Nodo
Nodo* nuevoNodo(int dato) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->dato = dato;
    nodo->altura = 1; // Los nuevos nodos se inicializan con altura 1
    nodo->h_izq = NULL;
    nodo->h_der = NULL;
    return nodo;
}

// Funcion que retorna la altura de un nodo
int altura(Nodo* nodo) {
    if (nodo == NULL) return 0;
    return nodo->altura;
}

// Funcion para calcular el factor balance de un nodo
int factorBalance(Nodo* nodo) {
    if (nodo == NULL) return 0;
    return altura(nodo->h_izq) - altura(nodo->h_der);
}

// Funciona para printear un nodo
void printNodo(Nodo* nodo) {
    if (nodo) {
        printf("Dato: %d, Altura: %d, Balance: %d\n",
               nodo->dato, nodo->altura, factorBalance(nodo));
    } else {
        printf("Nodo nulo\n");
    }
}

Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->h_izq;  // Hijo izquierdo del nodo pasado como parametro
    Nodo* T = x->h_der;  // Hijo der de x, que es hijo izq de y

    // Hago la rotacion
    x->h_der = y;
    y->h_izq = T;

    // Actualizo alturas
    y->altura = 1 + (altura(y->h_izq) > altura(y->h_der) ? altura(y->h_izq) : altura(y->h_der));
    x->altura = 1 + (altura(x->h_izq) > altura(x->h_der) ? altura(x->h_izq) : altura(x->h_der));

    // devuelvo a nueva raiz
    return x;
}

Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->h_der;  // Right child of x
    Nodo* T = y->h_izq;  // Left child of y becomes right child of x

    // Perform rotation
    y->h_izq = x;
    x->h_der = T;

    // Update heights
    x->altura = 1 + (altura(x->h_izq) > altura(x->h_der) ? altura(x->h_izq) : altura(x->h_der));
    y->altura = 1 + (altura(y->h_izq) > altura(y->h_der) ? altura(y->h_izq) : altura(y->h_der));

    // Return new root
    return y;
}

