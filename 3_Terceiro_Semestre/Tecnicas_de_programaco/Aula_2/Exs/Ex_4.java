package Aula_2.Exs;
import java.util.Scanner;

public class Ex_4 {
    public static void main (String[] atgs){

        try(Scanner teclado = new Scanner(System.in)){
            int n;
            
            System.out.print("Insira um numero: ");
            n = teclado.nextInt();
            
            int soma = 0, aux = 2;
            
            while(aux<n){
                for(int i=2; i<aux; i++)
                    if(aux%i==0)
                        soma = 1;
                if(soma!=1)
                    System.out.println(aux + " ");
                soma = 0;
                aux++;
            }
        }
    }
}