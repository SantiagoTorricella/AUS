package ejercicio2claseDiamand;

public class Main {
    public static void main(String[] args){

        Stack<String> stringStack  = new Stack<>();
        Stack<Integer> intStack  = new Stack<>();
    
    stringStack.push("Merca");
    stringStack.push("Falopa");
    stringStack.push("Tranquilizantes");
    stringStack.push("Sedantes");

    System.out.print(stringStack.peek() + "\n");
    System.out.print(stringStack.pop()+ "\n");
    System.out.print(stringStack.peek()+ "\n");
    System.out.print(stringStack.pop()+ "\n");
    System.out.print(stringStack.pop()+ "\n");
    System.out.print(stringStack.peek()+ "\n");
    System.out.print(stringStack.pop()+ "\n");

    intStack.push(25);
    intStack.push(30);
    intStack.push(1);
    intStack.push(89);
    System.out.print(intStack.peek() + "\n");
    System.out.print(intStack.pop()+ "\n");
    System.out.print(intStack.peek() + "\n");

}
    
}
