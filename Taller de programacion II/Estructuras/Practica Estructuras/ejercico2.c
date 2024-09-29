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
void mostrarPolinomio(Polinomio *, int);
int getCoef(int, Polinomio *);
Polinomio * sum(Polinomio*, Polinomio *);
Polinomio * mult(Polinomio*,Polinomio *);
void destruyePolinomio(Polinomio *);

int orden = 0, ordenDos = 0;

int main()
{

    srand(time(NULL)); // Inicializao srand

    Polinomio *p , *otroP;
    

    //Ingreso el orden maximo del polinomio
    printf("Ingrese orden del polinomio \n");
    scanf("%d", &orden);
    p = creaPolinomio(orden);
    

    //Ingreso el orden maximo del polinomio
    printf("Ingrese orden del segundo polinomio \n");
    scanf("%d", &ordenDos);
    otroP = creaPolinomio(ordenDos);

    mostrarPolinomio(p, orden);
    printf("\n");
    
    return 0;
}

//  Imprime el polinomio en pantalla
void mostrarPolinomio(Polinomio *p, int orden)
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

// Retorna un coeficiente especifico de un polinomio / n es la posc / p* el polinomio
int getCoef(int n, Polinomio *p)
{
    return p->coeficiente[n - 1];
}

Polinomio * sum(Polinomio *pUno, Polinomio *pDos)
{   
    Polinomio *polinomioSuma;
    polinomioSuma = (struct Polinomio *)malloc(sizeof(Polinomio));
    polinomioSuma->coeficiente = (int *)malloc((ordenDos + 1) * ordenDos);

    for (int i = 0; i <= ordenDos; i++)
    {
        polinomioSuma->coeficiente[i] = pUno->coeficiente[i] + pDos->coeficiente[i];
    }
    
    return polinomioSuma;
}

Polinomio * mult(Polinomio *pUno, Polinomio *pDos)
{
    Polinomio *pMult;
    pMult = (struct Polinomio *)malloc(sizeof(Polinomio));
    pMult->coeficiente = (int *)malloc((ordenDos + 1)* ordenDos);

    for (int i = 0; i <= ordenDos; i++)
    {
        pMult->coeficiente[i] = pUno->coeficiente[i] * pDos->coeficiente[i];
    }
    return pMult;
}

void destruyePolinomio(Polinomio *p)
{
    free(p);
}