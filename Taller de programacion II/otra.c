#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Estudiantes {
    char *nombreEstudiante;
    int edad;
    float promedio;
} estudiante;

// Function prototypes
void ingresarEstudiante(estudiante *pEstudiante);
void mostrarEstudiante(estudiante estudiante);
void guardarEstudiantes(estudiante est[], int n);
void liberarEstudiantes(estudiante est[], int n);

int main() {
    int n = 3;  // Number of students
    estudiante estudiantes[n];  // Array of students

    // Allocate memory for each student's name
    for (int i = 0; i < n; i++) {
        estudiantes[i].nombreEstudiante = (char *)malloc(50 * sizeof(char));
        if (estudiantes[i].nombreEstudiante == NULL) {
            perror("Error allocating memory for nombreEstudiante");
            return EXIT_FAILURE;
        }
    }

    // Input data for each student
    for (int i = 0; i < n; i++) {
        printf("\nEstudiante %d:\n", i + 1);
        ingresarEstudiante(&estudiantes[i]);
    }

    // Display data for each student
    for (int i = 0; i < n; i++) {
        printf("\nMostrando datos del Estudiante %d:\n", i + 1);
        mostrarEstudiante(estudiantes[i]);
    }

    // Save students to file
    guardarEstudiantes(estudiantes, n);

    // Free dynamically allocated memory
    liberarEstudiantes(estudiantes, n);

    return 0;
}

// Function to input data for a student
void ingresarEstudiante(estudiante *pEstudiante) {
    printf("Ingrese el nombre del estudiante: \n");
    scanf(" %[^\n]", pEstudiante->nombreEstudiante);  // Read string with spaces

    printf("Ingrese la edad del estudiante: \n");
    scanf("%d", &pEstudiante->edad);

    printf("Ingrese el promedio del estudiante: \n");
    scanf("%f", &pEstudiante->promedio);
}

// Function to display a student's data
void mostrarEstudiante(estudiante estudiante) {
    printf("\nDetalles del estudiante:\n");
    printf("Nombre: %s\n", estudiante.nombreEstudiante);
    printf("Edad: %d\n", estudiante.edad);
    printf("Promedio: %.2f\n", estudiante.promedio);
}

// Function to save an array of students to a binary file
void guardarEstudiantes(estudiante est[], int n) {
    FILE *f = fopen("estudiantes.dat", "wb");  // Open file in binary write mode
    if (f == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        // Save the length of the name (to handle variable-length strings)
        int nameLength = strlen(est[i].nombreEstudiante) + 1;  // Include null terminator
        fwrite(&nameLength, sizeof(int), 1, f);               // Write the length of the name
        fwrite(est[i].nombreEstudiante, sizeof(char), nameLength, f);  // Write the name
        fwrite(&est[i].edad, sizeof(int), 1, f);              // Write the age
        fwrite(&est[i].promedio, sizeof(float), 1, f);        // Write the average
    }

    fclose(f);
    printf("\nEstudiantes guardados exitosamente en 'estudiantes.dat'.\n");
}

// Function to free memory for all students
void liberarEstudiantes(estudiante est[], int n) {
    for (int i = 0; i < n; i++) {
        free(est[i].nombreEstudiante);
    }
}
