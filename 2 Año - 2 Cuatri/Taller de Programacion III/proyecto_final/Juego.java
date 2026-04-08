import java.util.Scanner;

public class Juego {
    
    private Scanner scanner;
    private Heroe heroeSeleccionado;
    private LoggerPartida logger;
    private Thread hiloLogger;
    
    public Juego() {
        this.scanner = new Scanner(System.in);
    }
    
    public void iniciar() {
        mostrarBienvenida();
        seleccionarHeroe();
        
        // Iniciar el logger en un hilo separado
        logger = new LoggerPartida(heroeSeleccionado.getNombre());
        hiloLogger = new Thread(logger);
        hiloLogger.start();
        
        logger.log("Partida iniciada con " + heroeSeleccionado.getNombre());
        
        boolean victoria = ejecutarRun();
        
        // Finalizar el logger
        logger.finalizarPartida(victoria);
        
        try {
            // Esperar sin timeout para garantizar que el log se escriba
            hiloLogger.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        
        mostrarResultadoFinal(victoria);
        scanner.close();
    }
    
    private void mostrarBienvenida() {
        System.out.println("╔══════════════════════════════════════════════════╗");
        System.out.println("║                                                  ║");
        System.out.println("║              DUNGEON CRAWLER RPG                 ║");
        System.out.println("║                                                  ║");
        System.out.println("╚══════════════════════════════════════════════════╝");
        System.out.println();
        System.out.println("Bienvenido, aventurero...");
        System.out.println("Deberas enfrentar 3 enemigos y un BOSS FINAL.");
        System.out.println("Buena suerte!\n");
    }
    
    private void seleccionarHeroe() {
        System.out.println("=== SELECCIONA TU HEROE ===\n");
        System.out.println("1. Guerrero  - HP: 10  | ATK: 6 | DEF: 2 | VEL: 4 | MANA: 4");
        System.out.println("   Habilidad: Rage - Ataque potenciado");
        System.out.println();
        System.out.println("2. Paladin   - HP: 10 | ATK: 4 | DEF: 3 | VEL: 3 | MANA: 6");
        System.out.println("   Habilidad: Curacion Divina - Recupera HP");
        System.out.println();
        System.out.println("3. Mago      - HP: 7  | ATK: 4 | DEF: 3 | VEL: 3 | MANA: 10");
        System.out.println("   Habilidad: Bola de Fuego - Gran danio magico");
        System.out.println();
        System.out.println("4. Picaro    - HP: 7  | ATK: 6 | DEF: 1 | VEL: 6 | MANA: 4");
        System.out.println("   Habilidad: Golpe Critico - Danio x1.5");
        System.out.println();
        
        int opcion = 0;
        while (opcion < 1 || opcion > 4) {
            System.out.print("Elige tu heroe (1-4): ");
            try {
                opcion = Integer.parseInt(scanner.nextLine().trim());
            } catch (NumberFormatException e) {
                System.out.println("Por favor, ingresa un numero valido.");
            }
        }
        
        switch (opcion) {
            case 1:
                heroeSeleccionado = new Guerrero();
                break;
            case 2:
                heroeSeleccionado = new Paladin();
                break;
            case 3:
                heroeSeleccionado = new Mago();
                break;
            case 4:
                heroeSeleccionado = new Picaro();
                break;
        }
        
        System.out.println("\nHas elegido a " + heroeSeleccionado.getNombre() + "!");
        System.out.println("Preparate para la aventura...\n");
        
        try {
            Thread.sleep(1500);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
    
    private boolean ejecutarRun() {
        // Lista de enemigos a enfrentar
        Enemigo[] enemigos = {
            new Goblin(),
            new Esqueleto(),
            new Troll()
        };
        
        // Combates contra enemigos base
        for (int i = 0; i < enemigos.length; i++) {
            System.out.println("\n════════════════════════════════════════");
            System.out.println("         ENCUENTRO " + (i + 1) + " de " + enemigos.length);
            System.out.println("════════════════════════════════════════");
            
            Combate combate = new Combate(heroeSeleccionado, enemigos[i], scanner, logger);
            
            boolean gano = combate.iniciarCombate();
            
            if (!gano) {
                return false; // Derrota
            }
            
            // Mostrar estado antes del siguiente combate
            if (i < enemigos.length - 1) {
                System.out.println("\nPreparandose para el siguiente enemigo!");
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }
        
        // BOSS FINAL
        System.out.println("\n╔══════════════════════════════════════════════════╗");
        System.out.println("║                                                  ║");
        System.out.println("║              BOSS FINAL                          ║");
        System.out.println("║                                                  ║");
        System.out.println("╚══════════════════════════════════════════════════╝");
        
        logger.log("=== BOSS FINAL ===");
        
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        
        heroeSeleccionado.restaurarVida();
        Boss bossFinal = new Boss();
        Combate combateBoss = new Combate(heroeSeleccionado, bossFinal, scanner, logger);
        
        return combateBoss.iniciarCombate();
    }
    
    private void mostrarResultadoFinal(boolean victoria) {
        System.out.println("\n");
        if (victoria) {
            System.out.println("╔══════════════════════════════════════════════════╗");
            System.out.println("║                                                  ║");
            System.out.println("║                 !!!VICTORIA!!!                   ║");
            System.out.println("║                                                  ║");
            System.out.println("║         Has derrotado a Sauron y salvado         ║");
            System.out.println("║              el reino. Felicidades!              ║");
            System.out.println("║                                                  ║");
            System.out.println("╚══════════════════════════════════════════════════╝");
        } else {
            System.out.println("╔══════════════════════════════════════════════════╗");
            System.out.println("║                                                  ║");
            System.out.println("║             GAME OVER                            ║");
            System.out.println("║                                                  ║");
            System.out.println("║       Tu aventura ha llegado a su fin...         ║");
            System.out.println("║           Intentaras de nuevo?                   ║");
            System.out.println("║                                                  ║");
            System.out.println("╚══════════════════════════════════════════════════╝");
        }
    }
    
    public static void main(String[] args) {
        Juego juego = new Juego();
        juego.iniciar();
    }
}
