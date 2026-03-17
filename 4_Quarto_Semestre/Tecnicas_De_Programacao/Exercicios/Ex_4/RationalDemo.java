package Exercicios.Ex_4;

import java.util.Scanner;

public class RationalDemo {
    
    public static void main(String[] args) {
        
        try(Scanner teclado = new Scanner(System.in)){
            //Setando Variável

            System.out.print("Insira um valor para o numerador:");
            int numerador = teclado.nextInt();
            System.out.print("Insira um valor para o denominador:");
            int denominador = teclado.nextInt();

            Rational Rac = new Rational(numerador, denominador);

            int aux = 0;
            char opcao = 0;

            //Apresentando operações

            do {
                System.out.println("\nSelecione uma operação | / | * | + | - | PontoFlutuante | Imprimir | Stop :");
                aux = (int) teclado.next().charAt(opcao);
                if (aux > 97)
                    aux -= 32;

                switch (aux) {
                    // Divisão
                    case 47:
                        System.out.println("Divisao selecionada \nInsira um valor para o numerador e denominador: ");
                        numerador = teclado.nextInt();
                        denominador = teclado.nextInt();

                        Rac.Quo(numerador, denominador);

                        aux = 1;

                        break;
                    // Multiplicação
                    case 42:
                        System.out.println("Multiplicacao selecionada \nInsira um valor para o numerador e denominador: ");
                        numerador = teclado.nextInt();
                        denominador = teclado.nextInt();

                        Rac.Prod(numerador, denominador);

                        aux = 2;

                        break;
                    // Soma
                    case 43:
                        System.out.println("Soma selecionada \nInsira um valor para o numerador e denominador: ");
                        numerador = teclado.nextInt();
                        denominador = teclado.nextInt();

                        Rac.Sum(numerador, denominador);

                        aux = 3;

                        break;
                    // Subtração
                    case 45:
                        System.out.println("Subtracao selecionada \nInsira um valor para o numerador e denominador: ");
                        numerador = teclado.nextInt();
                        denominador = teclado.nextInt();

                        Rac.Sub(numerador, denominador);

                        aux = 4;

                        break;

                    // Imprimir
                    case 73:
                        Rac.Imprimir();

                        aux = 5;

                        break;
                    // Imprimir Ponto
                    case 80:
                        System.out.println("Escolha a precisão decimal: ");
                        int n = teclado.nextInt();

                        Rac.ImprimirPonto(n);

                        aux = 6;

                        break;
                    case 83:
                        aux = 8;

                        break;
                    default:
                        System.out.println("Valor inválido inserido, nada foi computado.\n\n");
                        aux = 7;
                        break;
                }
            } while (aux > 0 && aux < 8);
        }
    }
}
