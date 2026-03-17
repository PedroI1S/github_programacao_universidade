import java.util.Random;

// Classe base para todos os veículos
abstract class Veiculo {
    protected int distanciaPercorrida;
    protected Roda[] rodas;
    protected int quantidadeRodas;
    protected String tipo;

    public Veiculo(int quantidadeRodas, String tipo) {
        this.quantidadeRodas = quantidadeRodas;
        this.rodas = new Roda[quantidadeRodas];
        this.tipo = tipo;
        Random rand = new Random();
        for (int i = 0; i < quantidadeRodas; i++) {
            rodas[i] = new Roda();
            rodas[i].setCalibragem(rand.nextBoolean());
        }
    }

    
    public Roda[] getRodas() {
        return rodas;
    }

    public boolean pneusCalibrados() {
        for (Roda roda : rodas) {
            if (!roda.getCalibragem()) {
                return false;
            }
        }
        return true;
    }

    public abstract void move();

    @Override
    public String toString() {
        return "Veiculo{" +
                "distanciaPercorrida=" + distanciaPercorrida +
                ", tipo=" + tipo +
                '}';
    }
}