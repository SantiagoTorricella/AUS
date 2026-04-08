import java.util.Scanner;
import java.util.Random;
import java.util.List;

public class Combate {
    
    private Heroe heroe;
    private Enemigo enemigo;
    private Scanner scanner;
    private LoggerPartida logger;
    private Random randomDrop;
    
    public Combate(Heroe heroe, Enemigo enemigo, Scanner scanner, LoggerPartida logger) {
        this.heroe = heroe;
        this.enemigo = enemigo;
        this.scanner = scanner;
        this.logger = logger;
        this.randomDrop = new Random();
    }
    
    public boolean iniciarCombate() {
        logger.log("=== COMBATE INICIADO: " + heroe.getNombre() + " vs " + enemigo.getNombre() + " ===");
        System.out.println("\n╔══════════════════════════════════════╗");
        System.out.println("║         ¡COMBATE INICIADO!           ║");
        System.out.println("╚══════════════════════════════════════╝");
        System.out.println(heroe.getNombre() + " VS " + enemigo.getNombre() + "\n");
        
        boolean turnoHeroe = heroe.getVelocidad() >= enemigo.getVelocidad();
        
        while (heroe.estaVivo() && enemigo.estaVivo()) {
            mostrarEstado();
            
            if (turnoHeroe) {
                ejecutarTurnoHeroe();
            } else {
                ejecutarTurnoEnemigo();
            }
            
            turnoHeroe = !turnoHeroe;
            
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        
        // Resultado del combate
        if (heroe.estaVivo()) {
            System.out.println("\n¡" + heroe.getNombre() + " ha derrotado a " + enemigo.getNombre() + "!");
            logger.log(heroe.getNombre() + " derroto a " + enemigo.getNombre());
            
            // Drop aleatorio al derrotar enemigo
            Item drop = obtenerDropAleatorio();
            heroe.agregarItem(drop);
            System.out.println("¡Has obtenido: " + drop.getNombre() + "!");
            logger.log("Item obtenido: " + drop.getNombre());
            
            return true;
        } else {
            System.out.println("\n" + heroe.getNombre() + " ha sido derrotado por " + enemigo.getNombre() + "...");
            logger.log(heroe.getNombre() + " fue derrotado por " + enemigo.getNombre());
            return false;
        }
    }
    
    private void mostrarEstado() {
        System.out.println("\n--- Estado del Combate ---");
        System.out.println(heroe.getNombre() + " | HP: " + heroe.getVida() + "/" + heroe.getVidaMax() + 
                          " | Mana: " + heroe.getManaActual() + "/" + heroe.getManaMax());
        System.out.println(enemigo.getNombre() + " | HP: " + enemigo.getVida() + "/" + enemigo.getVidaMax());
        System.out.println("--------------------------");
    }
    
    private void ejecutarTurnoHeroe() {
        boolean accionValida = false;
        
        while (!accionValida) {
            System.out.println("\n>>> Tu turno <<<");
            System.out.println("1. Atacar");
            System.out.println("2. Defender");
            System.out.println("3. Habilidad Especial (requiere mana)");
            System.out.println("4. Usar Item");
            System.out.print("Elige una accion: ");
            
            int opcion = leerInput();
            
            switch (opcion) {
                case 1:
                    System.out.println(heroe.getNombre() + " ataca!");
                    logger.log(heroe.getNombre() + " ataca a " + enemigo.getNombre());
                    heroe.atacar(enemigo);
                    accionValida = true;
                    break;
                case 2:
                    System.out.println(heroe.getNombre() + " se defiende!");
                    logger.log(heroe.getNombre() + " se defiende");
                    heroe.defenderse();
                    accionValida = true;
                    break;
                case 3:
                    // La habilidad retorna true si se ejecuto, false si falto mana
                    logger.log(heroe.getNombre() + " intenta usar habilidad especial");
                    boolean habilidadUsada = heroe.habilidadEspecial(enemigo);
                    if (habilidadUsada) {
                        accionValida = true;
                    } else {
                        System.out.println("Elige otra accion.");
                    }
                    break;
                case 4:
                    accionValida = usarItem();
                    break;
                default:
                    System.out.println("Opcion invalida. Intenta de nuevo.");
            }
        }
    }
    
    private int leerInput() {
        try {
            String input = scanner.nextLine().trim();
            return Integer.parseInt(input);
        } catch (NumberFormatException e) {
            return -1;
        }
    }
    
    private boolean usarItem() {
        List<Item> inventario = heroe.obtenerInventario();
        if (inventario.isEmpty()) {
            System.out.println("No tienes items. Elige otra accion.");
            return false;
        }
        
        System.out.println("\n--- Inventario ---");
        for (int i = 0; i < inventario.size(); i++) {
            System.out.println((i + 1) + ". " + inventario.get(i).getNombre());
        }
        System.out.println("0. Cancelar");
        System.out.print("Elige un item: ");
        
        try {
            int itemIndex = Integer.parseInt(scanner.nextLine().trim()) - 1;
            
            if (itemIndex == -1) {
                return false;
            }
            
            if (itemIndex >= 0 && itemIndex < inventario.size()) {
                Item item = heroe.removerItem(itemIndex);
                if (item != null) {
                    logger.log(heroe.getNombre() + " usa " + item.getNombre());
                    item.usar(heroe, enemigo);
                    return true;
                }
            }
            System.out.println("Item invalido. Elige otra accion.");
            return false;
        } catch (NumberFormatException e) {
            System.out.println("Entrada invalida. Elige otra accion.");
            return false;
        }
    }
    
    private void ejecutarTurnoEnemigo() {
        System.out.println("\n>>> Turno del " + enemigo.getNombre() + " <<<");
        logger.log("Turno de " + enemigo.getNombre());
        enemigo.realizarTurno(heroe);
    }
    
    private Item obtenerDropAleatorio() {
        int roll = randomDrop.nextInt(3);
        switch (roll) {
            case 0: return new PocionCuracion();
            case 1: return new PocionMana();
            case 2: return new PocionDanio();
            default: return new PocionCuracion();
        }
    }
}
