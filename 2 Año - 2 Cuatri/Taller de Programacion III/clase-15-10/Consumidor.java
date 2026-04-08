package clase1510;
import java.util.Stack;
import java.util.EmptyStackException;

public class Consumidor extends Thread{

    private Stack<Character> pila;
    private volatile boolean running = true; // Flag para detener el consumidor

    public Consumidor(Stack<Character> pila) {
        this.pila = pila;
    }

    @Override
    public void run(){
        // El consumidor debe consumir continuamente, no solo una vez
        while(running) {
            synchronized(pila) {
                // Mientras la pila esté vacía, esperamos
                while(pila.isEmpty() && running) {
                    try {
                        // wait() libera el lock y espera a ser notificado
                        // por el productor cuando agregue elementos
                        pila.wait(100); // Timeout de 100ms para verificar running
                    } catch(InterruptedException e) {
                        Thread.currentThread().interrupt();
                        return;
                    }
                }
                
                // Si la pila no está vacía, consumimos
                if(!pila.isEmpty()) {
                    try {
                        char c = pila.pop();
                        System.out.println(Thread.currentThread().getName() + " consumió: " + c + " | Tamaño: " + pila.size());
                    } catch(EmptyStackException e) {
                        // Manejo del caso de pila vacía (race condition menor)
                        // Esto puede pasar si otro consumidor toma el último elemento
                    }
                }
            }
            
            // Pequeña pausa entre consumos
            try {
                Thread.sleep(100 + (int)(Math.random() * 400));
            } catch(InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }
    
    // Método para detener el consumidor de forma segura
    public void stopConsuming() {
        running = false;
        interrupt();
    }
    
}
