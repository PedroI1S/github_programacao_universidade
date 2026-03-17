package Aula_2.Exs;

import java.util.Scanner;

public class Ex_6 {
    public static void main(String[] atgs) {

        try (Scanner teclado = new Scanner(System.in)) {
            while (true) {

                int n;
                Boolean controle = false;

                System.out.print("Insira um numero impar: ");
                do {
                    n = teclado.nextInt();
                    if(n==-1){
                        controle = true;
                        break;
                    }
                        
                } while (n < 0 || n % 2 == 0);

                if(controle == true)
                    break;

                int m[][] = new int[n][(n * 2) - 1];
                int key = 1;

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < (n * 2 - 1); j++) {
                        if (j == i) {
                            key = 0;
                        }
                        if (j == (n * 2 - 1) - i) {
                            key = 1;
                        }
                        m[i][j] = 1 - key;
                    }
                    if (i == 0) {
                        key = 1;
                    }
                }

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < (n * 2 - 1); j++) {
                        System.out.print(m[i][j] + " ");
                    }
                    System.out.print("\n");
                }
            }
        }
    }
}
