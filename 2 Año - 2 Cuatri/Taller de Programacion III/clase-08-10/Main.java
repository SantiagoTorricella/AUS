import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Main {

    public static void main(String[] args){
                FileReader fr = null;
        // Estamos viendo exceptions en esta clase
        // y con eso bloques try catch
        try{
        Class.forName("java.util.Date");
        }
        catch(ClassNotFoundException e){
            // ... aca va codigo para manejar la excepcion
        }
    
        try{
           fr = new FileReader("hola.txt");
            Class.forName("java.util.Date");
            fr.read();
        }
        catch(FileNotFoundException e){
            // ...codigo para handlear la excepcion 
        } 
        catch(ClassNotFoundException e){
            // ...codigo para handlear la excepcion 
        } 
        catch(IOException e){
            // ...codigo para handlear la excepcion 
        }
        finally{
            try{
            fr.close();
            }
            catch(IOException e){
            // ...Handleo el error
            }
        }
        
        // try-with-resources
        try(FileReader fra = new FileReader("Hola.txt")){
            fra.read();
        }
        catch(IOException exception){
            // ...Handleo la excepecion
            // Como se puede ver esto es mucho mas limpio, ni idea por que je 😅
        }

    }
}

// Aca digo q la excepcion es verificada
// TODO: ver que onda las excepcions verificadas/no verificadas
/* public class SinUnMangoException() extends Exception{

} */

/* public class MeCortaronElCableException extends RunTimeException(){
    
} */