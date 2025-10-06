package ejercicio2claseDiamand;

import java.util.ArrayList;
import java.util.EmptyStackException;

public class Stack<T> {

    private ArrayList<T> contenido;
    
    public Stack(){
        this.contenido = new ArrayList<>();
    }


    public void push (T item){
        contenido.add(item);
    }

    public T pop(){
        if (this.notEmpty()) {
            return contenido.remove(contenido.size() - 1);
        }
        throw new EmptyStackException();
    }
    
    public T peek(){
        if (this.notEmpty()) {
            return contenido.get(contenido.size() - 1);
        }
        throw new EmptyStackException();
    }

    public boolean notEmpty(){
        if (contenido.size() >= 1){
            return true;
        }
        return false;
    }

}
