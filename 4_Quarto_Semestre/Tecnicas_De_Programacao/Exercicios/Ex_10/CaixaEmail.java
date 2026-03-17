package Exercicios.Ex_10;

import java.util.ArrayList;
import java.util.List;

public class CaixaEmail {
    private List<Email> emails;

    public CaixaEmail() {
        emails = new ArrayList<>();
    }

    public void escreveEmail(Email email) {
        emails.add(email);
    }

    public List<Email> listarEmails(String usuario) {
        List<Email> emailsDoUsuario = new ArrayList<>();
        for (Email email : emails) {
            if (email.getPara().equals(usuario)) {
                emailsDoUsuario.add(email);
            }
        }
        return emailsDoUsuario;
    }

    public Email lerEmail(int posicao) {
        if (posicao >= 0 && posicao < emails.size()) {
            return emails.get(posicao);
        } else {
            System.out.println("E-mail não encontrado.");
            return null;
        }
    }

    public void excluirEmail(int posicao) {
        if (posicao >= 0 && posicao < emails.size()) {
            emails.remove(posicao);
            System.out.println("E-mail excluído com sucesso.");
        } else {
            System.out.println("E-mail não encontrado.");
        }
    }
}
