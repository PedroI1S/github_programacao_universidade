package Exercicios.Ex_2;

import java.util.Scanner;

public class texte {
    public static void main(String[] args) {     
        int aux = 0;   
        try (Scanner teclado = new Scanner(System.in)){
            aux = (int)teclado.nextLine().charAt(aux);
            System.out.println(aux);
        }
    }
}
