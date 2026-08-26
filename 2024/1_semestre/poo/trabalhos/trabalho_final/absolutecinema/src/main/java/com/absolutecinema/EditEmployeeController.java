/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import DAO.Conexao;
import DTO.FuncionarioBomboniereDTO;
import DTO.FuncionarioCinemaDTO;
import java.net.URL;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.collections.ObservableList;
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
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Win11
 */
public class EditEmployeeController implements Initializable {

    @FXML
    private Label labelNome;
    @FXML
    private Label labelID;
    @FXML
    private RadioButton botaoMeta;
    @FXML
    private RadioButton botaoNome;
    @FXML
    private RadioButton botaoSalario;
    @FXML
    private RadioButton botaoEscala;
    @FXML
    private RadioButton botaoCLT;
    @FXML
    private RadioButton botaoFaxina;
    @FXML
    private TextField campoTexto;
    @FXML
    private ChoiceBox campoChoice;
    @FXML
    private Button botaoCancelar;
    PreparedStatement preparedStatement = null;
    ResultSet rs = null;
    private int id;
    private String nome, sql;
    private Conexao conexao;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        if (sql.contains("funcionarioscinema")) {
            botaoFaxina.setVisible(true);
            botaoMeta.setVisible(false);
        }
        if (sql.contains("funcionariosbomboniere")) {
            botaoFaxina.setVisible(false);
            botaoMeta.setVisible(true);
        }

        ToggleGroup grupoBotao = new ToggleGroup();

        botaoNome.setToggleGroup(grupoBotao);
        botaoNome.setOnAction(event -> {
            campoChoice.setVisible(false);
            campoTexto.setVisible(true);
            campoTexto.setPromptText("Digite o nome do funcionário");
        });

        botaoSalario.setToggleGroup(grupoBotao);
        botaoSalario.setOnAction(event -> {
            campoChoice.setVisible(false);
            campoTexto.setVisible(true);
            campoTexto.setPromptText("Digite o salario do funcionário");
        });

        botaoEscala.setToggleGroup(grupoBotao);
        botaoEscala.setOnAction(event -> {
            campoChoice.setVisible(false);
            campoTexto.setVisible(true);
            campoTexto.setPromptText("Digite a escala do funcionário");
        });
        botaoCLT.setToggleGroup(grupoBotao);
        botaoCLT.setOnAction(event -> {
            campoChoice.setVisible(true);
            campoTexto.setVisible(false);
            campoChoice.getItems().addAll("Sim", "Não");
        });
        botaoFaxina.setToggleGroup(grupoBotao);
        botaoFaxina.setOnAction(event -> {
            campoChoice.setVisible(true);
            campoTexto.setVisible(false);
            campoChoice.getItems().addAll("Sim", "Não");
        });
        botaoMeta.setToggleGroup(grupoBotao);
        botaoMeta.setOnAction(event -> {
            campoChoice.setVisible(false);
            campoTexto.setVisible(true);
            campoTexto.setPromptText("Digite a meta do funcionário");
        });
    }

    public void carregarFuncionario(String sql, String parametros) {
        this.sql = sql;
        if (sql != null) {
            try {
                preparedStatement = (conexao.getConexao()).prepareStatement(sql);
                preparedStatement.setString(1, parametros);
                preparedStatement.setString(2, parametros);
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

    public void editarFuncionario(ActionEvent evento) {
        String parametro1 = null, parametro2 = null;
        int linhasAfetadas = 0;
        if (botaoFaxina.isVisible()) {
            if (botaoNome.isSelected()) {
                sql = "UPDATE funcionarioscinema SET nomeCompleto = ? WHERE id = ?";
                parametro1 = campoTexto.getText();
                parametro2 = Integer.toString(id);
            } else if (botaoSalario.isSelected()) {
                sql = "UPDATE funcionarioscinema SET salarioHora = ? WHERE id = ?";
                parametro1 = campoTexto.getText();
                parametro2 = Integer.toString(id);
            } else if (botaoEscala.isSelected()) {
                sql = "UPDATE funcionarioscinema SET horarioDeTrabalho = ? WHERE id = ?";
                parametro1 = campoTexto.getText();
                parametro2 = Integer.toString(id);
            } else if (botaoCLT.isSelected()) {
                sql = "UPDATE funcionarioscinema SET vinculoEmpregativo = ? WHERE id = ?";
                parametro1 = (String) campoChoice.getValue();
                parametro2 = Integer.toString(id);
            } else if (botaoFaxina.isSelected()) {
                sql = "UPDATE funcionarioscinema SET faxina = ? WHERE id = ?";
                parametro1 = (String) campoChoice.getValue();
                parametro2 = Integer.toString(id);
            }
        } else {
            if (botaoNome.isSelected()) {
                sql = "UPDATE funcionariosbomboniere SET nomeCompleto = ? WHERE id = ?";
                parametro1 = campoTexto.getText();
                parametro2 = Integer.toString(id);
            } else if (botaoSalario.isSelected()) {
                sql = "UPDATE funcionariosbomboniere SET salarioHora = ? WHERE id = ?";
                parametro1 = campoTexto.getText();
                parametro2 = Integer.toString(id);
            } else if (botaoEscala.isSelected()) {
                sql = "UPDATE funcionariosbomboniere SET horarioDeTrabalho = ? WHERE id = ?";
                parametro1 = campoTexto.getText();
                parametro2 = Integer.toString(id);
            } else if (botaoCLT.isSelected()) {
                sql = "UPDATE funcionariosbomboniere SET vinculoEmpregativo = ? WHERE id = ?";
                parametro1 = (String) campoChoice.getValue();
                parametro2 = Integer.toString(id);
            } else if (botaoMeta.isSelected()) {
                sql = "UPDATE funcionarioscinema SET meta = ? WHERE id = ?";
                parametro1 = campoTexto.getText();
                parametro2 = Integer.toString(id);
            }
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
