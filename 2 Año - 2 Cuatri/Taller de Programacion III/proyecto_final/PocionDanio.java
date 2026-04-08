public class PocionDanio extends Item {

    private static final int DANIO = 7;

    public PocionDanio() {
        super("Poción de Danio", "Inflige 7 puntos de danio al enemigo");
    }

    @Override
    public void usar(Heroe usuario, Personaje objetivo) {
        System.out.println(usuario.getNombre() + " lanza " + nombre + " contra " + objetivo.getNombre() + "!");
        objetivo.recibirDanio(DANIO);
    }
}
