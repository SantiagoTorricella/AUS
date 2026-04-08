public class Picaro extends Heroe {

    private static final int COSTO_MANA_BACKSTAB = 2;
    private static final int MULTIPLICADOR_BACKSTAB = 2;

    public Picaro() {
        super("Picaro", 7, 6, 1, 6, 4);
    }

    @Override
    protected int calcularDanio() {
        return getAtaque();
    }
    
    @Override
    protected boolean habilidadEspecial(Personaje p) {
        // Backstab: ataque critico x2
        if (tieneMana(COSTO_MANA_BACKSTAB)) {
            int danioCritico = getAtaque() * MULTIPLICADOR_BACKSTAB;
            System.out.println(getNombre() + " usa Backstab! Ataque critico!");
            p.recibirDanio(danioCritico);
            gastarMana(COSTO_MANA_BACKSTAB);
            return true;
        } else {
            System.out.println(getNombre() + " no tiene suficiente mana para usar Backstab!");
            return false;
        }
    }
}
