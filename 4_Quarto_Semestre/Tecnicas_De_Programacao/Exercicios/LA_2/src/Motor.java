import java.util.Random;

// Classe para o motor
class Motor {
    private int giroAtual;
    private float cilindrada;
    private String modo;
    public static final float fatorConsumoCombustao = 0.001f;
    public static final float fatorConsumoEletrico = 0.0001f;

    public Motor(float cilindrada, String modo) {
        this.cilindrada = cilindrada;
        this.modo = modo;
        this.giroAtual = new Random().nextInt(5000) + 1000; // Giro inicial randomico
    }

    public int converterGiroParaKmh() {
        return (int) (giroAtual * cilindrada / 1000); // Converte giro para km/h
    }

    public void acelerar() {
        if (modo.equals("elétrico")) {
            giroAtual = 6000; // Aceleração maior para motores elétricos
        } else {
            giroAtual = 5000; // Aceleração padrão para motores a combustão
        }
    }

    public String getModo() {
        return modo;
    }

    public float getFatorConsumoCombustao() {
        return fatorConsumoCombustao;
    }

    public float getFatorConsumoEletrico() {
        return fatorConsumoEletrico;
    }
}