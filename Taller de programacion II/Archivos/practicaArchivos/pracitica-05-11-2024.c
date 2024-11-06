#include <stdio.h>

int main()
{
/*
    ========= EJERCICIO 1 =========
    FILE *file;

    file = fopen("saludo.txt","a");

    fputs("\nHola Mundo!",file);

 */

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
    
    return 0;
}