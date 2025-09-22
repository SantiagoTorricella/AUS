class A {
    public A(){
        System.out.println("A");
    }
}

// Aunq extendamos de A, el constructor no se hereda
class B extends A { 
    public B(){
        System.out.println("B");
    }
}

// Instancio un objeto de ambas clases
// En java, todo codigo "ejectubal" se tiene que dar dentro de metodos, por eso comento lo de abajo
// dado que no esta en ningun metodo de una clase, no puedo declarar esto en top-level
// A a = new A();
// B b = new B();

// Si yo hago un a.toString() es decir un toString a un objeto
// me va a devolver algo asi A@#3AF59B que es el nombre de la
// clase de la cual es instanciada y el HASH CODE de esa instancia.