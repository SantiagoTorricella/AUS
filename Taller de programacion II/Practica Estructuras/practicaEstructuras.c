#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct tiempo
    {
        int anio, mes, dia, hora, minuto, segundo;

    } Tiempo;

    

int compara_tiempos(Tiempo *t1 , Tiempo *t2 );
void imprime_tiempo( Tiempo *t);

int main()
{
    


    Tiempo *t1;
    Tiempo *t2;

    t1 = (struct Tiempo *)malloc(sizeof (Tiempo));
    t2 = (struct Tiempo *)malloc(sizeof (Tiempo));

    (*t1).anio = 2022;
    (*t1).mes = 8;
    (*t1).dia = 10;
    (*t1).hora = 12;
    (*t1).minuto = 10;
    (*t1).segundo = 30;

    (*t2).anio = 2022;
    (*t2).mes = 8;
    (*t2).dia = 10;
    (*t2).hora = 12;
    (*t2).minuto = 10;
    (*t2).segundo = 30;

    


    printf("%d \n",compara_tiempos(t1,t2));

    imprime_tiempo(t1);
    imprime_tiempo(t2);


    return 0;
}

int compara_tiempos(Tiempo *t1, Tiempo *t2)
{
    if( (*t1).anio < (*t2).anio)    return 1;
    if( (*t1).anio > (*t2).anio)    return -1;

    if( (*t1).dia < (*t2).dia)    return 1;
    if( (*t1).dia > (*t2).dia)    return -1;

    if( (*t1).hora < (*t2).hora)    return 1;
    if( (*t1).hora > (*t2).hora)    return -1;


    return 0;

}

void imprime_tiempo(Tiempo *t){

    printf("El horario es : %d/%d/%d %d:%d:%d \n",(*t).dia,(*t).mes,(*t).anio,(*t).hora,(*t).minuto,(*t).segundo);

}