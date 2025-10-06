package ejercicio1claseDiamand;

public class Libro implements Ordenable {
    
    private String nombre;
    private String isbn;
    private int anio;



    public Libro(String nombre, String isbn,
    int anio){
        this.nombre = nombre;
        this.isbn = isbn;
        this.anio = anio;
    }

    public String getNombre(){
        return this.nombre;
    }

    public String getIsbn(){
        return this.isbn;
    }

    public int getAnio(){
        return this.anio;
    }

}
