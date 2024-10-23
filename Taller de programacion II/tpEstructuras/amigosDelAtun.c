#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char nombreLegislador[10];
    struct nodo * sgte ;
} Legislador;

void insertar (char[10], Legislador **i);
void listar (Legislador *i );



int main()
{
    Legislador *chicos_buenos, *chicos_malos;
    chicos_buenos = NULL;
    chicos_malos = NULL;

    insertar("Jorgito",&chicos_buenos);
    insertar("Matias",&chicos_buenos);

    listar(&chicos_buenos);

    return 0;
}

void listar ( Legislador * i ) {
    if ( i != NULL ) {
        printf ( " elemento := %s \n " , i->nombreLegislador ) ;
        listar(i->sgte);
    }
}

void insertar ( char nombre[10] , Legislador ** i ) {
    if (*i == NULL ) {
        printf ( " Insertando %s en la Legislador \n " , nombre ) ;
        * i = ( Legislador *) malloc ( sizeof ( Legislador ) ) ;
        strcpy((*i)->nombreLegislador, nombre);
    } else {
        if ((* i ) -> nombreLegislador > nombre ) { // cuando va al inicio
        printf ( " Insertando %s en la Legislador \n " , nombre ) ;
        Legislador * nuevo = ( Legislador *) malloc ( sizeof ( Legislador ) ) ;
        strcpy(nuevo->nombreLegislador,nombre);
        nuevo->sgte = * i ;
        *i = nuevo;
     } else if ((* i )->nombreLegislador < nombre && (* i )->sgte != NULL && 
                    (* i)->sgte-> nombreLegislador > nombre ) { // cuando esta entre dos
            printf ( " Insertando %s en la Legislador \n " , nombre ) ;
            Legislador * nuevo = ( Legislador *) malloc ( sizeof ( Legislador ) ) ;
            strcpy(nuevo->nombreLegislador,nombre);
            nuevo->sgte = (* i ) -> sgte ;
            (* i )->sgte = nuevo ;
     } else if ((* i ) -> nombreLegislador == nombre )
            printf ( " Ya existe el elemento %s en la Legislador \n " , nombre ) ;
     else
            insertar (nombre , &(* i ) -> sgte ) ;
     }
 }


