class Motocicleta extends VeiculoHibrido implements Calibravel, Desenhavel {
    public Motocicleta(Motor motor) {
        super(motor, 2, "Motocicleta");
    }

    @Override
    public void calibrarPneu(int idPneu) {
        if (idPneu >= 0 && idPneu < rodas.length) {
            rodas[idPneu].setCalibragem(true); // Calibra o pneu
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
    public String desenhar() {
        return "\n   ,_oo\n.-/c-//::\n( )'==( )\n";
    }
}