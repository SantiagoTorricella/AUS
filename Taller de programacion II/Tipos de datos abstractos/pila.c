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
    
    return 0;
}


void apila(struct nodo * , int dato)
{



}