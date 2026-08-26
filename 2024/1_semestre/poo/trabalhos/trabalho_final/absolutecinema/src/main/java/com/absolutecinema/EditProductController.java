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
public class EditProductController implements Initializable {

    @FXML
    private Label labelNome;
    @FXML
    private Label labelID;
    @FXML
    private RadioButton botaoCaloria;
    @FXML
    private RadioButton botaoNome;
    @FXML
    private RadioButton botaoEstoque;
    @FXML
    private RadioButton botaoValor;
    @FXML
    private RadioButton botaoDescricao;
    @FXML
    private RadioButton botaoCusto;
    @FXML
    private TextField campoTexto;
    @FXML
    private Button botaoCancelar;
    PreparedStatement preparedStatement = null;
    ResultSet rs = null;
    private int id;
    private String nome, sql;
    private Conexao conexao;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        ToggleGroup grupoBotao = new ToggleGroup();

        botaoNome.setToggleGroup(grupoBotao);
        botaoNome.setOnAction(event -> {
            campoTexto.setPromptText("Digite o nome do produto");
        });

        botaoEstoque.setToggleGroup(grupoBotao);
        botaoEstoque.setOnAction(event -> {
            campoTexto.setPromptText("Digite o estoque do produto");
        });

        botaoCaloria.setToggleGroup(grupoBotao);
        botaoCaloria.setOnAction(event -> {
            campoTexto.setPromptText("Digite a caloria do produto");
        });

        botaoValor.setToggleGroup(grupoBotao);
        botaoValor.setOnAction(event -> {
            campoTexto.setPromptText("Digite o valor do produto");
        });

        botaoCaloria.setToggleGroup(grupoBotao);
        botaoCaloria.setOnAction(event -> {
            campoTexto.setPromptText("Digite as calorias do produto");
        });

        botaoCusto.setToggleGroup(grupoBotao);
        botaoCusto.setOnAction(event -> {
            campoTexto.setPromptText("Digite o custo do produto");
        });
    }

    public void carregarProduto(String sql, String parametros) {
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

    public void editarProduto(ActionEvent evento) {
        String parametro1 = null, parametro2 = null;
        int linhasAfetadas = 0;
        if (botaoNome.isSelected()) {
            sql = "UPDATE produtosbomboniere SET nome = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoEstoque.isSelected()) {
            sql = "UPDATE produtosbomboniere SET totalemestoque = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoValor.isSelected()) {
            sql = "UPDATE produtosbomboniere SET valordosprodutos = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoCaloria.isSelected()) {
            sql = "UPDATE produtosbomboniere SET caloria = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoDescricao.isSelected()) {
            sql = "UPDATE produtosbomboniere SET descricao = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
        } else if (botaoCusto.isSelected()) {
            sql = "UPDATE produtosbomboniere SET custo = ? WHERE id = ?";
            parametro1 = campoTexto.getText();
            parametro2 = Integer.toString(id);
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
    }

    public void cancelarOperacao (ActionEvent evt) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }

}
