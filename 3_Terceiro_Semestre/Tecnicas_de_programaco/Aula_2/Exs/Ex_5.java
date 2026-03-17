package Aula_2.Exs;
import java.util.Random;

public class Ex_5 {
    public static void main(String[] args) {

        Random rand = new Random();
        int[] vet = new int[10];
        int i, troca, j;

        for(i=0; i<10; i++){
            vet[i] = rand.nextInt(21);
        }

        for(i=0; i<10; i++){
            for(j=0; j<i; j++){
                if(vet[j] > vet[i]){
                    troca = vet[i];
                    vet[i] = vet[j];
                    vet[j] = troca;
                    //j=0;
                }
            }
        }

        for(i=0; i<10; i++){
            System.out.print(vet[i] + " ");
        }
    }
}