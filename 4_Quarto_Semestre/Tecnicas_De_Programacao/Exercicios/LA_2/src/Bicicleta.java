// Classe para bicicletas
class Bicicleta extends VeiculoSemMotor implements Calibravel, Desenhavel {
    public Bicicleta() {
        super(2, "Bicicleta");
    }

    @Override
    public void calibrarPneu(int idPneu) {
        if (idPneu >= 0 && idPneu < rodas.length) {
            rodas[idPneu].setCalibragem(true); // Calibra o pneu
            System.out.println("Pneu " + idPneu + " da bicicleta calibrado.");
        }
    }

    @Override
    public boolean pneusCalibrados() {
        for (Roda roda : rodas) {
            if (!roda.getCalibragem()) {
                return false;
            }
        }
        return true;
    }

    @Override
    public void move() {
        if (pneusCalibrados()) {
            distanciaPercorrida += 1; // Bicicleta se move a uma velocidade constante
        } else {
            System.out.println(tipo + " não pode se mover: pneus descalibrados.");
        }
    }

    @Override
    public String desenhar() {
        return "\n   __o    \n _`\\<,_ \n(*)/ (*)\n";
    }
}