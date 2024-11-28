#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
=========================
    Inciso: El problema que estoy teniendo es que no se 
    pasan bien los datos a estudiantes.dat, le di varias vueltas
    pero no entiendo pq se corrompen los datos cuando los paso
    Perdona pablo que entregue sin terminar pero estoy en guardi
    y me van a matar si no hago todo lo que me pidieron en el laburo
    jajajajajaj. muchas gracias
=========================
 */

typedef struct Estudiantes {
    char *nombreEstudiante;
    int edad;
    float promedio;
} estudiante;


void ingresarEstudiante(estudiante *pEstudiante);
void mostrarEstudiante(estudiante estudiante);
void guardarEstudiantes(estudiante est[], int n);
void liberarEstudiantes(estudiante est[], int n);

int main() {
    int n = 3;  
    estudiante estudiantes[n];  

    
    for (int i = 0; i < n; i++) {
        estudiantes[i].nombreEstudiante = (char *)malloc(50 * sizeof(char));
    }

    
    for (int i = 0; i < n; i++) {
        printf("\nEstudiante %d:\n", i + 1);
        ingresarEstudiante(&estudiantes[i]);
    }

   
    for (int i = 0; i < n; i++) {
        printf("\nMostrando datos del Estudiante %d:\n", i + 1);
        mostrarEstudiante(estudiantes[i]);
    }

    
    guardarEstudiantes(estudiantes, n);

    
    liberarEstudiantes(estudiantes, n);

    return 0;
}


void ingresarEstudiante(estudiante *pEstudiante) {
   
    printf("Ingrese el nombre del estudiante: \n");
    scanf("%s", pEstudiante->nombreEstudiante);  

    printf("Ingrese la edad del estudiante: \n");
    scanf("%d", &pEstudiante->edad);

    printf("Ingrese el promedio del estudiante: \n");
    scanf("%f", &pEstudiante->promedio);
}


void mostrarEstudiante(estudiante estudiante) {

    printf("\nDetalles del estudiante:\n");
   
    printf("Nombre: %s\n", estudiante.nombreEstudiante);
   
    printf("Edad: %d\n", estudiante.edad);
    
    printf("Promedio: %.2f\n", estudiante.promedio);
}


void guardarEstudiantes(estudiante est[], int n) {
    
    FILE *f = fopen("estudiantes.dat", "wb");  

    if (f == NULL) printf("error al abrir archivo");

    for (int i = 0; i < n; i++) {

        int nameLength = strlen(est[i].nombreEstudiante) + 1; 
              
        fwrite(est[i].nombreEstudiante, sizeof(char), nameLength, f);  
        
        fwrite(&est[i].edad,sizeof(int), 1, f);              
        
        fwrite(&est[i].promedio,sizeof(float), 1, f);       
    }

    fclose(f);
    printf("\nEstudiantes guardados en estudiantes.dat \n");
}

void buscarEstudiantePorNombre(const char *nombreBuscado) {
   
    FILE *f = fopen("estudiantes.dat", "rb");  
    if (f == NULL) printf("Error al abrir el archivo");

    int found = 0;  // una flag para ver si encontre el estudiante

    printf("\nBuscando estudiante con nombre: %s\n", nombreBuscado);

    while (1) {
        int nameLength;
        
        if (fread(&nameLength, sizeof(int), 1, f) != 1) {
            break;  // Llegue al EOF
        }

        char *nombre = (char *)malloc(nameLength * sizeof(char)); // Aca guardo la memoria para el nombre buscado
    
        fread(nombre, sizeof(char), nameLength, f);

        int edad;
        float promedio;
        fread(&edad, sizeof(int), 1, f);
        fread(&promedio, sizeof(float), 1, f);

        // Comparo el nombre si lo encontre
        if (strcmp(nombre, nombreBuscado) == 0) {
            printf("\nEstudiante encontrado:\n");
            printf("Nombre: %s\n", nombre);
            printf("Edad: %d\n", edad);
            printf("Promedio: %.2f\n", promedio);
            found = 1;
            free(nombre);
            break;
        }

        free(nombre);
    }

    fclose(f);

    // Aviso que no aparece en mi archivo de estructura.dat
    if (!found) {
        printf("\nEstudiante con nombre '%s' no encontrado.\n", nombreBuscado);
    }
}


void actualizarPromedio(const char *nombreBuscado, float nuevoPromedio) {
    
    FILE *f = fopen("estudiantes.dat", "rb+"); 
    
    if (f == NULL) printf("Error al abrir el archivo");

    int found = 0;  

    while (1) {
        int nameLength;

        if (fread(&nameLength, sizeof(int), 1, f) != 1) {
            break;  
        }

        char *nombre = (char *)malloc(nameLength * sizeof(char));
        
        fread(nombre, sizeof(char), nameLength, f);

        int edad;
        float promedio;
        fread(&edad, sizeof(int), 1, f);
        fread(&promedio, sizeof(float), 1, f);

        // Encontre el nombre del usuario buscado
        if (strcmp(nombre, nombreBuscado) == 0) {
            found = 1;

            // Aca busco la posicion del promedio en mi archivo
            fseek(f, sizeof(estudiante), SEEK_CUR);

            // Aca actualizo el promedio en el archivo
            fwrite(&nuevoPromedio, sizeof(float), 1, f);
            printf("\nPromedio actualizado exitosamente para el estudiante '%s'.\n", nombre);

            free(nombre);
            break;
        }

        free(nombre);
    }

    fclose(f);

    if (!found) {
        printf("\nEstudiante con nombre '%s' no encontrado.\n", nombreBuscado);
    }
}



// Freerear la memoria
void liberarEstudiantes(estudiante est[], int n) {
    for (int i = 0; i < n; i++) {
        free(est[i].nombreEstudiante);
    }
}
