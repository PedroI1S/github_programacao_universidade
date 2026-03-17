package Exercicios.Ex_9;

import java.io.Serializable;

public class Email implements Serializable{
    private String de, para, assunto, mensagem;
    private static final long serialVersionUID = -4497795320043108019L;

    //construtor
    public Email(String de, String para, String assunto, String mensagem){
        this.de = de;
        this.para = para;
        this.assunto = assunto;
        this.mensagem = mensagem;
    }

    public String getRemetente(){
        return this.de;
    }

    public String getDestinatario(){
        return this.para;
    }

    public String toString(){
        return "Remetente: " + this.de + "\nDestinatario: " + this.para + "\nAssunto: " + this.assunto + "\nMensagem: " + this.mensagem;
    }

    public String getList(){
        return "-> De: " + this.de + ", Para: " + this.para + ", " + this.assunto;
    }
}