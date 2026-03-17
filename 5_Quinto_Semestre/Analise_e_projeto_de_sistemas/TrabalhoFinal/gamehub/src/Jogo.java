import java.util.ArrayList;
import java.util.List;

public class Jogo {
    private String codigo;
    private String titulo;
    private String descricao;
    private float preco;
    private List<Avaliacao> avaliacoes;

    public Jogo(String codigo, String titulo, String descricao, float preco) {
        this.codigo = codigo;
        this.titulo = titulo;
        this.descricao = descricao;
        this.preco = preco;
        this.avaliacoes = new ArrayList<>();
    }

    public void adicionarAvaliacao(Avaliacao avaliacao) {
        this.avaliacoes.add(avaliacao);
    }

    public String getCodigo() {
        return codigo;
    }

    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public float getPreco() {
        return preco;
    }

    public void setPreco(float preco) {
        this.preco = preco;
    }

    public String getDescricao() {
        return descricao;
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public String getNome() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'getNome'");
    }
}