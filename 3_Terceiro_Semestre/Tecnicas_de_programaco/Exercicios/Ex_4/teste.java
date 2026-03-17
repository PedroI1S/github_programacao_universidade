package Exercicios.Ex_4;

import java.math.BigDecimal;
import java.math.RoundingMode;

public class teste {

    public static void main(String[] args) {
        int numerador, denominador;
        int num, den;

        numerador = 2;
        denominador = 3;

        num = 3;
        den = 4;

        numerador = numerador * den - num * denominador;
        denominador *= den;

        System.out.println(numerador + "/" + denominador);

        double ponto = (double)numerador / (double)denominador;
        ponto = BigDecimal.valueOf(ponto)
        .setScale(3, RoundingMode.HALF_UP)
        .doubleValue();

        System.err.println(ponto);
    }
}
