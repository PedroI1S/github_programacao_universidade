package Exercicios.Ex_5;

public class Fatura {
    private String numeroDePeca;
    private String descricaoDaPeca;
    private int quantidade;
    private double precoPorItem;
    
    public Fatura(String numeroDePeca, String descricaoDaPeca, int quantidade, double precoPorItem) {
        this.numeroDePeca = numeroDePeca;
        this.descricaoDaPeca = descricaoDaPeca;
        setQuantidade(quantidade);
        setPrecoPorItem(precoPorItem);
    }
    
    public String getNumeroDePeca() {
        return numeroDePeca;
    }

    public void setNumeroDePeca(String numeroDePeca) {
        this.numeroDePeca = numeroDePeca;
    }

    public String getDescricaoDaPeca() {
        return descricaoDaPeca;
    }

    public void setDescricaoDaPeca(String descricaoDaPeca) {
        this.descricaoDaPeca = descricaoDaPeca;
    }

    public int getQuantidade() {
        return quantidade;
    }

    public void setQuantidade(int quantidade) {
        if (quantidade > 0) {
            this.quantidade = quantidade;
        } else {
            this.quantidade = 0;
        }
    }

    public double getPrecoPorItem() {
        return precoPorItem;
    }

    public void setPrecoPorItem(double precoPorItem) {
        if (precoPorItem > 0) {
            this.precoPorItem = precoPorItem;
        } else {
            this.precoPorItem = 0;
        }
    }
    
    public double obterValorFatura() {
        return quantidade * precoPorItem;
    }
}
