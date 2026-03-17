class CarroPasseio extends VeiculoHibrido implements Calibravel, Desenhavel {
    public CarroPasseio(Motor motor) {
        super(motor, 4, "CarroPasseio");
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
        return "\n    ____\n __/  |_\\_\n| _     _``-.\n'-( )---( )--'\n";
    }
}