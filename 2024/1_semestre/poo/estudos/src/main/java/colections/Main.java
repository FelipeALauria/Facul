package Colections;

import java.util.*;

public class Main {
    public static void main(String[] args) {
        List<Pessoa> lista = new ArrayList<>();

        Pessoa bruna = new Pessoa("Bruna", "123.456.789-10", "Jamaica");
        Pessoa felipe = new Pessoa("DJuana", "098.765.432-11", "Crazy Bitch Land");
        Pessoa andre = new Pessoa("Andre", "147258369-33", "Jamaica");
        Pessoa maisuma = new Pessoa("Sla", "aaa", "EUA");
        Pessoa zebra = new Pessoa("Zebra", "654367892-10", "Jamaica");

        lista.add(bruna);
        lista.add(felipe);
        lista.add(andre);
        lista.add(maisuma);
        lista.add(zebra);

        System.out.println("Antes de Ordenar:");

        for(Pessoa pessoa : lista) {
            System.out.println(pessoa.getNome());
        }

        Collections.sort(lista);

        System.out.println();
        System.out.println("Apos Ordenar:");

        for(Pessoa pessoa : lista) {
            System.out.println(pessoa.getNome());
        }
    }
}