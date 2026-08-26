/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import java.net.URL;
import java.util.ResourceBundle;

import DAO.*;
import DTO.*;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author Win11
 */
public class AddNewMovieController implements Initializable {

    @FXML
    TextField campoNome;
    @FXML
    TextField campoIdioma;
    @FXML
    TextField campoSalas;
    @FXML
    TextField campoDuracao;
    @FXML
    TextField campoIngressos;
    @FXML
    TextField campoHorario;
    @FXML
    TextField campoDiretor;
    @FXML
    TextField campoValor;
    @FXML
    TextField campoDescricao;
    @FXML
    Button botaoCancelar;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }

    public void cancelarOperacao(ActionEvent event) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }

    public void adicionarFilme() {
        FilmesDTO filme = new FilmesDTO();
        filme.setNome(campoNome.getText());
        filme.setDescricao(campoDescricao.getText());
        filme.setValor(Double.parseDouble(campoValor.getText()));
        filme.setQuantidadeDeProdutos(Integer.parseInt(campoIngressos.getText()));
        filme.setIdioma(campoIdioma.getText());
        filme.setHorariosDeExibicao(campoHorario.getText());
        filme.setDiretor(campoDiretor.getText());
        filme.setDuracaoDoFilme(Integer.parseInt(campoDuracao.getText()));
        filme.setSalaDeExibicao(Integer.parseInt(campoSalas.getText()));
        ProdutoDAO filmeDAO = new FilmesDAO();
        filmeDAO.adicionarProduto(filme);
    }
}
