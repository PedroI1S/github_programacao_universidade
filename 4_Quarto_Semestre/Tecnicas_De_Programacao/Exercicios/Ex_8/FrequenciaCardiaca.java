package Exercicios.Ex_8;

import java.util.Calendar;

public class FrequenciaCardiaca {
    private String primeiroNome;
    private String sobrenome;
    private int diaNascimento;
    private int mesNascimento;
    private int anoNascimento;
    
    public FrequenciaCardiaca(String primeiroNome, String sobrenome, int diaNascimento, int mesNascimento, int anoNascimento) {
        this.primeiroNome = primeiroNome;
        this.sobrenome = sobrenome;
        this.diaNascimento = diaNascimento;
        this.mesNascimento = mesNascimento;
        this.anoNascimento = anoNascimento;
    }
    
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

    public int getDiaNascimento() {
        return diaNascimento;
    }

    public void setDiaNascimento(int diaNascimento) {
        this.diaNascimento = diaNascimento;
    }

    public int getMesNascimento() {
        return mesNascimento;
    }

    public void setMesNascimento(int mesNascimento) {
        this.mesNascimento = mesNascimento;
    }

    public int getAnoNascimento() {
        return anoNascimento;
    }

    public void setAnoNascimento(int anoNascimento) {
        this.anoNascimento = anoNascimento;
    }
    
    public int obterIdade() {
        Calendar calendario = Calendar.getInstance();
        int anoAtual = calendario.get(Calendar.YEAR);
        int mesAtual = calendario.get(Calendar.MONTH) + 1;
        int diaAtual = calendario.get(Calendar.DAY_OF_MONTH);
        
        int idade = anoAtual - anoNascimento;
        
        if (mesAtual < mesNascimento || (mesAtual == mesNascimento && diaAtual < diaNascimento)) {
            idade--;
        }
        
        return idade;
    }
    
    public int obterFrequenciaMaxima() {
        return 220 - obterIdade();
    }
    
    public String obterFrequenciaIdeal() {
        int frequenciaMaxima = obterFrequenciaMaxima();
        int frequenciaMinima = (int) (frequenciaMaxima * 0.5);
        int frequenciaMaximaIdeal = (int) (frequenciaMaxima * 0.85);
        return frequenciaMinima + " a " + frequenciaMaximaIdeal;
    }
}
