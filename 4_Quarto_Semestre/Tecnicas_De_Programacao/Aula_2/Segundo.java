package Aula_2;

import java.util.Scanner;
import java.util.Random;

public class Segundo {

	public static void main(String[] args) {

		try (Scanner teclado = new Scanner(System.in)) {
			System.out.print("Digite um numero inteiro: ");
			int i = teclado.nextInt();

			System.out.print("Digite um numero real: ");
			double r = teclado.nextDouble();

			System.out.print("Digite uma frase: ");
			String s = teclado.nextLine();
			s = teclado.nextLine();

			System.out.println("\n\ninteiro: " + i + ", real: " + r);
			System.out.println("Frase: " + s);
		}

		Random x = new Random();
		int j = x.nextInt(10);
		System.out.println("\nUm numero inteiro pseudo-aleatoria: " + j);

	}
}
