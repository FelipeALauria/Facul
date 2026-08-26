package com.mycompany.teste1;

import java.util.Scanner;

public class Teste1 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        Teste2 test = new Teste2(0, 0);
        
        System.out.println(test.getVariavel());
        System.out.println(test.getVariavel2());
        
        int novaVariavel = sc.nextInt();
        int novaVariavel2 = sc.nextInt();
        
        test.setVariaveis(novaVariavel, novaVariavel2);
        
        System.out.println(test.getVariavel());
        System.out.println(test.getVariavel2());
        
        System.out.println(test.somatory(novaVariavel, novaVariavel2));
    }
}
