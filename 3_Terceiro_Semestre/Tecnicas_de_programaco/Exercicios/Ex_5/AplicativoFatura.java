package Exercicios.Ex_5;

public class AplicativoFatura {
    public static void main(String[] args) {
        Fatura fatura1 = new Fatura("001", "Martelo", 2, 15.99);
        
        System.out.println("Número de peça: " + fatura1.getNumeroDePeca());
        System.out.println("Descrição da peça: " + fatura1.getDescricaoDaPeca());
        System.out.println("Quantidade: " + fatura1.getQuantidade());
        System.out.println("Preço por item: " + fatura1.getPrecoPorItem());
        
        System.out.println("Valor da fatura: " + fatura1.obterValorFatura());
        
        fatura1.setQuantidade(3);
        fatura1.setPrecoPorItem(20.49);
        
        System.out.println("Valor da fatura atualizado: " + fatura1.obterValorFatura());
    }
}

