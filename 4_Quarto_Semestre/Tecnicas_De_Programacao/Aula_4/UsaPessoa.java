package Aula_4;

import java.util.Scanner;

public class UsaPessoa {
    
	public static void main(String[] Args){

        try(Scanner teclado = new Scanner(System.in)){
            int ano;
            String nome, cpf;

            System.out.print("Nome: ");
            nome = teclado.nextLine();
            System.out.print("Cpf: ");
            cpf = teclado.nextLine();
            System.out.print("Ano: ");
            ano = teclado.nextInt();

            Pessoa p = new Pessoa(nome, cpf, ano);
            p.imprimirDados();
        }

	}
    
}
