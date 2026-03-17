package Exercicios.Ex_9;

import java.util.Scanner;

public class usaEmail {
    public static void main(String[] args) {
        try (Scanner teclado = new Scanner(System.in)) {
            int ativo = 0;

            while (true) {
                System.err.println("1. Fazer login \n2. Sair do programa");
                ativo = teclado.nextInt();

                if (ativo == 1) {
                    teclado.nextLine();
                    System.out.print("Nome de Usuário: ");
                    user = teclado.nextLine();
                    System.out.println();
                    

                    while (true){
                        int aux = 5, posicao =0;
                        System.out.println("1. Escrever um e-mail \n2. Listar os e-mails \n3. Ler um e-mail \n4. Excluir um e-mail \n5. Fazer logout");
                        aux = teclado.nextInt();
                        teclado.nextLine();

                        String destinatario, assunto, mensagem;

                        switch(aux){
                            case 1:
                                System.out.println("Destinatário:");
                                destinatario = teclado.nextLine();

                                System.out.println("Assunto:");
                                assunto = teclado.nextLine();

                                System.out.println("Mensagem: ");
                                mensagem = teclado.nextLine();

                                escrever_email(destinatario, assunto, mensagem);
                                break;
                            
                            case 2:
                                listar_emails();
                                break;

                            case 3:
                                posicao = 10;
                                System.out.println("Insira a posição do e-mail desejado:");
                                posicao = teclado.nextInt();
                                if(posicao != 10)
                                    ler_email(posicao);

                                break;

                            case 4:
                                posicao = 10;
                                System.out.println("Insira a posição do e-mail desejado:");
                                posicao = teclado.nextInt();
                                if(posicao != 10)
                                    excluir_email(posicao);

                                break;
                        }

                        if(aux>= 5){
                            break;
                        }

                    }
                }
                else{
                    break;
                }
            }
        }
    }
    
    private static String user;
    private static email[] list = new email[10];

    public static void escrever_email(String para, String assunto, String mensagem){
        int i = 0;
        for(i = 0; i<10; i++){
            if(list[i] == null){
                list[i] = new email(user, para, assunto, mensagem);
                i=100;
            }
        }
        if(i == 10){
            System.out.println("\nSEM ESPAÇO NA CAIXA, EXCLUA UM E-MAIL");
        }
    }

    public static void listar_emails(){
        for(int i = 0; i<10; i++){
            if(list[i] != null && (user.equals(list[i].getDestinatario()) || user.equals(list[i].getRemetente()))){
                System.out.println( "\n" + (i+1) + list[i].getList());
            }
        }
    }

    public static void ler_email(int i){
        if( list[i-1] != null && user.equals(list[i-1].getDestinatario())){
            System.out.println(list[i-1].toString());
        }
        else
            System.out.println("E-mail não encontrado");
    }

    public static void excluir_email(int i){
        boolean aux = false;
        if(list[i-1] != null && user.equals(list[i-1].getRemetente())){
            list[i-1] = null;
            aux = true;
        }
        if(aux == false){
            System.out.println("E-mail não encontrado");
        }
    }
    
}
