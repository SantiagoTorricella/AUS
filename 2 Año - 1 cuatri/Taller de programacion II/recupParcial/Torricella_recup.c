#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[50];
    int edad;
}Alumno;

void completarAlumno(Alumno *al)
{
    printf("Ingrese el nombre del Alumno: ");
    scanf("%s",al->nombre);
    printf("\nIngrese la edad del alumno: ");
    scanf("%d",&al->edad);
}

void mostrarAlumno(Alumno  al)
{
    printf("\nNombre del alumno: %s", al.nombre);
    printf("\nEdad del alumno : %d",al.edad);
}

void inscribirAlumno(Alumno al)
{
    char eleccionMateria;
    int i = 1;
    
    printf("\nElija a que materias se inscribira el alumno, si selecciona alguna no valida, se dara por finalizada la inscripcion");
    while(i == 1)
    {
        printf("\nElija a que materias se inscribira el alumno: ");
        // Aca no se que es lo que pasa, pero el primer scanf no lo lee, solo me lee si pongo un segundo scanf
        scanf("%c",&eleccionMateria);
        scanf("%c",&eleccionMateria);
        
        if(eleccionMateria == 'a')
        {
          FILE *f = fopen("algebra.txt","a");
          fwrite(&al,sizeof(Alumno),1,f);
          fclose(f);
          printf("El usuario se ha inscripto correctamente en algebra\n");
        }

        else if(eleccionMateria == 'l')
        {
          FILE *f = fopen("logica.txt","a");
          fwrite(&al,sizeof(Alumno),1,f);
          fclose(f);
          printf("El usuario se ha inscripto correctamente en logica\n");
        }
        else if(eleccionMateria == 'i')
        {
          FILE *f = fopen("informatica.txt","a");
          fwrite(&al,sizeof(Alumno),1,f);
          fclose(f);
          printf("El usuario se ha inscripto correctamente en informatica\n");
        }
        else if(eleccionMateria == 'b')
        {
          FILE *f = fopen("algoritmos.txt","a");
          fwrite(&al,sizeof(Alumno),1,f);
          fclose(f);
          printf("El usuario se ha inscripto correctamente en algoritmos\n");
        }
        else break;
    }
}

void buscarAlumno (Alumno al, char materia)
{
    Alumno alumnoAuxiliar;
    int encontrado;

    if(materia == 'a')
    {
        FILE *f = fopen("algebra.txt","rb+");
        
        while(fread(&alumnoAuxiliar,sizeof(Alumno),1,f) == 1)
        {
            if(strcmp(alumnoAuxiliar.nombre,al.nombre) == 0)
            {
                printf("El alumno:%s esta inscripito en Algebra\n",al.nombre);
                encontrado = 1;
            }
            
        }
        fclose(f);
        if(encontrado != 1) printf("El alumno no esta inscripto en Algebra\n");

    }
    
    if(materia == 'l')
    {
        FILE *f = fopen("logica.txt","rb");
        while(fread(&alumnoAuxiliar,sizeof(Alumno),1,f) == 1)
        {
            if(strcmp(alumnoAuxiliar.nombre,al.nombre) == 0)
            {
                printf("El alumno:%s esta inscripito en Logica\n",al.nombre);
                encontrado = 1;
            }
            
        }
        fclose(f);
        if(encontrado != 1) printf("El alumno no esta inscripto en Logica\n");
    }

    if(materia == 'i')
    {
        FILE *f = fopen("informatica.txt","rb");
        while(fread(&alumnoAuxiliar,sizeof(Alumno),1,f) == 1)
        {
            if(strcmp(alumnoAuxiliar.nombre,al.nombre) == 0)
            {
                printf("El alumno:%s esta inscripito en Informatica\n",al.nombre);
                encontrado = 1;
            }
            
        }
        fclose(f);
        if(encontrado != 1) printf("El alumno no esta inscripto en Informatica\n");
    }

    if(materia == 'b')
    {
        FILE *f = fopen("algoritmos.txt","rb");
        while(fread(&alumnoAuxiliar,sizeof(Alumno),1,f) == 1)
        {
            if(strcmp(alumnoAuxiliar.nombre,al.nombre) == 0)
            {
                printf("El alumno:%s esta inscripito en Algoritmos\n",al.nombre);
                encontrado = 1;
            }
            
        }
        fclose(f);
        if(encontrado != 1) printf("El alumno no esta inscripto en Algoritmos\n");
    }
    encontrado = 0;
}




int main()
{
    Alumno alumnoPrueba;

    completarAlumno(&alumnoPrueba);
    mostrarAlumno(alumnoPrueba);
   
    inscribirAlumno(alumnoPrueba);
    
    buscarAlumno(alumnoPrueba,'a');
    buscarAlumno(alumnoPrueba,'i');
    

    return 0;
}