package org.example;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        JFrame tela = new JFrame();
        Janela janela = new Janela();

        tela.add(janela);
        tela.setSize(500, 500);
        tela.setVisible(true);
        tela.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        tela.setTitle("Estudos");
    }
}