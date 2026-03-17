import java.util.Arrays;
import java.util.Objects;

// Classe para o simulador
class Simulador {
    private Veiculo[] veiculos;
    private int count;

    public Simulador() {
        veiculos = new Veiculo[10];
        count = 0;
    }

    public void incluiVeiculo(Veiculo veiculo) {
        if (count < 10) {
            veiculos[count++] = veiculo;
            System.out.println("Veículo adicionado com sucesso.");
        } else {
            System.out.println("Limite de veículos atingido (máximo de 10 veículos).");
        }
    }

    public void moveVeiculos() {
        for (Veiculo veiculo : veiculos) {
            if (veiculo != null) {
                veiculo.move();
            }
        }
    }

    public void calibrarTodosPneus() {
        for (Veiculo veiculo : veiculos) {
            if (veiculo != null && veiculo instanceof Calibravel) {
                Calibravel veiculoCalibravel = (Calibravel) veiculo;
                for (int i = 0; i < veiculo.getRodas().length; i++) {
                    veiculoCalibravel.calibrarPneu(i); // Calibra cada pneu
                }
                System.out.println("Pneus do veículo " + veiculo.tipo + " calibrados.");
            }
        }
        System.out.println("Todos os pneus de todos os veículos foram calibrados.");
    }

    public void abastecerTodosVeiculos(float quantidade) {
        for (Veiculo veiculo : veiculos) {
            if (veiculo != null && veiculo instanceof Reabastecivel) {
                ((Reabastecivel) veiculo).abastecerCombustivel(quantidade);
            }
        }
        System.out.println("Todos os veículos foram abastecidos.");
    }

    public void carregarTodosVeiculos(int nivel) {
        for (Veiculo veiculo : veiculos) {
            if (veiculo != null && veiculo instanceof Recarregavel) {
                ((Recarregavel) veiculo).carregarBateria(nivel);
            }
        }
        System.out.println("Todos os veículos foram carregados.");
    }

    public void listarVeiculos() {
        System.out.println("Lista de Veículos:");
        for (int i = 0; i < count; i++) {
            Veiculo veiculo = veiculos[i];
            System.out.println("ID: " + i + " - Tipo: " + veiculo.tipo);
            System.out.println("Pneus:");
            for (int j = 0; j < veiculo.getRodas().length; j++) {
                System.out.println("  Pneu " + j + ": " + (veiculo.getRodas()[j].getCalibragem() ? "Calibrado" : "Descalibrado"));
            }
            if (veiculo instanceof VeiculoHibrido) {
                VeiculoHibrido veiculoHibrido = (VeiculoHibrido) veiculo;
                System.out.println("Tipo do Motor: " + veiculoHibrido.getMotor().getModo());
                if (veiculoHibrido.getMotor().getModo().equals("combustão")) {
                    System.out.println("Tanque Combustivel: " + veiculoHibrido.getTanqueCombustivel() + "%");
                } else {
                    System.out.println("Nivel Bateria: " + veiculoHibrido.getNivelBateria() + "%");
                }
            }
            System.out.println("Distancia Percorrida: " + veiculo.distanciaPercorrida + " km");
            System.out.println();
        }
    }

    public void desenharPista() {
        System.out.println("Pista de Corrida:");
    
        // Filtra os veículos não nulos e ordena pela distância percorrida (do maior para o menor)
        Veiculo[] veiculosAtivos = Arrays.stream(veiculos)
                .filter(Objects::nonNull)
                .toArray(Veiculo[]::new);
    
        // Desenha a pista
        for (Veiculo veiculo : veiculosAtivos) {
            if (veiculo instanceof Desenhavel) {
                // Obtém o desenho do veículo
                String desenho = ((Desenhavel) veiculo).desenhar();
    
                // Divide o desenho em linhas
                String[] linhas = desenho.split("\n");
    
                // Adiciona espaços antes de cada linha, proporcional à distância percorrida
                for (String linha : linhas) {
                    for (int i = 0; i < veiculo.distanciaPercorrida; i++) {
                        System.out.print(" ");
                    }
                    System.out.println(linha);
                }
            }
        }
    }

    public int getCount() {
        return count;
    }
}