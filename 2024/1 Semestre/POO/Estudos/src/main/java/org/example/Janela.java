package org.example;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Janela extends JPanel implements ActionListener, KeyListener {
    private JButton botao1 = new JButton("Vaca");
    private JButton botao2 = new JButton("Porco");
    private JButton botao3 = new JButton("Galinha");
    private JButton botao4 = new JButton("Cavalo");

    private JLabel pergunta = new JLabel("Qual é o animal da figura?");
    private JLabel label = new JLabel();
    private ImageIcon icon = new ImageIcon("C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\POO\\Estudos\\src\\main\\java\\org\\example\\porco.jpg");

    Color corBotao1 = new Color(170, 99, 70);
    Color corBotao3 = new Color(246, 235, 86);
    Color corBotao2 = new Color(232, 132, 136);
    Color corBotao4 = new Color(34, 31, 31, 255);
    Color corFundo = new Color(55, 6, 6);
    Color corTexto = new Color(46, 92, 79);

    public Janela() {
        this.setLayout(new BorderLayout());

        label.setIcon(icon);
        botao1.setBackground(corBotao1);
        botao1.setForeground(corTexto);
        botao2.setBackground(corBotao2);
        botao2.setForeground(corTexto);
        botao3.setBackground(corBotao3);
        botao3.setForeground(corTexto);
        botao4.setBackground(corBotao4);
        botao4.setForeground(corTexto);

        botao1.addActionListener(this);
        botao2.addActionListener(this);
        botao3.addActionListener(this);
        botao4.addActionListener(this);
        botao1.addKeyListener(this);


        this.setBackground(corFundo);

        JPanel botoesPanel = new JPanel();
        botoesPanel.setBackground(corFundo);
        botoesPanel.add(botao1);
        botoesPanel.add(botao2);
        botoesPanel.add(botao3);
        botoesPanel.add(botao4);

        pergunta.setForeground(corTexto);

        JPanel perguntaPanel = new JPanel();
        perguntaPanel.setBackground(corFundo);
        perguntaPanel.add(pergunta);

        JPanel labelPanel = new JPanel();
        labelPanel.setBackground(corFundo);
        labelPanel.add(label);

        this.add(perguntaPanel, BorderLayout.NORTH);
        this.add(labelPanel, BorderLayout.CENTER);
        this.add(botoesPanel, BorderLayout.SOUTH);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == botao1)
            JOptionPane.showMessageDialog(null, "Errou!");
        else if (e.getSource() == botao2)
            JOptionPane.showMessageDialog(null, "Acertou!");
        else if (e.getSource() == botao3)
            JOptionPane.showMessageDialog(null, "Errou!");
        else if (e.getSource() == botao4)
            JOptionPane.showMessageDialog(null, "Errou!");
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {
        if(e.getKeyCode() == KeyEvent.VK_P){
            JOptionPane.showMessageDialog(null, "Acertou!");
        }
        else {
            JOptionPane.showMessageDialog(null, "Errou!");
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}