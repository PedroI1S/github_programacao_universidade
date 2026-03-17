package Exercicios.Ex_10;

public class Email {
    private String de;
    private String para;
    private String assunto;
    private String mensagem;
    private Anexo anexo;
    private Data data;

    public Email(String de, String para, String assunto, String mensagem, Data data) {
        this.de = de;
        this.para = para;
        this.assunto = assunto;
        this.mensagem = mensagem;
        this.anexo = new Anexo();
        this.data = data;
    }

    public String getDe() {
        return de;
    }

    public String getPara() {
        return para;
    }

    public String getAssunto() {
        return assunto;
    }

    public String getMensagem() {
        return mensagem;
    }

    public Data getData() {
        return data;
    }

    public Anexo getAnexo() {
        return anexo;
    }

    @Override
    public String toString() {
        StringBuilder emailStr = new StringBuilder();
        emailStr.append("De: ").append(de)
                .append("\nPara: ").append(para)
                .append("\nAssunto: ").append(assunto)
                .append("\nMensagem: ").append(mensagem)
                .append("\nData: ").append(data != null ? data.porExtenso() : "Sem data")
                .append("\n").append(anexo.toString());
        return emailStr.toString();
    }
}
