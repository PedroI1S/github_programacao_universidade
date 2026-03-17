package Exercicios.Ex_7;

public class TesteDate {
    public static void main(String[] args) {
        // Criando objeto da classe Date
        Date data = new Date(15, 6, 2022);
        
        // Exibindo a data
        System.out.print("Data: ");
        data.mostraData();
        
        // Atualizando o mês para um valor inválido
        data.setMes(15);
        
        // Exibindo a data atualizada
        System.out.print("Data atualizada: ");
        data.mostraData();
    }
}
