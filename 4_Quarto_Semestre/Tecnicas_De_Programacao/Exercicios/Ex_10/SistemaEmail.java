package Exercicios.Ex_10;

import java.util.List;
import java.util.Scanner;

public class SistemaEmail {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        CaixaEmail caixaEmail = new CaixaEmail();
        String usuarioLogado = null;
        
        while (true) {
            System.out.println("1. Fazer login");
            System.out.println("2. Escrever um e-mail");
            System.out.println("3. Listar e-mails");
            System.out.println("4. Ler um e-mail");
            System.out.println("5. Excluir um e-mail");
            System.out.println("6. Fazer logout");
            System.out.println("7. Sair");
            System.out.print("Escolha uma opção: ");
            int opcao = scanner.nextInt();
            scanner.nextLine(); // Consome a nova linha

            switch (opcao) {
                case 1: // Fazer login
                    System.out.print("Digite seu nome para login: ");
                    usuarioLogado = scanner.nextLine();
                    System.out.println("Login realizado como " + usuarioLogado);
                    break;
                
                case 2: // Escrever um e-mail
                    if (usuarioLogado != null) {
                        System.out.print("Destinatário: ");
                        String destinatario = scanner.nextLine();
                        System.out.print("Assunto: ");
                        String assunto = scanner.nextLine();
                        System.out.print("Mensagem: ");
                        String mensagem = scanner.nextLine();
                        
                        // Define a data fixa para o exemplo
                        Data dataAtual = new Data(31, 10, 2024);
                        Email novoEmail = new Email(usuarioLogado, destinatario, assunto, mensagem, dataAtual);

                        // Pergunta ao usuário se deseja adicionar anexos
                        System.out.print("Deseja adicionar anexos? (S/N): ");
                        String respostaAnexo = scanner.nextLine();
                        if (respostaAnexo.equalsIgnoreCase("S")) {
                            System.out.print("Quantos anexos deseja adicionar? ");
                            int quantidadeAnexos = scanner.nextInt();
                            scanner.nextLine(); // Consome a nova linha

                            for (int i = 0; i < quantidadeAnexos; i++) {
                                System.out.print("Tipo do anexo " + (i + 1) + ": ");
                                String tipoAnexo = scanner.nextLine();
                                System.out.print("Nome do documento do anexo " + (i + 1) + ": ");
                                String nomeDocumento = scanner.nextLine();
                                System.out.print("Tamanho do documento (KB) do anexo " + (i + 1) + ": ");
                                int tamanhoDocumento = scanner.nextInt();
                                scanner.nextLine(); // Consome a nova linha

                                novoEmail.getAnexo().addDocumento(tipoAnexo, nomeDocumento, tamanhoDocumento);
                            }
                        }

                        caixaEmail.escreveEmail(novoEmail);
                        System.out.println("E-mail enviado com sucesso!");
                    } else {
                        System.out.println("Faça login para enviar um e-mail.");
                    }
                    break;
                
                case 3: // Listar e-mails
                    if (usuarioLogado != null) {
                        List<Email> emails = caixaEmail.listarEmails(usuarioLogado);
                        System.out.println("E-mails para " + usuarioLogado + ":");
                        for (int i = 0; i < emails.size(); i++) {
                            System.out.println("[" + i + "] " + emails.get(i).getAssunto() + " - " + emails.get(i).getData());
                        }
                    } else {
                        System.out.println("Faça login para listar e-mails.");
                    }
                    break;
                
                case 4: // Ler um e-mail
                    if (usuarioLogado != null) {
                        System.out.print("Digite a posição do e-mail que deseja ler: ");
                        int posicao = scanner.nextInt();
                        scanner.nextLine();
                        Email email = caixaEmail.lerEmail(posicao);
                        if (email != null && email.getPara().equals(usuarioLogado)) {
                            System.out.println(email);
                        } else {
                            System.out.println("E-mail não encontrado ou não pertence a você.");
                        }
                    } else {
                        System.out.println("Faça login para ler e-mails.");
                    }
                    break;
                
                case 5: // Excluir um e-mail
                    if (usuarioLogado != null) {
                        System.out.print("Digite a posição do e-mail que deseja excluir: ");
                        int posicao = scanner.nextInt();
                        scanner.nextLine();
                        Email email = caixaEmail.lerEmail(posicao);
                        if (email != null && email.getPara().equals(usuarioLogado)) {
                            caixaEmail.excluirEmail(posicao);
                        } else {
                            System.out.println("E-mail não encontrado ou não pertence a você.");
                        }
                    } else {
                        System.out.println("Faça login para excluir e-mails.");
                    }
                    break;
                
                case 6: // Fazer logout
                    usuarioLogado = null;
                    System.out.println("Logout realizado.");
                    break;
                
                case 7: // Sair
                    System.out.println("Encerrando o sistema...");
                    scanner.close();
                    return;
                
                default:
                    System.out.println("Opção inválida.");
            }
        }
    }
}
