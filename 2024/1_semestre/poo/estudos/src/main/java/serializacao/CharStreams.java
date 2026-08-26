package Serializacao;

import javax.swing.*;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class CharStreams {
    public static void main(String[] args) {

        try {
            FileReader ler = new FileReader("C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\POO\\Estudos\\src\\main\\java\\Serializacao\\Arquivo.txt");
            FileWriter escrever = new FileWriter("C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\POO\\Estudos\\src\\main\\java\\Serializacao\\Arquivo2.txt");
            int c;
            while((c = ler.read()) != -1) {
                escrever.write(c);
            }
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Arquivo irmão" + e.getMessage());
        }
    }
}
