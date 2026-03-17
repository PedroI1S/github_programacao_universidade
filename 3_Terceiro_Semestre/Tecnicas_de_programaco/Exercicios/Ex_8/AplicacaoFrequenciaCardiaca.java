package Exercicios.Ex_8;

import java.util.Scanner;

public class AplicacaoFrequenciaCardiaca {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Solicita informações da pessoa
        System.out.println("Informe seu primeiro nome:");
        String primeiroNome = scanner.nextLine();
        
        System.out.println("Informe seu sobrenome:");
        String sobrenome = scanner.nextLine();
        
        System.out.println("Informe o dia do seu nascimento:");
        int diaNascimento = scanner.nextInt();
        
        System.out.println("Informe o mês do seu nascimento:");
        int mesNascimento = scanner.nextInt();
        
        System.out.println("Informe o ano do seu nascimento:");
        int anoNascimento = scanner.nextInt();
        
        // Instancia um objeto da classe FrequenciaCardiaca
        FrequenciaCardiaca pessoa = new FrequenciaCardiaca(primeiroNome, sobrenome, diaNascimento, mesNascimento, anoNascimento);
        
        // Imprime as informações do objeto
        System.out.println("\nInformações da pessoa:");
        System.out.println("Nome: " + pessoa.getPrimeiroNome() + " " + pessoa.getSobrenome());
        System.out.println("Data de Nascimento: " + pessoa.getDiaNascimento() + "/" + pessoa.getMesNascimento() + "/" + pessoa.getAnoNascimento());
        
        // Calcula e imprime a idade da pessoa
        System.out.println("Idade: " + pessoa.obterIdade() + " anos");
        
        // Calcula e imprime a frequência cardíaca máxima da pessoa
        System.out.println("Frequência Cardíaca Máxima: " + pessoa.obterFrequenciaMaxima() + " bpm");
        
        // Calcula e imprime a frequência cardíaca ideal da pessoa
        System.out.println("Faixa de Frequência Cardíaca Ideal: " + pessoa.obterFrequenciaIdeal() + " bpm");
        
        scanner.close();
    }
}
