package ejercicio1claseDiamand;

public class Pelicula implements Ordenable {
    
    private String nombre;
    private String genero;
    private int anio;


    public Pelicula(String nombre, String genero,
    int anio){
        this.nombre = nombre;
        this.genero = genero;
        this.anio = anio;
    }

    public String getNombre(){
        return this.nombre;
    }

    public String getGenero(){
        return this.genero;
    }

    public int getAnio(){
        return this.anio;
    }

}
