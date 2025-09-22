#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int dato;
    struct nodo *siguiente;
} Nodo;

void apila(Nodo*,int);


int main () 
{

    Nodo *nodito;
    nodito = (struct Nodo *)malloc(sizeof(Nodo));
    nodito->dato = 5;
    nodito->siguiente = malloc(sizeof(Nodo));
    nodito->siguiente = NULL;

    apila(nodito, 5);

    return 0;
}                   


void apila(Nodo *nodo  , int dato)
{
    Nodo *noditoSiguiente; 
    noditoSiguiente = (struct Nodo *)malloc(sizeof(Nodo)); 
    noditoSiguiente->siguiente = malloc(sizeof(Nodo));
    noditoSiguiente -> dato = dato;
    nodo->siguiente = &noditoSiguiente;


}   