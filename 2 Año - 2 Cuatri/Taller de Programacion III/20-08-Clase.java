/* public class Calucadora{    

public static void main(String [] args){



switch (args[0]) {
    case "+":
        int result = Integer.parseInt(args[1]) + Integer.parseInt(args[2]);
        System.out.println(result);
        return;
    case "-":
        int result2 = Integer.parseInt(args[1]) - Integer.parseInt(args[2]);
        System.out.println(result2);
        return;
    case "x":
        int result3 = Integer.parseInt(args[1]) * Integer.parseInt(args[2]);
        System.out.println(result3);
        return;
    case "/":
        int result4 = Integer.parseInt(args[1]) / Integer.parseInt(args[2]);
        System.out.println(result4);
        return;
        
    default:
        throw new AssertionError();
        }
    }
} */

public class StringDemo2{
    public static void main(String[] args) {
    long ct = System.currentTimeMillis();
     String a ="";
     for(int i = 0; i < 10000; i++){
        a = a + i;
        // Esta verga crea 10000 copias distintas en cada iteracion
     }
    long end = System.currentTimeMillis();
    System.out.println(end - ct);
    StringBuilder sb = new StringBuilder("");
    
    long ct2 = System.currentTimeMillis();
    for(int i = 0; i < 10000; i++){
        sb.append(i);
    }
    long end2 = System.currentTimeMillis();
    System.out.println(end2 - ct2);
    }
}