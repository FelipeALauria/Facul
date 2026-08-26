package com.mycompany.aula4;

public class Predio {
    int quantidadePredio;
    Andar andar;
    Andar.Sala sala;
    
    public Predio(int quantidadePredio, Andar andar, Andar.Sala sala){
        this.quantidadePredio = quantidadePredio;
        this.andar = new Andar(quantidadePredio, andar, sala);
    }
 
    //Classe Andar
    public class Andar{
        int quantidadeAndar;
        Sala sala;
        Andar andar;
         
        public Andar(int quantidadeAndar, Andar andar, Sala sala){
                this.quantidadeAndar = quantidadeAndar;
                this.andar = andar;
                this.sala = new Sala(quantidadeAndar, sala);
        }
       
       public Andar getAndar(){
           return andar;
       }
       
        public void setAndar(Andar andar){
           this.andar = andar;
       }
        
        //Classe Sala
         public class Sala{
            int quantidadeSala;
            Sala sala;
            
            public Sala(int quantidadeSala, Sala sala){
                this.quantidadeSala = quantidadeSala;
                this.sala = sala;
            }
            
            public Sala getSala(){
                return sala;
            }
            
            public void setSala(Sala sala){
                this.sala = sala;
            }
         }    
    }
    
    public int getPredio(){
        return quantidadePredio;
    }
    
    public void setPredio(int quantidadePredio){
        this.quantidadePredio = quantidadePredio;
    }
}
