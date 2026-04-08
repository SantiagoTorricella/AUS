import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public abstract class Heroe extends Personaje {
    
    private int manaMax;
    protected int manaActual;
    private List<Item> inventario;

    public Heroe(String nombre, int vida, int ataque, int defensa, int velocidad, int manaMax){
        super(nombre,vida,ataque,defensa,velocidad);
        this.manaMax = manaMax;
        this.manaActual = manaMax;
        // Solo los heroes jugables van a tener un inventario
        this.inventario = new ArrayList<>();
    }

    protected abstract boolean habilidadEspecial(Personaje objetivo);

    public void recargarMana(int cantidad) {
        this.manaActual += cantidad;
        if (this.manaActual > manaMax) {
            this.manaActual = manaMax;
        }
    }

    public int getManaActual() {
        return manaActual;
    }

    public int getManaMax() {
        return manaMax;
    }

    public boolean tieneMana(int cantidad) {
        return manaActual >= cantidad;
    }

    public void gastarMana(int cantidad) {
        if (tieneMana(cantidad)) {
            manaActual -= cantidad;
        }
    }

    public void restaurarVida(){
        this.vidaActual = getVidaMax();
    }

    // INVENTARIO
    public void agregarItem(Item item) {
        if (item != null) {
            inventario.add(item);
        }
    }

    public boolean tieneItems() {
        return !inventario.isEmpty();
    }

    public List<Item> obtenerInventario() {
        return Collections.unmodifiableList(inventario);
    }

    public Item removerItem(int indice) {
        if (indice >= 0 && indice < inventario.size()) {
            return inventario.remove(indice);
        }
        return null;
    }
}
