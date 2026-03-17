// Classe para rodas
class Roda {
    private boolean calibrado;

    public void setCalibragem(boolean calibrado) {
        this.calibrado = calibrado;
    }

    public boolean getCalibragem() {
        return calibrado;
    }

    @Override
    public String toString() {
        return "Roda{" +
                "calibrado=" + calibrado +
                '}';
    }
}