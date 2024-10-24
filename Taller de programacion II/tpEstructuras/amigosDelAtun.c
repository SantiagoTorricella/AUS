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
void liberaLista(Legislador **i);
void cargarVotacion(Legislador **i, Legislador **j);



int main()
{
    Legislador *chicos_buenos  = NULL, *chicos_malos = NULL;

    
    cargarVotacion(&chicos_buenos,&chicos_malos);

    printf("Lista de Senadores Buenos \n");
    listar(chicos_buenos);

    printf("Lista de Senadores Malos \n");
    listar(chicos_malos);

    liberaLista(&chicos_buenos);
    liberaLista(&chicos_buenos);    
    
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
        *i = ( Legislador *) malloc ( sizeof ( Legislador ) ) ; 
        (*i)->nombreLegislador = malloc(sizeof(char) * 20);
        strcpy((*i)->nombreLegislador, nombre);
    } 
    else 
    {
        if (strcmp((* i ) -> nombreLegislador,nombre) > 0 )   // cuando va al inicio 
        {                      
            Legislador * nuevo = ( Legislador *) malloc ( sizeof ( Legislador ) ) ;
            nuevo->nombreLegislador = malloc(sizeof(char) * 20);
            strcpy(nuevo->nombreLegislador,nombre);
            nuevo->sgte = * i ;
            *i = nuevo;
        } 
        else if (strcmp((* i ) -> nombreLegislador,nombre) < 0 && 
                 (* i )->sgte != NULL && 
                 strcmp((* i)->sgte-> nombreLegislador, nombre ) > 0) //cuando esta entre dos
            {  
                Legislador * nuevo = ( Legislador *) malloc ( sizeof ( Legislador ) ) ;
                nuevo->nombreLegislador = malloc(sizeof(char) * 20);
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
        
        Legislador * aux = (* i ) ;
        (* i ) = (* i ) -> sgte ;
        free ( aux ) ;
    } else if (strcmp((* i )->nombreLegislador,nombre) < 0 && (* i ) -> sgte != NULL &&
                    strcmp((* i )-> sgte-> nombreLegislador,nombre) == 0) { // elimino al siguiente
            
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

void cargarVotacion(Legislador **chicosBuenos, Legislador **chicosMalos)
{
    char tipoDeVoto = 'a';
    char nombreDelSenador[10];
    
    printf("Comienza la votacion en la SPIA \n");

    while (tipoDeVoto != 'e' && tipoDeVoto != 'E')
    {
        printf("\nVoto: ( \"E|e\" = fin)\n>"); 
        scanf(" %c",&tipoDeVoto); 
     
       switch(tipoDeVoto)
        {
        case 'f': case 'F':

            printf("Nombre:\n>");
            scanf("%s",nombreDelSenador);

            if( miembro(nombreDelSenador, *chicosMalos) == 0)  
            {
                insertar(nombreDelSenador,chicosBuenos);
            }
            else 
            {
                printf("\nEl legislador \"%s\" cambio de lista.\n", nombreDelSenador);
                eliminar( nombreDelSenador,chicosMalos);
                insertar( nombreDelSenador, chicosBuenos);
            }
            break;

        case 'd': case 'D': 

            printf("Nombre:\n>");
            scanf("%s",nombreDelSenador);

            if( miembro(nombreDelSenador, *chicosBuenos) == 0 ) 
            {
                insertar(nombreDelSenador, chicosMalos);
            }
            else                               
            {
                printf("\nEl legislador \"%s\" cambio de Lista.\n", nombreDelSenador);
                eliminar(nombreDelSenador,chicosBuenos);
                insertar(nombreDelSenador, chicosMalos);
            }

        break;

        case 'e': case 'E': 
        break;

        default:
            printf("\n Ingreasar un tipo de dato valido.\n VALIDOS: (f, d, e)\n"); 
        }
    }
}

void liberaLista(Legislador **listLeg)
{
    while (*listLeg != NULL)
    {
        Legislador *temp = *listLeg;      
        *listLeg = (*listLeg)->sgte; 
        free(temp);                       
    }
}