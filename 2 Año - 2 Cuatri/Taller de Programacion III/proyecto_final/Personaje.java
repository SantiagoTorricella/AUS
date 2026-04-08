public abstract class Personaje {

    private String nombre;
    private int vidaMax;
    protected int vidaActual;
    protected int ataque;
    protected int defensa;
    protected int velocidad;
    protected boolean defendiendo = false;

    public Personaje(String nombre, int vidaMax, int ataque, int defensa, int velocidad){
        this.nombre = nombre;
        this.vidaMax = vidaMax;
        this.vidaActual = vidaMax;
        this.ataque = ataque;
        this.defensa = defensa;
        this.velocidad = velocidad; 
    }

    // El danio base va a depender de cada Personaje
    protected abstract int calcularDanio();

    public void recibirDanio(int danioEntrante){
        // para evitar posibles danios erroneos como:
        // danioEntrante = 10 | defensa = 15
        int danioActual = Math.max(0, danioEntrante -  defensa);
        
        // mitad de danio si atacan con personaje defendiendo
        if (defendiendo){
            danioActual = danioActual/2;
            // deja de estar en defensa luego de recibir ataque
            defendiendo = false;
        }

        vidaActual = Math.max(0, vidaActual - danioActual);
    }    

    public void atacar(Personaje personaje){
        int ataqueFinal;
        ataqueFinal = calcularDanio(); 
        personaje.recibirDanio(ataqueFinal);
    }

    public void defenderse(){
        defendiendo = true;
    }

    public boolean estaVivo(){
        return vidaActual > 0;
    }

    public void curar(int curacion){
        // No nos podemos pasar de la vidaMax al curarnos
        vidaActual = Math.min(vidaMax, vidaActual + curacion);
    }

    // GETTERS
    public String getNombre() {return nombre;}
    public int getVidaMax() {return vidaMax;}
    public int getVida() {return vidaActual;}
    public int getAtaque() {return ataque;}
    public int getDefensa() {return defensa;}
    public int getVelocidad() {return velocidad;}
}
