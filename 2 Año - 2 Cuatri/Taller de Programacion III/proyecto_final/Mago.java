public class Mago extends Heroe {

    private static final int COSTO_MANA_FIREBALL = 4;
    private static final int DANIO_FIREBALL = 10;

    public Mago() {
        super("Mago", 7, 4, 3, 3, 10);
    }

    @Override
    protected int calcularDanio() {
        return getAtaque();
    }
    
    @Override
    protected boolean habilidadEspecial(Personaje p) {
        // Fireball: causa danio magico fijo
        if (tieneMana(COSTO_MANA_FIREBALL)) {
            System.out.println(getNombre() + " lanza Fireball!");
            p.recibirDanio(DANIO_FIREBALL);
            gastarMana(COSTO_MANA_FIREBALL);
            return true;
        } else {
            System.out.println(getNombre() + " no tiene suficiente mana para usar Fireball!");
            return false;
        }
    }
}
