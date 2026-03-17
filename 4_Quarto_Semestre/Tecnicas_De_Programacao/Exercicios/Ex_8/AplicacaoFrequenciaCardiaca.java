package Exercicios.Ex_8;

import java.util.Scanner;

public class AplicacaoFrequenciaCardiaca {
    public static void main(String[] args) {
        try(Scanner scanner = new Scanner(System.in)){
        
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
        
        FrequenciaCardiaca pessoa = new FrequenciaCardiaca(primeiroNome, sobrenome, diaNascimento, mesNascimento, anoNascimento);
        
        System.out.println("\nInformações da pessoa:");
        System.out.println("Nome: " + pessoa.getPrimeiroNome() + " " + pessoa.getSobrenome());
        System.out.println("Data de Nascimento: " + pessoa.getDiaNascimento() + "/" + pessoa.getMesNascimento() + "/" + pessoa.getAnoNascimento());
        
        System.out.println("Idade: " + pessoa.obterIdade() + " anos");
        
        System.out.println("Frequência Cardíaca Máxima: " + pessoa.obterFrequenciaMaxima() + " bpm");
        
        System.out.println("Faixa de Frequência Cardíaca Ideal: " + pessoa.obterFrequenciaIdeal() + " bpm");
        }
    }
}
