package Serializacao;

import javax.swing.*;
import java.io.*;

public class BufferedStreams {
    public static void main(String[] args) {
        try {
            BufferedReader ler = new BufferedReader(new FileReader("C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\POO\\Estudos\\src\\main\\java\\Serializacao\\Arquivo.txt"));
            BufferedWriter escrever = new BufferedWriter(new FileWriter("C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\POO\\Estudos\\src\\main\\java\\Serializacao\\Arquivo2.txt"));
            String c;
            while((c = ler.readLine()) != null){
                escrever.write(c);
                System.out.println((String) c);
            }
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Arquivo irmão" + e.getMessage());
        }
    }

}
