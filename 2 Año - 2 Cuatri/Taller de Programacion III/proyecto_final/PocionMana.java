public class PocionMana extends Item {

    private static final int MANA_RECUPERADO = 4;

    public PocionMana() {
        super("Poción de Maná", "Restaura 4 puntos de maná");
    }

    @Override
    public void usar(Heroe usuario, Personaje objetivo) {
        usuario.recargarMana(MANA_RECUPERADO);
        System.out.println(usuario.getNombre() + " usa " + nombre + " y recupera " + MANA_RECUPERADO + " de maná!");
    }
}
