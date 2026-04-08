public class Troll extends Enemigo {

    public Troll() {
        super("Troll", 10, 5, 1, 2);
    }

    @Override
    protected int calcularDanio() {
        return this.ataque;
    }
}
