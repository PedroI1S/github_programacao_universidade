package Aula_2.Exs;

import java.util.Scanner;

public class Ex_2 {
    
    public static void main (String[] args){

        try(Scanner teclado = new Scanner(System.in)){
            System.out.print("Informe um numero: ");
            int n = teclado.nextInt();

            int j=0;

            for(int i=2; i<n; i++){
                if(n%i!=0){
                    j=1;
                }
            }

            if(j!=0)
            System.out.println("Primo");
            else
            System.out.println("Nao primo");
        }
    }
}
