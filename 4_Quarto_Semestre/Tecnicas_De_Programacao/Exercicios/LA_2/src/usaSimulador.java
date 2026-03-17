// Classe principal para testar o simulador
public class usaSimulador {
    public static void main(String[] args) {
        Simulador simulador = new Simulador();

        // Adiciona veículos de todos os tipos
        System.out.println("Adicionando veículos...");
        simulador.incluiVeiculo(new Bicicleta());
        simulador.incluiVeiculo(new Motocicleta(new Motor(1.0f, "combustão")));
        simulador.incluiVeiculo(new CarroPasseio(new Motor(1.5f, "combustão")));
        simulador.incluiVeiculo(new CarroEsportivo(new Motor(2.5f, "combustão")));
        simulador.incluiVeiculo(new Motocicleta(new Motor(0.75f, "elétrico")));
        simulador.incluiVeiculo(new CarroPasseio(new Motor(1.25f, "elétrico")));
        simulador.incluiVeiculo(new CarroEsportivo(new Motor(2.25f, "elétrico")));
        
        System.out.println("Veículos adicionados com sucesso!\n");

        // Lista os veículos após adição
        System.out.println("Listando veículos após adição:");
        simulador.listarVeiculos();

        // Calibra os pneus de todos os veículos
        System.out.println("\nCalibrando pneus de todos os veículos...");
        simulador.calibrarTodosPneus();
        System.out.println("Pneus calibrados com sucesso!\n");

        // Abastece os veículos a combustão
        System.out.println("\nAbastecendo veículos a combustão...");
        simulador.abastecerTodosVeiculos(50); // Abastece com 50% de combustível
        System.out.println("Veículos abastecidos com sucesso!\n");

        // Recarrega os veículos elétricos
        System.out.println("Recarregando veículos elétricos...");
        simulador.carregarTodosVeiculos(50); // Recarrega com 50% de bateria
        System.out.println("Veículos recarregados com sucesso!\n");

        // Move os veículos mais algumas vezes
        System.out.println("Movendo veículos...");
        for (int i = 0; i < 5; i++) {
            simulador.moveVeiculos();
        }

        simulador.desenharPista();

        System.out.println("Listando veículos após movimento:");
        simulador.listarVeiculos();
    }
}