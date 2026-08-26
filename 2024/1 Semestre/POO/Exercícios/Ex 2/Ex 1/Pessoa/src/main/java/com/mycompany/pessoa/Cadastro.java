package com.mycompany.pessoa;

public class Cadastro {
    private String name;
    private int age;
    private long socialSecurityNumber;
    
    public Cadastro(String name, int age, long socialSecurityNumber){
        this.name = name;
        this.age = age;
        this.socialSecurityNumber = socialSecurityNumber;
    }
    
    public String getName(){
        return name;
    }
    
    public void setName(String name){
        this.name = name;
    }
    
    public int getAge(){
        return age;
    }
    
    public void setAge(int age){
        this.age = age;
    }
    
    public long getSocialSecurityNumber(){
        return socialSecurityNumber;
    }
   
    public void setSocialSecurityNumber(long socialSecurityNumber){
        this.socialSecurityNumber = socialSecurityNumber;
    }
    
}
    

