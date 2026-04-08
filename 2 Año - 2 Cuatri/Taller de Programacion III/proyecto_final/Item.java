public abstract class Item {
    
    protected String nombre;
    protected String descripcion;

    public Item(String nombre, String descripcion) {
        this.nombre = nombre;
        this.descripcion = descripcion;
    }

    // Metodo abstracto que define el efecto del item
    // El usuario es quien usa el item, el objetivo es sobre quien se aplica
    public abstract void usar(Heroe usuario, Personaje objetivo);

    public String getNombre() {
        return nombre;
    }

    public String getDescripcion() {
        return descripcion;
    }

    @Override
    public String toString() {
        return nombre + " - " + descripcion;
    }
}
