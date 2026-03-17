package Exercicios.Ex_10;

import java.util.ArrayList;
import java.util.List;

public class Anexo {
    private List<DocumentoAnexo> documentos;

    public Anexo() {
        this.documentos = new ArrayList<>();
    }

    public void addDocumento(String tipo, String nome, int tamanho) {
        documentos.add(new DocumentoAnexo(tipo, nome, tamanho));
    }

    public List<DocumentoAnexo> getDocumentos() {
        return documentos;
    }

    @Override
    public String toString() {
        if (documentos.isEmpty()) {
            return "Nenhum anexo.";
        }
        
        StringBuilder anexosStr = new StringBuilder("Anexos:");
        for (DocumentoAnexo doc : documentos) {
            anexosStr.append("\n - ").append(doc.toString());
        }
        return anexosStr.toString();
    }
}

class DocumentoAnexo {
    private String tipo;
    private String nome;
    private int tamanho;

    public DocumentoAnexo(String tipo, String nome, int tamanho) {
        this.tipo = tipo;
        this.nome = nome;
        this.tamanho = tamanho;
    }

    @Override
    public String toString() {
        return "Tipo: " + tipo + ", Nome: " + nome + ", Tamanho: " + tamanho + " KB";
    }
}
