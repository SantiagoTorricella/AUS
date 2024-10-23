#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    char * nombreLegislador;
    struct nodo * sgte ;
} Legislador;

void insertar (char[10], Legislador **i);
void listar (Legislador *i );
void eliminar(char[10], Legislador **i);
int miembro(char[10], Legislador *i);
void cargarVotacion(Legislador **i, Legislador **j);



int main()
{
    Legislador *chicos_buenos, *chicos_malos;
    chicos_buenos = NULL;
    chicos_malos = NULL;

    

    return 0;
}

void listar ( Legislador * i ) 
{
    if ( i != NULL ) 
    {
        printf ( " elemento := %s \n " , i->nombreLegislador ) ;
        listar(i->sgte);
    }
}

void insertar ( char nombre[10] , Legislador ** i ) 
{
    if (*i == NULL ) 
    {
        printf ( " Insertando %s en la Legislador \n " , nombre ) ;
        *i = ( Legislador *) malloc ( sizeof ( Legislador ) ) ; 
        (*i)->nombreLegislador = malloc(sizeof(char) * (strlen(nombre) + 1 ) );
        strcpy((*i)->nombreLegislador, nombre);
        *(*i)->nombreLegislador;
    } 
    else 
    {
        if (strcmp((* i ) -> nombreLegislador,nombre) > 0 )   // cuando va al inicio 
        {                      
            printf ( " Insertando %s en la Legislador \n " , nombre ) ;
            Legislador * nuevo = ( Legislador *) malloc ( sizeof ( Legislador ) ) ;
            nuevo->nombreLegislador = malloc(sizeof(char) * (strlen(nombre) + 1 ));
            strcpy(nuevo->nombreLegislador,nombre);
            nuevo->sgte = * i ;
            *i = nuevo;
        } 
        else if (strcmp((* i ) -> nombreLegislador,nombre) < 0 && 
                 (* i )->sgte != NULL && 
                 strcmp((* i)->sgte-> nombreLegislador, nombre ) > 0) //cuando esta entre dos
            {  
                printf ( " Insertando %s en la Legislador \n " , nombre ) ;
                Legislador * nuevo = ( Legislador *) malloc ( sizeof ( Legislador ) ) ;
                nuevo->nombreLegislador = malloc(sizeof(char) * (strlen(nombre) + 1 ));
                strcpy(nuevo->nombreLegislador,nombre);
                nuevo->sgte = (* i ) -> sgte ;
                (* i )->sgte = nuevo ;
            } 
            else if ((* i ) -> nombreLegislador == nombre )
            printf ( " Ya existe el elemento %s en la Legislador \n " , nombre ) ;
    else
            insertar (nombre , &(* i ) -> sgte ) ;
    }
 }

void eliminar ( char nombre[10] , Legislador ** i ) {
    if (* i == NULL )
        printf ( " No existe el elemento a eliminar \n " ) ;
    else {
        if (strcmp((* i )->nombreLegislador, nombre) == 0) { // elimino al primero
        printf ( " Elimino a %s \n " , nombre ) ;
        Legislador * aux = (* i ) ;
        (* i ) = (* i ) -> sgte ;
        free ( aux ) ;
    } else if (strcmp((* i )->nombreLegislador,nombre) < 0 && (* i ) -> sgte != NULL &&
                    strcmp((* i )-> sgte-> nombreLegislador,nombre) == 0) { // elimino al siguiente
            printf ( " Elimino a %s \n " , nombre ) ;
            Legislador * aux = (* i )->sgte ;
            (* i )->sgte = (* i )->sgte->sgte ;
            free( aux ) ;
    }
    else
            eliminar (nombre , &(* i ) -> sgte ) ;
    }
 }

int miembro (char nombre[10], Legislador *i)
{

    while(i != NULL)
    {
        if(strcmp(i->nombreLegislador,nombre) == 0) return 1;
        i = i->sgte;
    }

    return 0;
}

void cargaVotacion(Legislador **chicosBuenos, Legislador *chicosMalos)
{

}