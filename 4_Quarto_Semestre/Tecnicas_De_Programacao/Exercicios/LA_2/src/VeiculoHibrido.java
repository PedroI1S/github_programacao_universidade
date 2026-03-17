import java.util.Random;

// Classe para veículos híbridos (com motor)
abstract class VeiculoHibrido extends Veiculo implements Reabastecivel, Recarregavel {
    private float tanqueCombustivel;
    private int nivelBateria;
    private Motor motor;

    public VeiculoHibrido(Motor motor, int quantidadeRodas, String tipo) {
        super(quantidadeRodas, tipo + " (" + motor.getModo() + ")");
        this.motor = motor;
        Random rand = new Random();
        this.tanqueCombustivel = motor.getModo().equals("combustão") ? rand.nextFloat() * 100 : 0;
        this.nivelBateria = motor.getModo().equals("elétrico") ? rand.nextInt(101) : 0;
    }

    @Override
    public void move() {
        if (pneusCalibrados()) {
            if (motor.getModo().equals("combustão") && tanqueCombustivel > 0) {
                motor.acelerar();
                int velocidade = motor.converterGiroParaKmh();
                distanciaPercorrida += velocidade;
                tanqueCombustivel -= motor.getFatorConsumoCombustao() * velocidade;
                if (tanqueCombustivel < 0) {
                    tanqueCombustivel = 0;
                }
            } else if (motor.getModo().equals("elétrico") && nivelBateria > 0) {
                motor.acelerar();
                int velocidade = motor.converterGiroParaKmh();
                distanciaPercorrida += velocidade;
                nivelBateria -= motor.getFatorConsumoEletrico() * velocidade;
                if (nivelBateria < 0) {
                    nivelBateria = 0;
                }
            }
        }
    }

    @Override
    public void abastecerCombustivel(float quantidade) {
        if (motor.getModo().equals("combustão")) {
            tanqueCombustivel += quantidade;
            if (tanqueCombustivel > 100) {
                tanqueCombustivel = 100;
            }
        }
    }

    @Override
    public void carregarBateria(int nivel) {
        if (motor.getModo().equals("elétrico")) {
            nivelBateria += nivel;
            if (nivelBateria > 100) {
                nivelBateria = 100;
            }
        }
    }

    public float getTanqueCombustivel() {
        return tanqueCombustivel;
    }

    public int getNivelBateria() {
        return nivelBateria;
    }

    public Motor getMotor() {
        return motor;
    }
}