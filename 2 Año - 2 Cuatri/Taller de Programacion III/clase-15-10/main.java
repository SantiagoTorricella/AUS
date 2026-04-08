package clase1510;
import java.util.Stack;


// Productor-Consumidor
// Vamos a repasar sobre el problema de la ultima clase ne la que
// incrementabamos una variable con un hilo y la decrementabamos
// con otro, pisandose ambos procesos por la variable compartida

public class main {
    
    public static void main(String[] args) {

        Stack<Character> pila = new Stack<>();

        Productor productor = new Productor(pila);
        Productor productor2 = new Productor(pila);
        Consumidor consumidor = new Consumidor(pila);
        Consumidor consumidor2 = new Consumidor(pila);

        // Seteados consumidores y productores + la pila

        // IMPORTANTE: Usar .start() en vez de .run()
        // .start() crea un nuevo hilo y ejecuta run() concurrentemente
        // .run() simplemente ejecuta el método como una función normal (sin concurrencia)
        productor.start();
        productor2.start();
        consumidor.start();
        consumidor2.start();

        // Esperamos a que los PRODUCTORES terminen primero
        // join() hace que el hilo principal espere a que el hilo llamado termine
        try {
            productor.join();
            productor2.join();
            System.out.println("Productores terminaron. Tamaño de pila: " + pila.size());

            // Detenemos los consumidores de forma segura
            consumidor.stopConsuming();
            consumidor2.stopConsuming();

            // Esperamos a que terminen los consumidores
            consumidor.join();
            consumidor2.join();
        } catch(InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Tamaño final de la pila: " + pila.size());
    }
}
