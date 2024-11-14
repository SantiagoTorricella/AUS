/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MAX_NAMES 100
// #define MAX_NAME_LENGTH 100


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

/*  
    ======== EJERCICIO 5 =======
    FILE *f;

    f = fopen("texto.txt","r");

    char miArchivo[100];
    int contadorPalabras = 0;
    
    while (fgets(miArchivo,100,f))
    {
        for(int i = 0 ; i < strlen(miArchivo); i++)
        {
            if(miArchivo[i] == ' ' || miArchivo[i] == '\n') contadorPalabras ++;
        }
    }
    
     printf("La cantidad de palabaras contadas son: %d" , contadorPalabras);
     fclose(f);
*/
/* 
    ======== EJERCICIO 7 =======
    FILE *namesFile, *sortedNames;
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    int nameCount = 0;
    
    // Open the input file
    namesFile = fopen("nombres.txt", "r");
    if (namesFile == NULL) {
        perror("Error opening file 'names.txt'");
        return EXIT_FAILURE;
    }

    // Read names from the file
    while (fgets(names[nameCount], MAX_NAME_LENGTH, namesFile) != NULL) {
        
        // Remove newline character if present
        names[nameCount][strcspn(names[nameCount], "\n")] = '\0';
        nameCount++;

        if (nameCount >= MAX_NAMES) {
            printf("Reached maximum number of names (%d).\n", MAX_NAMES);
            break;  
        }
    }

    fclose(namesFile);

    sortNames(names,nameCount);

    sortedNames = fopen("nombresArreglado.txt","w");

    if(sortedNames == NULL)
    {
        perror("Error abriendo el archivo");
        return EXIT_FAILURE;
    }

    for(int i = 0; i< nameCount ; i++)
    {
        fprintf(sortedNames,"%s \n" ,names[i] );
    }

    fclose(sortedNames);
    sortedNames =fopen("nombresArreglado.txt","r");
    char ojota[100];

    while (fgets(ojota, 100, sortedNames))
    {
        printf("%s\n", ojota);
    }
    
    fclose(sortedNames); 
*/

/*  
    FILE *document;




    return 0;
}  
 */


/* void sortNames(char names[][MAX_NAME_LENGTH], int count) {
    char temp[MAX_NAME_LENGTH];
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
} */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void replaceWordInLine(const char *line, const char *oldWord, const char *newWord, char *result) {
    char *pos, temp[MAX_LINE_LENGTH];
    int index = 0;
    int oldWordLen = strlen(oldWord);

    // Copy the original line into temp
    strcpy(temp, line);

    // Initialize result as an empty string
    result[0] = '\0';

    while ((pos = strstr(temp, oldWord)) != NULL) {
        // Copy the text before the old word
        int len = pos - temp;
        strncat(result, temp, len);
        result[len + index] = '\0';  // Null-terminate result

        // Append the new word
        strcat(result, newWord);

        // Update index and temp
        index += len + strlen(newWord);
        strcpy(temp, pos + oldWordLen);
    }

    // Append the rest of the line
    strcat(result, temp);
}

int main() {
    FILE *inputFile, *outputFile;
    char line[MAX_LINE_LENGTH];
    char modifiedLine[MAX_LINE_LENGTH];
    const char *oldWord = "Merca";
    const char *newWord = "Keta";

    // Open the input file
    inputFile = fopen("document.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening file 'document.txt'");
        return EXIT_FAILURE;
    }

    // Open the output file
    outputFile = fopen("updated_document.txt", "w");
    if (outputFile == NULL) {
        perror("Error opening file 'updated_document.txt'");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    // Process each line in the file
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        // Replace the word in the current line
        replaceWordInLine(line, oldWord, newWord, modifiedLine);

        // Write the modified line to the output file
        fprintf(outputFile, "%s", modifiedLine);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("The word '%s' has been replaced with '%s' in 'updated_document.txt'.\n", oldWord, newWord);

    return EXIT_SUCCESS;
}