package Exercicios.Ex_10;

public class Data {
    private int dia;
    private int mes;
    private int ano;

    public Data(int dia, int mes, int ano) {
        if (validaData(dia, mes, ano)) {
            this.dia = dia;
            this.mes = mes;
            this.ano = ano;
        } else {
            System.out.println("Data inválida. Configurando para 01/01/2000.");
            this.dia = 1;
            this.mes = 1;
            this.ano = 2000;
        }
    }

    public boolean validaData(int dia, int mes, int ano) {
        if (ano < 0 || mes < 1 || mes > 12) {
            return false;
        }

        int[] diasPorMes = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (mes == 2 && anoBissexto(ano)) {
            diasPorMes[1] = 29;
        }
        return dia > 0 && dia <= diasPorMes[mes - 1];
    }

    private boolean anoBissexto(int ano) {
        return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    }

    // Método toString para retornar a data no formato "DD/MM/AAAA"
    @Override
    public String toString() {
        return dia + "/" + mes + "/" + ano;
    }

    public String porExtenso() {
        String[] nomeMes = {"janeiro", "fevereiro", "março", "maio", "abril", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};
        return dia + " de " + nomeMes[mes-1] + " de " + ano;
    }
}
