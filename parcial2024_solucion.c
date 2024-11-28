#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char nombre[50];
    int edad;
    float promedio;
} Estudiante;

void ingresarEstudiante(Estudiante *est) {
    printf("Ingrese nombre: ");
    scanf("%s", est->nombre);
    printf("Ingrese edad: ");
    scanf("%d", &est->edad);
    printf("Ingrese promedio: ");
    scanf("%f", &est->promedio);
}

void mostrarEstudiante(Estudiante est) {
    printf("Nombre: %s\n", est.nombre);
    printf("Edad: %d\n", est.edad);
    printf("Promedio: %.2f\n", est.promedio);
}

void guardarEstudiantes(Estudiante est[], int n) {
    FILE *archivo = fopen("estudiantes.dat", "wb+");
    if (archivo != NULL) {
        fwrite(est, sizeof(Estudiante), n, archivo);
        fclose(archivo);
    }
}

int cargarEstudiantes(Estudiante est[], int max) {
    FILE *archivo = fopen("estudiantes.dat", "rb");
    int i = 0;
    if (archivo != NULL) {
        while (fread(&est[i], sizeof(Estudiante), 1, archivo) == 1 && i < max) {
            i++;
        }
        fclose(archivo);
    }
    return i; // retorna la cantidad de estudiantes leídos
}
void buscarEstudiantePorNombre(const char *nombre) {
    FILE *archivo = fopen("estudiantes.dat", "rb");
    Estudiante est;
    int encontrado = 0;
    if (archivo != NULL) {
        while (fread(&est, sizeof(Estudiante), 1, archivo) == 1) {
            if (strcmp(est.nombre, nombre) == 0) {
                mostrarEstudiante(est);
                encontrado = 1;
                break;
            }
        }
        fclose(archivo);
        if (!encontrado) {
            printf("Estudiante no encontrado.\n");
        }
    }
}
void actualizarPromedio(const char *nombre, float nuevoPromedio) {
    FILE *archivo = fopen("estudiantes.dat", "rb+");
    Estudiante est;
    int encontrado = 0;
    if (archivo != NULL) {
        while (fread(&est, sizeof(Estudiante), 1, archivo) == 1) {
            if (strcmp(est.nombre, nombre) == 0) {
                est.promedio = nuevoPromedio;
                fseek(archivo, -sizeof(Estudiante), SEEK_CUR);
                fwrite(&est, sizeof(Estudiante), 1, archivo);
                encontrado = 1;
                break;
                printf("Hola mundo\naguante codeBlocks");
            }
        }
        fclose(archivo);
        if (encontrado) {
            printf("Promedio actualizado.\n");
        } else {
            printf("Estudiante no encontrado.\n");
        }
    }
}

int main(){

    Estudiante est[5];

    for (int x = 0; x < 5; x++){
        ingresarEstudiante(&(est[x]));
    }
    
    guardarEstudiantes(est, 5);
    char nombre_a_buscar[50];
    float nuevoPromedio = 0.0;
    printf("Ingrese nombre a buscar: ");
    scanf("%s", nombre_a_buscar);
    buscarEstudiantePorNombre(nombre_a_buscar);

    printf("Ingrese nombre de estudiante: ");
    scanf("%s", nombre_a_buscar);
    printf("Ingrese nuevo promedio: ");
    scanf("%f", &nuevoPromedio);

    actualizarPromedio(nombre_a_buscar, nuevoPromedio);
    buscarEstudiantePorNombre(nombre_a_buscar);
    return 0;
}