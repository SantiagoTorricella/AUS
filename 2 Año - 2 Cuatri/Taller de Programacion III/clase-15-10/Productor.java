package clase1510;
import java.util.Stack;

public class Productor extends Thread{

    private Stack<Character> pila;

    public Productor(Stack<Character> pila) {
        this.pila = pila;
    }

    @Override
    public void run(){
        // Aca genero los caracteres para la pila
        for(int i=0 ; i<200; i++){
            char c = (char)('a' + Math.random() * 26);
            
            // SINCRONIZACIÓN: synchronized evita que múltiples hilos accedan
            // simultáneamente a la pila (condición de carrera)
            synchronized(pila) {
                pila.push(c);
                System.out.println(Thread.currentThread().getName() + " produjo: " + c + " | Tamaño: " + pila.size());
                
                // notifyAll() despierta a los consumidores que estén esperando
                pila.notifyAll();
            }
            
            try{
                // Simulamos tiempo de producción variable
                Thread.sleep(200 + (int)(Math.random() * 800));
            }
            catch(InterruptedException e){
                e.printStackTrace();
            }
        }
    }
    
}
