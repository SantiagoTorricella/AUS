public class Guerrero extends Heroe {

    private static final int COSTO_MANA_RAGE = 2;
    private static final int BONUS_DANIO_RAGE = 4;

    public Guerrero() {
        super("Guerrero", 10, 6, 2, 4, 4);
    }

    @Override
    protected int calcularDanio() {
        return getAtaque();
    }
    
    @Override
    protected boolean habilidadEspecial(Personaje p) {
        // Rage: aumenta danio en este ataque
        if (tieneMana(COSTO_MANA_RAGE)) {
            int danioConRage = getAtaque() + BONUS_DANIO_RAGE;
            System.out.println(getNombre() + " usa Rage! Ataque potenciado!");
            p.recibirDanio(danioConRage);
            gastarMana(COSTO_MANA_RAGE);
            return true;
        } else {
            System.out.println(getNombre() + " no tiene suficiente mana para usar Rage!");
            return false;
        }
    }
}
