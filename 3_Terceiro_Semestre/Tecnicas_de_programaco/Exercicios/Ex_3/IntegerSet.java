package Exercicios.Ex_3;

public class IntegerSet{
    private boolean[] integer;
    
    public IntegerSet(){
        integer = new boolean[101];
    }
    
    public boolean isEqualTo(IntegerSet a){
        for(int i = 0; i<101; i++){
            if(integer[i] != a.integer[i]){
                return false;
            }
        }
        return true;
    }
    
    public IntegerSet union(IntegerSet a){
        IntegerSet b = new IntegerSet();
        
        for(int i = 0; i<101; i++){
            if(integer[i] == true || a.integer[i] == true){
                b.integer[i] = true;
            }
        }
        return b;
    }
    
    public IntegerSet intersection(IntegerSet a){
        IntegerSet b = new IntegerSet();
        
        for(int i = 0; i<101; i++){
            if(integer[i] == true && a.integer[i] == true){
                b.integer[i] = true;
            }
        }
        return b;
    }
    
    public void insertElement(int k){
        integer[k]=true;
    }
    
    public void removeElement(int k){
        integer[k]=false;
    }
    
    public String toSetString(){
        String aux = " ";
        for(int i = 0; i<101; i++){
            if(integer[i] == true){
                aux += i + " ";
            }
        }
        if(aux.equals(" "))return "--";
        return aux;
    }
}