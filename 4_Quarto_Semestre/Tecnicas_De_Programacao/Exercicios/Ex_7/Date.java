package Exercicios.Ex_7;

public class Date {
    private int dia;
    private int mes;
    private int ano;
    
    public Date(int dia, int mes, int ano) {
        this.dia = dia;
        setMes(mes);
        this.ano = ano;
    }
    
    public int getDia() {
        return dia;
    }

    public void setDia(int dia) {
        this.dia = dia;
    }

    public int getMes() {
        return mes;
    }

    public void setMes(int mes) {
        if (mes >= 1 && mes <= 12) {
            this.mes = mes;
        } else {
            this.mes = 1;
        }
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }
    
    public void mostraData() {
        System.out.println(dia + "/" + mes + "/" + ano);
    }
}
