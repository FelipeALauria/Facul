package com.mycompany.pessoa;

public class Pessoa {

    public static void main(String[] args) {
     
        Cadastro registry = new Cadastro("Felipe", 21, 123456789);
        
        System.out.println("Name: " + registry.getName());
        System.out.println("Age: " + registry.getAge());
        System.out.println("Social Security Number: " + registry.getSocialSecurityNumber());
        
        registry.setName("Amanda");
        registry.setAge(40);
        registry.setSocialSecurityNumber(123456);
        
        System.out.println();
        
        System.out.println("Name: " + registry.getName());
        System.out.println("Age: " + registry.getAge());
        System.out.println("Social Security Number: " + registry.getSocialSecurityNumber());
    }
}
