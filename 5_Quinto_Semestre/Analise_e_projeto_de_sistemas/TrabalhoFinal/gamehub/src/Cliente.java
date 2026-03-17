import java.util.List;

public class Cliente extends Usuario {
    private BibliotecaDeJogos biblioteca;
    private Carrinho carrinho;

    public Cliente(String nome, String email, String senha) {
        super(nome, email, senha);
        this.biblioteca = new BibliotecaDeJogos();
        this.carrinho = new Carrinho();
    }

    public void avaliarJogo(Jogo jogo, int estrelas, String comentario) {
        if (biblioteca.getJogos().contains(jogo)) {
            Avaliacao avaliacao = new Avaliacao(estrelas, comentario);
            jogo.adicionarAvaliacao(avaliacao);
        } else {
            System.out.println("Você precisa comprar este jogo para avaliá-lo.");
        }
    }

    public void finalizarCompra() {
        Pedido pedido = new Pedido();
        for (Jogo jogo : carrinho.getJogos()) {
            pedido.adicionarJogo(jogo);
            biblioteca.adicionarJogo(jogo);
        }
        System.out.println("Compra finalizada com sucesso!");
        carrinho.esvaziarCarrinho();
    }

    public void verCarrinho() {
        List<Jogo> jogosNoCarrinho = carrinho.getJogos();
        if (jogosNoCarrinho.isEmpty()) {
            System.out.println("Seu carrinho está vazio.");
        } else {
            System.out.println("Jogos no seu carrinho:");
            for (Jogo jogo : jogosNoCarrinho) {
                System.out.println("- " + jogo.getNome());
            }
        }
    }

    public BibliotecaDeJogos getBiblioteca() {
        return biblioteca;
    }

    public Carrinho getCarrinho() {
        return carrinho;
    }
}