package Exercicios.Ex_6;

public class Empregado {
    private String primeiroNome;
    private String sobrenome;
    private double salarioMensal;
    
    // Construtor
    public Empregado(String primeiroNome, String sobrenome, double salarioMensal) {
        this.primeiroNome = primeiroNome;
        this.sobrenome = sobrenome;
        setSalarioMensal(salarioMensal); // Usando setter para garantir que o salário seja não negativo
    }
    
    // Getters e Setters
    public String getPrimeiroNome() {
        return primeiroNome;
    }

    public void setPrimeiroNome(String primeiroNome) {
        this.primeiroNome = primeiroNome;
    }

    public String getSobrenome() {
        return sobrenome;
    }

    public void setSobrenome(String sobrenome) {
        this.sobrenome = sobrenome;
    }

    public double getSalarioMensal() {
        return salarioMensal;
    }

    public void setSalarioMensal(double salarioMensal) {
        if (salarioMensal > 0) {
            this.salarioMensal = salarioMensal;
        } else {
            this.salarioMensal = 0;
        }
    }
    
    // Método para calcular o salário anual
    public double salarioAnual() {
        return salarioMensal * 12;
    }
    
    // Método para dar aumento de 10% no salário
    public void aumentoSalario() {
        salarioMensal *= 1.10;
    }
}

