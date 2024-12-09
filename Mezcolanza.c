#include <stdio.h>
#include <stdlib.h>
#include <string.h>

<<<<<<< HEAD
int main() 
{

=======
typedef struct 
{
    char nombre[50];
    int edad;
    float promedio;
} Estudiante;


void ingresarEstudiante(Estudiante *est)
{
    printf("Ingrese el nombre del estudiante: \n");
    scanf("%s",est->nombre);
    printf("Ingrese la edad del estudiantes: \n");
    scanf("%d",&est->edad);
    printf("Ingrese el promedio del estudiante: \n");
    scanf("%f",&est->promedio);
}

void mostrarEstudiante(Estudiante est)
{
    printf("El nombre del estudiante es:\n%s\n", est.nombre);
    printf("La edad del estudiante es:\n %d\n", est.edad);
    printf("El promedio del estudiante es:\n %f\n", est.promedio);
}

void guardarEstudiantes(Estudiante est[],int n)
{
    FILE *f = fopen("estudiantes.dat","wb+");

    if(f != NULL)
    {
        fwrite(est, sizeof(Estudiante),n,f);
        fclose(f);
    }

}

void buscarEstudiantePorNombre(const char *nombre)
{
    FILE *f = fopen("estudiantes.dat", "rb");
    Estudiante est;
    int encontrado = 0;

    while(fread(&est,sizeof(Estudiante),1,f) == 1)
    {
        if(strcmp(est.nombre,nombre) == 0) 
        {
        mostrarEstudiante(est);
        encontrado = 1;
        break;
        }
    }
    fclose(f);
    if(encontrado == 0) printf("Estudiante no encontrado \n");
}

void actualizarPromedio(const char *nombre, float nuevoPromedio)
{
    FILE *f = fopen("estudiantes.dat", "rb+");
    Estudiante est;
    int encontrado = 0;

    while(fread(&est,sizeof(Estudiante),1,f) == 1)
    {
        if(strcmp(est.nombre,nombre) == 0)
        {
            est.promedio = nuevoPromedio;
            fseek(f,-sizeof(Estudiante),SEEK_CUR);
            fwrite(&est,sizeof(Estudiante),1,f);
            encontrado = 1;
            break;
        }
    }

    fclose(f);
    if(encontrado != 1) printf("Alumno no encontrado \n");


} 

int main() 
{

Estudiante est[5];

for(int x = 0 ; x < 2 ; x++)
{
    ingresarEstudiante(&(est[x]));
    mostrarEstudiante(est[x]);
}

guardarEstudiantes(est,2);
    
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
>>>>>>> 1c30cfbcc967854049688e8ed4f93a094d35c2ff
}