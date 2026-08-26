package com.mycompany.teste1;

public class Teste2 {
    int variavel;
    int variavel2;
    public Teste2(int variavel, int variavel2){
        this.variavel = variavel; 
        this.variavel2 = variavel2;
    }
    
    public int getVariavel(){
        return variavel;
    }
    
    public int getVariavel2(){
        return variavel2;
    }
    
    public void setVariaveis(int variavel, int variavel2){
        this.variavel = variavel;
        this.variavel2 = variavel2;
    }
    
    public int somatory(int variavel, int variavel2){
        return (variavel + variavel2);
    }     
}
    

