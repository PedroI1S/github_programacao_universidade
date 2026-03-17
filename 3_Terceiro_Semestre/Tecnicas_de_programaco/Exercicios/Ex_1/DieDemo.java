package Exercicios.Ex_1;

public class DieDemo {
    
    public static void main(String[] args){
        Die a = new Die();
        Die b = new Die();

        a.roll();
        b.roll();

        System.err.println(a.GetSideUp()+b.GetSideUp());
    }
}
