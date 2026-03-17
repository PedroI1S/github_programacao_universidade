package Exercicios.Ex_7;

public class TesteDate {
    public static void main(String[] args) {
        Date data = new Date(15, 6, 2022);
        
        System.out.print("Data: ");
        data.mostraData();
        
        data.setMes(15);
        
        System.out.print("Data atualizada: ");
        data.mostraData();
    }
}
