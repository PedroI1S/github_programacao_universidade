import java.util.ArrayList;
import java.util.List;

public class Catalogo {
    private List<Jogo> jogos;

    public Catalogo() {
        this.jogos = new ArrayList<>();
    }

    public void adicionarJogo(Jogo jogo) {
        this.jogos.add(jogo);
    }

    public void removerJogo(Jogo jogo) {
        this.jogos.remove(jogo);
    }

    public Jogo buscarPorGenero(String genero) {
        return null;
    }
}