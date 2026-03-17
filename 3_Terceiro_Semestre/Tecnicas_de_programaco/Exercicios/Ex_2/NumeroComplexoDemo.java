package Exercicios.Ex_2;

import java.util.Scanner;

public class NumeroComplexoDemo {
    public static void main(String[] args) {
        // Adquiro o primeiro valor

        System.out.println("Insira um numero para parte real e um para a parte imaginaria: ");

        try (Scanner teclado = new Scanner(System.in)) {
            double real;
            real = teclado.nextDouble();
            double imaginario;
            imaginario = teclado.nextDouble();

            NumeroComplexo NumC = new NumeroComplexo(real, imaginario);

            // Apresento operações e finalizo o programa

            int aux = 0;
            char opcao = 0;
            NumeroComplexo a1 = new NumeroComplexo();

            do {
                System.out.println("\nSelecione uma operação | / | * | + | - | Comparar | Imprimir | Parar :");
                aux = (int) teclado.next().charAt(opcao);
                if (aux > 97)
                    aux -= 32;

                switch (aux) {
                    // Divisão
                    case 47:
                        System.out.println("Divisao selecionada \nInsira um valor para o denominador: ");
                        real = teclado.nextDouble();
                        imaginario = teclado.nextDouble();

                        a1.InicializaNumero(real, imaginario);
                        NumC.divisao(a1);

                        aux = 1;

                        break;
                    // Multiplicação
                    case 42:
                        System.out.println("Multiplicacao selecionada \nInsira um valor para a operacao: ");
                        real = teclado.nextDouble();
                        imaginario = teclado.nextDouble();

                        a1.InicializaNumero(real, imaginario);
                        NumC.multiplicacao(a1);

                        aux = 2;

                        break;
                    // Soma
                    case 43:
                        System.out.println("Soma selecionada \nInsira um valor para a operacao: ");
                        real = teclado.nextDouble();
                        imaginario = teclado.nextDouble();

                        a1.InicializaNumero(real, imaginario);
                        NumC.soma(a1);

                        aux = 3;

                        break;
                    // Subtração
                    case 45:
                        System.out.println("Subtracao selecionada \nInsira um valor para a operacao: ");
                        real = teclado.nextDouble();
                        imaginario = teclado.nextDouble();

                        a1.InicializaNumero(real, imaginario);
                        NumC.subtracao(a1);

                        aux = 4;

                        break;

                    // Imprimir
                    case 73:
                        NumC.ImprimeNumero();

                        aux = 5;

                        break;
                    // comparar
                    case 67:
                        System.out.println("Comparacao selecionada \nInsira um valor para comparar: ");
                        real = teclado.nextDouble();
                        imaginario = teclado.nextDouble();

                        a1.InicializaNumero(real, imaginario);
                        NumC.eIgual(a1);

                        aux = 6;

                        break;
                    case 80:
                        aux = 8;
                        break;

                    default:
                        System.out.println("Valor inválido inserido, nada foi computado. \n\n");
                        aux = 7;
                        break;
                }
            } while (aux > 0 && aux < 8);
        }
    }
}
