package Exercicios.Ex_6;

public class TesteEmpregado {
    public static void main(String[] args) {
        // Criando objetos da classe Empregado
        Empregado empregado1 = new Empregado("João", "Silva", 3000);
        Empregado empregado2 = new Empregado("Maria", "Santos", 4000);
        
        // Exibindo salário anual de cada empregado
        System.out.println("Salário anual de " + empregado1.getPrimeiroNome() + ": " + empregado1.salarioAnual());
        System.out.println("Salário anual de " + empregado2.getPrimeiroNome() + ": " + empregado2.salarioAnual());
        
        // Dando aumento de 10% no salário de cada empregado
        empregado1.aumentoSalario();
        empregado2.aumentoSalario();
        
        // Exibindo salário anual atualizado de cada empregado
        System.out.println("Salário anual atualizado de " + empregado1.getPrimeiroNome() + ": " + empregado1.salarioAnual());
        System.out.println("Salário anual atualizado de " + empregado2.getPrimeiroNome() + ": " + empregado2.salarioAnual());
    }
}

