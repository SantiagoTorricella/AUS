public class Paladin extends Heroe {

    private static final int COSTO_MANA_CURACION = 3;
    private static final int CURACION_DIVINA = 6;

    public Paladin() {
        super("Paladin", 10, 4, 3, 3, 6);
    }

    @Override
    protected int calcularDanio() {
        return getAtaque();
    }
    
    @Override
    protected boolean habilidadEspecial(Personaje p) {
        // Curacion Divina: se cura a si mismo
        if (tieneMana(COSTO_MANA_CURACION)) {
            System.out.println(getNombre() + " usa Curacion Divina!");
            curar(CURACION_DIVINA);
            gastarMana(COSTO_MANA_CURACION);
            return true;
        } else {
            System.out.println(getNombre() + " no tiene suficiente mana para usar Curacion Divina!");
            return false;
        }
    }
}
