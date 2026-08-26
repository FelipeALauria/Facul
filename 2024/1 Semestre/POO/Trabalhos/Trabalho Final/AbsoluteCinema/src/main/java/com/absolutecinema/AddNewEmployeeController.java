/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import java.net.URL;
import java.util.Objects;
import java.util.ResourceBundle;

import DAO.FuncionarioBomboniereDAO;
import DAO.FuncionarioCinemaDAO;
import DAO.FuncionarioDAO;
import DTO.FuncionarioBomboniereDTO;
import DTO.FuncionarioCinemaDTO;
import DTO.FuncionarioDTO;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Win11
 */
public class AddNewEmployeeController implements Initializable {

    @FXML
    TextField campoNome;
    @FXML
    TextField campoCPF;
    @FXML
    TextField campoSalario;
    @FXML
    TextField campoEscala;
    @FXML
    TextField campoMeta;
    @FXML
    ChoiceBox campoArea;
    @FXML
    ChoiceBox campoFaxina;
    @FXML
    Button botaoCancelar;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        campoArea.getItems().addAll("Bomboniere", "Cinema");
        campoFaxina.getItems().addAll("Sim", "Não");

        campoMeta.setVisible(false);
        campoMeta.visibleProperty().bind(campoArea.valueProperty().isEqualTo("Bomboniere"));

        campoFaxina.setVisible(false);
        campoFaxina.visibleProperty().bind(campoArea.valueProperty().isEqualTo("Cinema"));
    }

    public void cancelarOperacao(ActionEvent event) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }
    
    public void adicionarFuncionario(){
        if(((String)campoArea.getValue()).equals("Cinema")){
            FuncionarioDTO funcionario = new FuncionarioCinemaDTO();
            funcionario.setNomeCompleto(campoNome.getText());
            funcionario.setCpf(campoCPF.getText());
            Object area = campoArea.getValue();
            String areaa = area.toString();
            funcionario.setVinculoEmpregativo(areaa);
            funcionario.setSalarioHora(Double.parseDouble(campoSalario.getText()));
            funcionario.setCargaHoraria(Integer.parseInt(campoEscala.getText()));
            Object faxina = campoFaxina.getValue();
            String faxinaa = (String) faxina;
            ((FuncionarioCinemaDTO)funcionario).setFaxina(faxinaa);
            FuncionarioDAO funcionarioDAO = new FuncionarioCinemaDAO();
            funcionarioDAO.contratarFuncionario(funcionario);
        }
        else if(((String)campoArea.getValue()).equals("Bomboniere")){
            FuncionarioDTO funcionario = new FuncionarioBomboniereDTO();
            funcionario.setNomeCompleto(campoNome.getText());
            funcionario.setCpf(campoCPF.getText());
            Object area = campoArea.getValue();
            String areaa = area.toString();
            funcionario.setVinculoEmpregativo(areaa);
            funcionario.setSalarioHora(Double.parseDouble(campoSalario.getText()));
            funcionario.setCargaHoraria(Integer.parseInt(campoEscala.getText()));
            ((FuncionarioBomboniereDTO)funcionario).setMeta(Double.parseDouble(campoMeta.getText()));
            FuncionarioDAO funcionarioDAO = new FuncionarioBomboniereDAO();
            funcionarioDAO.contratarFuncionario(funcionario);
        }
    }
}