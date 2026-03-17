class CarroEsportivo extends VeiculoHibrido implements Calibravel, Desenhavel {
    public CarroEsportivo(Motor motor) {
        super(motor, 4, "CarroEsportivo");
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
        return "\n   _______\n _/\\______\\\\__\n/ ,-. -|-  ,-.`-.\n`( o )----( o )-'\n  `-'      `-'\n";
    }
}