package Exercicios.Ex_4;

import java.math.BigDecimal;
import java.math.RoundingMode;

public class Rational {

    private int numerador, denominador;

    private void Reduzir(int num, int den) {
        for (int i = 9; i > 1; i--) {
            if (num % i == 0) {
                if (den % i == 0) {
                    den /= i;
                    num /= i;
                    i=9;
                }
            }
        }
        numerador = num;
        denominador = den;
    }

    public Rational(int num, int den) {
        Reduzir(num, den);
    }

    public void Sum(int num, int den) {
        Reduzir(numerador * den + num * denominador, denominador * den);
    }

    public void Sub(int num, int den) {
        Reduzir(numerador * den - num * denominador, denominador * den);
    }

    public void Prod(int num, int den) {
        Reduzir(numerador * num, denominador * den);
    }

    public void Quo(int num, int den) {
        Reduzir(numerador * den, denominador * num);
    }

    public void Imprimir(){
        System.out.println(numerador + "/" + denominador);
    }

    public void ImprimirPonto(int n){
        double ponto = (double)numerador / (double)denominador;
        ponto = BigDecimal.valueOf(ponto)
        .setScale(n, RoundingMode.HALF_UP)
        .doubleValue();

        System.out.println(ponto);
    }
}
