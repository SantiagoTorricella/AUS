public class PocionCuracion extends Item {

    private static final int CURACION = 4;

    public PocionCuracion() {
        super("Poción de Curación", "Restaura 4 puntos de vida");
    }

    @Override
    public void usar(Heroe usuario, Personaje objetivo) {
        usuario.curar(CURACION);
        System.out.println(usuario.getNombre() + " usa " + nombre + " y recupera " + CURACION + " PV!");
    }
}
