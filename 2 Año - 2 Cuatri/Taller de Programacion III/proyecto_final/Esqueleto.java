public class Esqueleto extends Enemigo {

    public Esqueleto() {
        super("Esqueleto", 8, 4, 2, 4);
    }

    @Override
    protected int calcularDanio() {
        return this.ataque;
    }
}
