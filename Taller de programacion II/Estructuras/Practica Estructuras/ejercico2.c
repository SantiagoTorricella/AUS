#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

typedef struct
{
int n;  //Orden del polinomio
int *coeficiente; 
} Polinomio;

Polinomio * creaPolinomio(int);
void setCoef(int , int , Polinomio *);
void mostrarPolinomio(Polinomio *);
int getCoef(int, Polinomio *);

int orden = 0;

int main()
{

    srand(time(NULL)); // Inicializao srand

    Polinomio *p;
    

    //Ingreso el coeficiente maximo del polinomio
    printf("Ingrese orden del polinomio \n");
    scanf("%d", &orden);

    p = creaPolinomio(orden);
    mostrarPolinomio(p);
    printf("\n");
    setCoef(2,3,p);
    mostrarPolinomio(p);;
    printf("\n");
    printf("%d", getCoef(1,p));
    printf("\n");
    

    return 0;
}

//  Imprime el polinomio en pantalla
void mostrarPolinomio(Polinomio *p)
{

    for(int i=0 ; i <= orden ; i++)
        {
            printf("%d\t",p->coeficiente[i]); 
        }

}

//  Creo un polinomio y lo carga
Polinomio * creaPolinomio(int orden)
{
    Polinomio *p;
    p = (struct Polinomio *)malloc(sizeof(Polinomio)); // Reservo memoria para estructura
    p->coeficiente = (int *)malloc((orden + 1) * orden); // Reservo memoria para el puntero coeficiente

    for(int i=0 ; i <= orden ; i++)
    {
        p->coeficiente[i] = (rand() % 10) + 1 ;
    }
    
    return p;
}


//  Asigna coeficientes: n es la posiciom / c el valor / *p el polinomio
void setCoef (int n, int c, Polinomio *p)
{
    if (n > orden) return NULL; //verifica que solo acceda a posiciones validas
    p->coeficiente[n - 1] = c;
}

int getCoef(int n, Polinomio *p)
{
    return p->coeficiente[n - 1];
}