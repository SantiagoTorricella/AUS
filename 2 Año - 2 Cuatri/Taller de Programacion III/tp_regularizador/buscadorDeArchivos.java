import java.io.File;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

public class buscadorDeArchivos {
    
    private static AtomicBoolean encontrado = new AtomicBoolean(false);
    private static AtomicInteger tareasActivas = new AtomicInteger(0);
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("=== BUSCADOR DE ARCHIVOS MULTIHILO ===");
        System.out.print("Ingrese el nombre del archivo a buscar (agregar extension del archivo): ");
        String nombreArchivo = scanner.nextLine();
        
        System.out.print("Ingrese la ruta inicial de busqueda (Enter para directorio actual): ");
        String rutaInicial = scanner.nextLine();
        
        if (rutaInicial.isEmpty()) {
            rutaInicial = System.getProperty("user.dir"); 
        }
        
        File directorioInicial = new File(rutaInicial);
        
        if (!directorioInicial.exists() || !directorioInicial.isDirectory()) {
            System.out.println("Error: La ruta especificada no existe o no es un directorio.");
            scanner.close();
            return;
        }
        
        System.out.println("\nIniciando busqueda de '" + nombreArchivo + "' en: " + directorioInicial.getAbsolutePath());
        System.out.println("Usando " + Runtime.getRuntime().availableProcessors() + " hilos...\n");
        
        ExecutorService executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
        
        tareasActivas.incrementAndGet();
        buscarArchivo(directorioInicial, nombreArchivo, executor);
        
        // Esperar hasta que no hayxa tareas activas
        while (tareasActivas.get() > 0) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                break;
            }
        }
        
        executor.shutdown();
        try {
            executor.awaitTermination(10, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            System.err.println("La busqueda fue interrumpida.");
        }
        
        if (!encontrado.get()) {
            System.out.println("\nArchivo no encontrado.");
        }
        
        System.out.println("\nBusqueda finalizada");
        scanner.close();
    }
    
    private static void buscarArchivo(File directorio, String nombreArchivo, ExecutorService executor) {
        try {
            if (encontrado.get()) {
                return;
            }
            
            File[] archivos = directorio.listFiles();
            
            if (archivos == null) {
                System.out.println("[ADVERTENCIA] No se puede leer: " + directorio.getAbsolutePath());
                return;
            }
            
            for (File archivo : archivos) {
                if (encontrado.get()) {
                    return;
                }
                
                tareasActivas.incrementAndGet();
                executor.submit(() -> {
                    try {
                        if (encontrado.get()) {
                            return;
                        }
                        
                        if (archivo.isFile()) {
                            
                            if (archivo.getName().equals(nombreArchivo)) {
                                encontrado.set(true);
                                System.out.println("\nARCHIVO ENCONTRADO por " + Thread.currentThread().getName());
                                System.out.println("  Ruta: " + archivo.getAbsolutePath());
                                System.out.println("  Tamaño: " + archivo.length() + " bytes");
                            }
                        } else if (archivo.isDirectory() && archivo.canRead()) {
                            buscarArchivo(archivo, nombreArchivo, executor);
                        }
                    } catch (SecurityException e) {
                        System.out.println("[PERMISO DENEGADO] " + archivo.getAbsolutePath());
                    } finally {
                        tareasActivas.decrementAndGet();
                    }
                });
            }
        } finally {
            tareasActivas.decrementAndGet();
        }
    }
}