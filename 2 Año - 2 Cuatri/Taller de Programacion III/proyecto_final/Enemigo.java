import java.util.Random;

public abstract class Enemigo extends Personaje {

    private static final double PROB_ESQUIVAR = 0.30;
    private static final double PROB_ATACAR = 0.70;
    protected Random random;
    private Item itemDrop;

    public Enemigo(String nombre, int vida, int ataque, int defensa, int velocidad) {
        super(nombre, vida, ataque, defensa, velocidad);
        this.random = new Random();
        this.itemDrop = null;
    }

    public void realizarTurno(Personaje objetivo) {
        double probabilidad = random.nextDouble();

        if (probabilidad < PROB_ATACAR) {
            System.out.println(getNombre() + " decide atacar!");
            atacar(objetivo);
        } else {
            System.out.println(getNombre() + " decide defenderse!");
            defenderse();
        }
    }

    @Override
    public void recibirDanio(int danioEntrante) {
        double probabilidad = random.nextDouble();
        
        if (probabilidad < PROB_ESQUIVAR) {
            System.out.println(getNombre() + " esquivo el ataque!");
            if (defendiendo) {
                defendiendo = false;
            }
        } else {
            super.recibirDanio(danioEntrante);
        }
    }

    public Item dropearItem() {
        if (!estaVivo() && itemDrop != null) {
            System.out.println(getNombre() + " ha dropeado: " + itemDrop.toString());
            return itemDrop;
        }
        return null;
    }

    public void setItemDrop(Item item) {
        this.itemDrop = item;
    }
}
