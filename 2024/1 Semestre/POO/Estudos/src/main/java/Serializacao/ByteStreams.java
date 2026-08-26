package Serializacao;

import javax.swing.*;
import java.io.*;

public class ByteStreams {
    public static void main(String[] args) {
        FileInputStream in = null;
        FileOutputStream out = null;

        try {
            in = new FileInputStream("C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\POO\\Estudos\\src\\main\\java\\Serializacao\\Arquivo.txt");
            out = new FileOutputStream("C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\POO\\Estudos\\src\\main\\java\\Serializacao\\Arquivo2.txt");
            int c;
            while ((c = in.read()) != -1) {
                out.write(c);
            }
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Arquivo irmão" + e.getMessage());
        }
    }
}
