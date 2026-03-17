package Aula_2.Exs;

import java.util.Scanner;

public class Ex_1 {

    public static void main (String[] args){
        
        try(Scanner teclado = new Scanner(System.in)){
            System.out.print("Digite um numero: ");
            int i = teclado.nextInt();

            for(int j=1; j<i; j+=2){
                System.out.printf("%d  ", j);
            }
        }
    }
}
