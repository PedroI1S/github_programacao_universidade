public class Administrador extends Usuario {

    public Administrador(String nome, String email, String senha) {
        super(nome, email, senha);
    }

    public void gerenciarCatalogo(String operacao, Catalogo catalogo, Jogo jogo) {
        switch (operacao.toLowerCase()) {
            case "adicionar":
                catalogo.adicionarJogo(jogo);
                break;
            case "remover":
                catalogo.removerJogo(jogo);
                break;
        }
    }
}