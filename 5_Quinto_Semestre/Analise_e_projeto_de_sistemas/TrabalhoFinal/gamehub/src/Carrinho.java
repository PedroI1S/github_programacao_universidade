import java.util.ArrayList;
import java.util.List;

public class Carrinho {
    private List<Jogo> jogos;

    public Carrinho() {
        this.jogos = new ArrayList<>();
    }

    public void adicionarJogo(Jogo jogo) {
        if (!jogos.contains(jogo)) {
            this.jogos.add(jogo);
        } else {
            System.out.println("Este jogo já está no carrinho.");
        }
    }

    public void removerJogo(Jogo jogo) {
        this.jogos.remove(jogo);
    }

    public void esvaziarCarrinho() {
        this.jogos.clear();
    }

    public List<Jogo> getJogos() {
        return jogos;
    }
}