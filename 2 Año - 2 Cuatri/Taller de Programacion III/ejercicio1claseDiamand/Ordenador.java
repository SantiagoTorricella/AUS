package ejercicio1claseDiamand;

public class Ordenador {

    // Helper method to swap two elements in the array
    private void swap(Ordenable[] items, int i, int j) {
        Ordenable temp = items[i];
        items[i] = items[j];
        items[j] = temp;
    }

    // Helper method to compare two Ordenable objects by year, then by name
    // Returns true if first should come after second (needs swap)
    private boolean shouldSwapByAnio(Ordenable first, Ordenable second) {
        if (first.getAnio() > second.getAnio()) {
            return true;
        }
        if (first.getAnio() == second.getAnio()) {
            return first.getNombre().compareTo(second.getNombre()) > 0;
        }
        return false;
    }

    // Helper method to compare two Ordenable objects by name, then by year
    // Returns true if first should come after second (needs swap)
    private boolean shouldSwapByNombre(Ordenable first, Ordenable second) {
        int nameComparison = first.getNombre().compareTo(second.getNombre());
        if (nameComparison > 0) {
            return true;
        }
        if (nameComparison == 0) {
            return first.getAnio() > second.getAnio();
        }
        return false;
    }

    public void ordenarPorAnio(Ordenable[] items) {
        int length = items.length;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length - i - 1; j++) {
                if (shouldSwapByAnio(items[j], items[j + 1])) {
                    swap(items, j, j + 1);
                }
            }
        }
    }

    public void ordenarPorNombre(Ordenable[] items) {
        int length = items.length;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length - i - 1; j++) {
                if (shouldSwapByNombre(items[j], items[j + 1])) {
                    swap(items, j, j + 1);
                }
            }
        }
    }
}