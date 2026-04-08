public class Goblin extends Enemigo {

    private static final double PROB_ESQUIVAR_GOBLIN = 0.50;

    public Goblin() {
        super("Goblin", 6, 4, 1, 7);
    }

    @Override
    protected int calcularDanio() {
        return this.ataque;
    }

    // Override para que el Goblin tenga 50% de probabilidad de esquivar
    @Override
    public void recibirDanio(int danioEntrante) {
        double probabilidad = random.nextDouble();
        
        if (probabilidad < PROB_ESQUIVAR_GOBLIN) {
            System.out.println(getNombre() + " esquivo el ataque agilmente!");
            if (defendiendo) {
                defendiendo = false;
            }
        } else {
            // Aplicar danio directamente sin pasar por la esquiva de 
            // xq sino tiene mas chances de esquivar
            int danioActual = Math.max(0, danioEntrante - defensa);
            
            if (defendiendo) {
                danioActual = danioActual / 2;
                defendiendo = false;
            }
            
            vidaActual = Math.max(0, vidaActual - danioActual);
        }
    }
}
