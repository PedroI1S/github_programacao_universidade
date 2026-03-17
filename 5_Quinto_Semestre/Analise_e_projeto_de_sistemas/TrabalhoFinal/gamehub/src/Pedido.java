import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Pedido {
    private int numeroPedido;
    private Date data;
    private float valor;
    private List<Jogo> jogos;

    public Pedido() {
        this.jogos = new ArrayList<>();
        this.data = new Date();
    }

    public int getNumeroPedido() {
        return numeroPedido;
    }

    public void setNumeroPedido(int numeroPedido) {
        this.numeroPedido = numeroPedido;
    }

    public void adicionarJogo(Jogo jogo) {
        this.jogos.add(jogo);
        this.valor += jogo.getPreco();
    }

    public Date getData() {
        return data;
    }
}