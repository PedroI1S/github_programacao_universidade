package Exercicios.Ex_1;

import java.util.Random;

public class Die {

    public Die(){
        SideUp=0;
    }

    private int SideUp;

    public void roll(){
        Random rand = new Random();
        SideUp = rand.nextInt(1, 7);
    }
    
    public int GetSideUp(){
        return SideUp;
    }
}
