package Exercicios.Ex_2;

public class NumeroComplexo {
    
    private Double real, imaginario;

    public NumeroComplexo(){
        real = 0.0;
        imaginario = 0.0;
    }

    public NumeroComplexo(double Real){
        real = Real;
        imaginario = 0.0;
    }

    public NumeroComplexo(double Real, double Imaginario){
        real = Real;
        imaginario = Imaginario;  
    }

    public void InicializaNumero(double Real, double Imaginario){
        real = Real;
        imaginario = Imaginario;
    }

    public void ImprimeNumero(){
        System.out.println(real + "+" + imaginario + "i");
    }

    public int eIgual(NumeroComplexo teste){
        if(real == teste.real || imaginario == teste.imaginario)
            return 1;
        else
            return 0;
    }

    public void soma(NumeroComplexo soma){
        real = real + soma.real;
        imaginario = imaginario + soma.imaginario;
    }

    public void subtracao(NumeroComplexo sub){
        real = real - sub.real;
        imaginario =  imaginario - sub.imaginario;
    }

    public void multiplicacao(NumeroComplexo mult){
        double auxR = real, auxI = imaginario;
        real = (auxR * mult.real) - (auxI * mult.imaginario);
        imaginario = (auxR * mult.imaginario) + (auxI * mult.real);
    }

    public void divisao(NumeroComplexo div){
        double auxR = real, auxI = imaginario;
        real = (auxR * div.real + auxI * div.imaginario)/(div.real*div.real + div.imaginario*div.imaginario);
        imaginario = (auxI*div.real - auxR*div.imaginario)/(div.real*div.real + div.imaginario*div.imaginario);
    }
}
