package Aula_2.Exs;

import java.util.Scanner;

public class Ex_3 {
    public static void main (String[] atgs){

        try(Scanner teclado = new Scanner(System.in)){
            int n;
            
            System.out.print("Insira um numero: ");
            n = teclado.nextInt();
            
            int soma = 0, aux = 1;
            
            while(aux<n){
                if(n%aux == 0)
                    soma+=aux;
                aux++;
            }
            if(soma==n)
                System.out.printf("%d eh um numero perfeito", n);
            else
                System.out.printf
                ("%d nao eh um numero perfeito", n);
        }
    }
}