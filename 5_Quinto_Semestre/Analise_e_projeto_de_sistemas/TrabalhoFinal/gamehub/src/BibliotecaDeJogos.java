import java.util.ArrayList;
import java.util.List;

public class BibliotecaDeJogos {
    private List<Jogo> jogos;

    public BibliotecaDeJogos() {
        this.jogos = new ArrayList<>();
    }

    public void adicionarJogo(Jogo jogo) {
        this.jogos.add(jogo);
    }

    public List<Jogo> getJogos() {
        return jogos;
    }
}