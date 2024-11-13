#include <stdio.h>

int main()
{
/*
    ========= EJERCICIO 1 =========
    FILE *file;

    file = fopen("saludo.txt","a");

    fputs("\nHola Mundo!",file);

*/
/* 
    ========= EJERCICO 2 ==========
    FILE *f;
    
    f = fopen("datos.txt","r");

    char miArchivo[100];

    if(f == NULL)  
    {
        printf("El archivo no se abrio bien");
    }

    while(fgets(miArchivo,100,f))
    {
        printf("%s",miArchivo);
    }

    fclose(f);
*/
/* 
    ======== EJERCICIO 3 ========
    FILE *f;

    f = fopen("datos.txt","r");
    int contador = 0;

    char miArchivo[100];

    if(f == NULL)  
    {
        printf("El archivo no se abrio bien");
    }

     while(fgets(miArchivo,100,f))
    {
        contador ++;
    }

    printf("%d", contador);

    fclose(f);
*/
/* 
    ======== EJERCICIO 4 ========
    FILE *f, *t;

    f = fopen("source.txt", "r");
    t = fopen("target.txt","w");
    char miArchivo[100];

    if(f == NULL) printf("El archivo fallo en abrirse");

    while (fgets(miArchivo, 100, f))
    {
        fprintf(t,"%s",miArchivo); 
    }
    fclose(t);
    t = fopen("target.txt","r");
    while(fgets(miArchivo,100,t))   printf("%s", miArchivo);
    fclose(f);
 */

    FILE *f;

    f = fopen("texto.txt","r");

    char miArchivo[100];

    
    while (fgets(miArchivo,100,f))
    {
        printf("hola");
    }
    
     

    return 0;
}  