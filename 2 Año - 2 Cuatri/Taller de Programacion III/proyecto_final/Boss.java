public class Boss extends Enemigo {
    
    private static final double PROB_ATAQUE_ESPECIAL = 0.30;
    private int ataqueEspecialDanio;
    
    public Boss() {
        super("Sauron", 25, 8, 5, 3);
        this.ataqueEspecialDanio = 12;
    }
    
    @Override
    protected int calcularDanio() {
        return ataque;
    }
    
    @Override
    public void realizarTurno(Personaje objetivo) {
        double probabilidad = random.nextDouble();
        
        if (probabilidad < PROB_ATAQUE_ESPECIAL) {
            System.out.println(getNombre() + " usa su ATAQUE ESPECIAL!");
            ataqueEspecial(objetivo);
        } else if (probabilidad < 0.85) {
            System.out.println(getNombre() + " ataca ferozmente!");
            atacar(objetivo);
        } else {
            System.out.println(getNombre() + " se prepara para defenderse!");
            defenderse();
        }
    }
    
    private void ataqueEspecial(Personaje objetivo) {
        System.out.println("¡" + getNombre() + " desata un ataque devastador!");
        objetivo.recibirDanio(ataqueEspecialDanio);
    }
}
