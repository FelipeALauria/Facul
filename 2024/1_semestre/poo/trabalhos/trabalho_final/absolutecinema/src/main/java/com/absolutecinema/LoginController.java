package com.absolutecinema;

import DAO.GerenteDAO;
import DTO.GerenteDTO;
import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class LoginController {

    @FXML
    private TextField campoNome;
    @FXML
    private PasswordField campoSenha;
    @FXML
    private Button botaoFechar;
    @FXML
    private Label mensagemLogin;
    private GerenteDTO gerente;
    private GerenteDAO gerenteDAO;
    MainscreenController main;

    public void fecharJanela(ActionEvent e) {
        Stage stage = (Stage) botaoFechar.getScene().getWindow();
        stage.close();
    }

    public void VerificarLogin(ActionEvent e) {
        if ((campoNome.getText()).isEmpty()) {
            mensagemLogin.setText("Por favor insira o nome de usuário");
        } else {
            System.out.println(campoNome.getText() + " " + campoSenha.getText());
            ValidarLogin(campoNome.getText(), campoSenha.getText());
        }
    }

    public void ValidarLogin(String loginUsuario, String senhaUsuario) {
        try {
            gerente = new GerenteDTO();
            gerente.setLoginGerente(loginUsuario);
            gerente.setSenhaGerente(senhaUsuario);
            gerenteDAO = new GerenteDAO();
            ResultSet rsUsuarioDAO = gerenteDAO.autenticacaoGerente(gerente);

            if (rsUsuarioDAO != null && rsUsuarioDAO.next()) {
                LoginFeito();
            } else {
                mensagemLogin.setText("Usuário ou Senha Inválida!");
            }

        } catch (SQLException e) {
            mensagemLogin.setText("Erro na Validação");
            e.printStackTrace();
        }

    }

    private void LoginFeito() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("mainscreen.fxml"));
            Parent root = loader.load();
            Scene mainScene = new Scene(root);
            Stage mainStage = new Stage();
            mainStage.setScene(mainScene);
            MainscreenController mainscreenController = loader.getController();
            mainscreenController.mostrarInformacoes(gerente);
            mainStage.initStyle(StageStyle.UNDECORATED);
            mainStage.show();
        } catch (IOException e) {
            mensagemLogin.setText("Erro ao abrir o programa");
            e.printStackTrace();
        } finally {
            Stage loginStage = (Stage) campoNome.getScene().getWindow();
            loginStage.close();
        }
    }
}