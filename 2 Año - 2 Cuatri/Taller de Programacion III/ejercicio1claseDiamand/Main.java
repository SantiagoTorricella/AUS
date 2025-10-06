package ejercicio1claseDiamand;

public class Main {
    public static void main(String[] args) {
        
        Pelicula pelicula1 = new Pelicula("Rocky", "Epica", 2000);
        Pelicula pelicula2 = new Pelicula("Rapido Y Furioso", "Accion", 2005);
        Pelicula pelicula3 = new Pelicula("El Rey Leon", "Ninios", 1996);
        Pelicula pelicula4 = new Pelicula("El senior de los anillos", "Fantasia", 2003);

        Libro libro1 = new Libro("Harry Potter", "askds", 1976);
        Libro libro2 = new Libro("Harry Potter Y Azvaban", "askds", 1950);
        Libro libro3 = new Libro("Harry Potter SAPE", "askds", 2000);

        Pelicula[] peliculas = {pelicula1,pelicula2,pelicula3,pelicula4};
        Libro[] libros = {libro1,libro2,libro3};

        Ordenador ordenador = new Ordenador();
        
        // Primero vemos sin ordenar
        System.out.print("====== PELICULAS ======\n");
        for (int i = 0; i < peliculas.length ; i++){
            System.out.print(peliculas[i].getNombre() + " ");
            System.out.print(peliculas[i].getGenero() + " ");
            System.out.print(peliculas[i].getAnio() + "\n");
        }
        System.out.print("====== LIBROS ======\n");
        for (int i = 0; i < libros.length ; i++){
            System.out.print(libros[i].getNombre() + " ");
            System.out.print(libros[i].getIsbn() + " ");
            System.out.print(libros[i].getAnio() + "\n");
        }

        ordenador.ordenarPorAnio(peliculas);
        ordenador.ordenarPorAnio(libros);

        System.out.print("==== PELICULAS ORDENADAS ======\n");
         for (int i = 0; i < peliculas.length ; i++){
            System.out.print(peliculas[i].getNombre() + " ");
            System.out.print(peliculas[i].getGenero() + " ");
            System.out.print(peliculas[i].getAnio() + "\n");
        }
        System.out.print("==== LIBROS ORDENADOS ======\n");
        for (int i = 0; i < libros.length ; i++){
            System.out.print(libros[i].getNombre() + " ");
            System.out.print(libros[i].getIsbn() + " "); 
            System.out.print(libros[i].getAnio() + "\n");
        }
        

    }
    
}
