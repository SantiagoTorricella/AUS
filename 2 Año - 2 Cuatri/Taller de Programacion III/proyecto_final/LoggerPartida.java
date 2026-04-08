import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class LoggerPartida implements Runnable {
    
    private BlockingQueue<String> colaLogs;
    private volatile boolean partidaTerminada;
    private String nombreHeroe;
    private StringBuilder logCompleto;
    private String resultadoFinal;
    
    public LoggerPartida(String nombreHeroe) {
        this.colaLogs = new LinkedBlockingQueue<>();
        this.partidaTerminada = false;
        this.nombreHeroe = nombreHeroe;
        this.logCompleto = new StringBuilder();
        this.resultadoFinal = "EN_PROGRESO";
        
        // Header del log
        LocalDateTime ahora = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        logCompleto.append("=== LOG DE PARTIDA ===\n");
        logCompleto.append("Fecha: ").append(ahora.format(formatter)).append("\n");
        logCompleto.append("Heroe: ").append(nombreHeroe).append("\n");
        logCompleto.append("======================\n\n");
    }
    
    public void log(String mensaje) {
        try {
            colaLogs.put(mensaje);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
    
    public void finalizarPartida(boolean victoria) {
        this.resultadoFinal = victoria ? "VICTORIA" : "DERROTA";
        this.partidaTerminada = true;
    }
    
    @Override
    public void run() {
        while (!partidaTerminada || !colaLogs.isEmpty()) {
            try {
                String mensaje = colaLogs.poll();
                if (mensaje != null) {
                    LocalDateTime ahora = LocalDateTime.now();
                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss");
                    String lineaLog = "[" + ahora.format(formatter) + "] " + mensaje + "\n";
                    logCompleto.append(lineaLog);
                }
                // Que no consuma toda la CUPU
                Thread.sleep(50);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
        
        // Generar archivo de log al finalizar
        generarArchivoLog();
    }
    
    private void generarArchivoLog() {
        logCompleto.append("\n======================\n");
        logCompleto.append("RESULTADO: ").append(resultadoFinal).append("\n");
        logCompleto.append("======================\n");
        
        LocalDateTime ahora = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyyMMdd_HHmmss");
        String nombreArchivo = "log_partida_" + nombreHeroe + "_" + ahora.format(formatter) + ".txt";
        
        try (PrintWriter writer = new PrintWriter(new FileWriter(nombreArchivo))) {
            writer.print(logCompleto.toString());
            System.out.println("\n Log guardado en: " + nombreArchivo);
        } catch (IOException e) {
            System.err.println("Error al guardar el log: " + e.getMessage());
        }
    }
}
