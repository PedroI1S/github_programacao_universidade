package Exercicios.Ex_3;

import java.util.Scanner;

public class IntegerSetDemo {
    public static void main(String[] args) {

        try (Scanner teclado = new Scanner(System.in)) {

            int aux = 0;
            IntegerSet in = new IntegerSet();
            IntegerSet a = new IntegerSet();
            int i;

            do {
                System.out.print("Selecione uma operação \n1 - Union \n2 - Intersection \n3 - InsertElement \n4 - deleteElement \n5 - toSetString \n6 - isEqualTo \n7 - Parar \nValor:");
                aux = teclado.nextInt();
                i = 0;

                switch (aux) {
                    case 1:
                        System.out.print("\nOperacao Union selecionada \nInsira um valores para o array ( -1 para parar ):\n");
                        while (i >= 0) {
                            i = teclado.nextInt();
                            if (i < 0) {
                                i = 0;
                                break;
                            }
                            a.insertElement(i);
                        }
                        System.out.println(in.union(a).toSetString());
                        a = new IntegerSet();
                        break;

                    case 2:
                        System.out.print("\nOperacao Intersection selecionada \nInsira um valores para o array ( -1 para parar ):");
                        while (i >= 0) {
                            i = teclado.nextInt();
                            if (i < 0) {
                                i = 0;
                                break;
                            }
                            a.insertElement(i);
                        }
                        System.out.println(in.intersection(a).toSetString());
                        a = new IntegerSet();
                        break;

                    case 3:
                        System.out.print("\nInsira um valores para adicionar ao array ( -1 para parar ):\n");
                        while (i >= 0) {
                            i = teclado.nextInt();
                            if (i < 0) {
                                i = 0;
                                break;
                            }
                            in.insertElement(i);
                        }
                        break;

                    case 4:
                        System.out.print("\nInsira um valores para remover do array ( -1 para parar ):\n");
                        while (i >= 0) {
                            i = teclado.nextInt();
                            if (i < 0) {
                                i = 0;
                                break;
                            }
                            in.removeElement(i);
                        }
                        break;

                    case 5:
                        System.out.println(in.toSetString() + "\n\n");

                        break;

                    case 6:
                        System.out.print("\nOperacao IsEqual selecionada \nInsira um valores para o array ( -1 para parar ):\n");
                        while (i >= 0) {
                            i = teclado.nextInt();
                            if (i < 0) {
                                i = 0;
                                break;
                            }
                            a.insertElement(i);
                        }
                        if(in.isEqualTo(a))
                            System.out.println("Eh igual\n");
                        else
                            System.out.println("Nao eh igual\n");

                        a = new IntegerSet();
                        break;
                }
            } while (aux < 7 && aux > 0);
        }
    }
}