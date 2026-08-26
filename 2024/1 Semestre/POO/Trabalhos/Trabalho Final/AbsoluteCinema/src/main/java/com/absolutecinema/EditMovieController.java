/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import DAO.Conexao;
import java.net.URL;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Win11
 */
public class EditMovieController implements Initializable {

    @FXML
    private Label labelNome;
    @FXML
    private Label labelID;
    @FXML
    private RadioButton botaoDuracao;
    @FXML
    private RadioButton botaoNome;
    @FXML
    private RadioButton botaoSala;
    @FXML
    private RadioButton botaoIngresso;
    @FXML
    private RadioButton botaoDiretor;
    @FXML
    private RadioButton botaoIdioma;
    @FXML
    private RadioButton botaoDescricao;
    @FXML
    private RadioButton botaoHorario;
    @FXML
    private RadioButton botaoValor;
    @FXML
    private TextField campoTexto;
    @FXML
    private Button botaoCancelar;
    PreparedStatement preparedStatement = null;
    ResultSet rs = null;
    private int id;
    private String nome, sqlEditar, sql;
    private Conexao conexao;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        ToggleGroup grupoBotao = new ToggleGroup();

        botaoNome.setToggleGroup(grupoBotao);
        botaoNome.setOnAction(event -> {
            campoTexto.setPromptText("Digite o nome do filme");
        });

        botaoIdioma.setToggleGroup(grupoBotao);
        botaoIdioma.setOnAction(event -> {
            campoTexto.setPromptText("Digite o idioma do filme");
        });

        botaoDuracao.setToggleGroup(grupoBotao);
        botaoDuracao.setOnAction(event -> {
            campoTexto.setPromptText("Digite a duração do filme");
        });
        
        botaoSala.setToggleGroup(grupoBotao);
        botaoSala.setOnAction(event -> {
            campoTexto.setPromptText("Digite as salas de exibição do filme");
        });
        
        botaoIngresso.setToggleGroup(grupoBotao);
        botaoIngresso.setOnAction(event -> {
            campoTexto.setPromptText("Digite a quantidade de ingressos do filme");
        });
        
        botaoDiretor.setToggleGroup(grupoBotao);
        botaoDiretor.setOnAction(event -> {
            campoTexto.setPromptText("Digite o diretor do filme");
        });

        botaoDescricao.setToggleGroup(grupoBotao);
        botaoDescricao.setOnAction(event -> {
            campoTexto.setPromptText("Digite a descrição do filme");
        });

        botaoHorario.setToggleGroup(grupoBotao);
        botaoHorario.setOnAction(event -> {
            campoTexto.setPromptText("Digite o horário do filme");
        });

        botaoValor.setToggleGroup(grupoBotao);
        botaoValor.setOnAction(event -> {
            campoTexto.setPromptText("Digite o valor do ingresso do filme");
        });
    }

    public void carregarFilme(String sql, String parametros) {
        this.sql = sql;
        if (sql != null) {
            try {
                preparedStatement = (conexao.getConexao()).prepareStatement(sql);
                preparedStatement.setString(1, parametros);
                rs = preparedStatement.executeQuery();
                if (rs.next()) {
                    id = rs.getInt("id");
                    nome = rs.getString("nome");
                }
            } catch (SQLException e) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Erro");
                alert.setHeaderText("Ocorreu um erro ao acessar o banco de dados");
                alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
                alert.setOnCloseRequest(event -> {
                    Platform.exit();
                });
                alert.showAndWait();
            } finally {
                labelNome.setText(nome);
                labelID.setText(Integer.toString(id));
            }
        } else {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Edição Incorreta");
            alert.setHeaderText("Impossível realizar a edição");
            alert.setContentText("Por favor pesquise o funcionário do qual deseja editar");
            ButtonType closeButton = new ButtonType("Fechar");
            alert.getButtonTypes().setAll(closeButton);
            alert.setOnCloseRequest(event -> {
                event.consume();
            });
            alert.showAndWait();
        }
    }

    public void editarFilme(ActionEvent evento) {
        String parametro1 = null, parametro2 = null;
        int linhasAfetadas = 0;
        if (botaoNome.isSelected()) {
            sql = "UPDATE catalogodefilmes SET nome = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoIdioma.isSelected()) {
            sql = "UPDATE catalogodefilmes SET idioma = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoDuracao.isSelected()) {
            sql = "UPDATE catalogodefilmes SET duracaofilme = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoSala.isSelected()) {
            sql = "UPDATE catalogodefilmes SET saladeexibicao = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoIngresso.isSelected()) {
            sql = "UPDATE catalogodefilmes SET totaldeingressos = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoDiretor.isSelected()) {
            sql = "UPDATE catalogodefilmes SET diretor = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoDescricao.isSelected()) {
            sql = "UPDATE catalogodefilmes SET descricao = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoHorario.isSelected()) {
            sql = "UPDATE catalogodefilmes SET horariodeexibicao = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoValor.isSelected()) {
            sql = "UPDATE catalogodefilmes SET valordosingressos = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        }


        try {
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            preparedStatement.setString(1, parametro1);
            preparedStatement.setString(2, parametro2);
            linhasAfetadas = preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o banco de dados");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.showAndWait();
        } finally {
            if (linhasAfetadas > 0) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Sucessos");
                alert.setHeaderText("A edição foi realizada com sucesso");
                alert.showAndWait();
            } else {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Erro");
                alert.setHeaderText("A edição não foi realizada");
                alert.setContentText("Entre em contato com a assistência técnica");
                alert.showAndWait();
            }

        }
    }

    public void cancelarOperacao(ActionEvent event) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }
}
