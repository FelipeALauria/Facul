/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import DAO.*;
import DTO.*;
import java.net.URL;
import java.util.ResourceBundle;
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
public class AddNewProductController implements Initializable {

    @FXML
    TextField campoNome;
    @FXML
    TextField campoEstoque;
    @FXML
    TextField campoDescricao;
    @FXML
    TextField campoValor;
    @FXML
    TextField campoCalorias;
    @FXML
    TextField campoCusto;
    @FXML
    Button botaoCancelar;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
    }

    public void cancelarOperacao(ActionEvent event) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }

    public void adicionarProduto() {
        ProdutoDTO produto = new BomboniereDTO();
        produto.setNome(campoNome.getText());
        produto.setDescricao(campoDescricao.getText());
        produto.setQuantidadeDeProdutos(Integer.parseInt(campoEstoque.getText()));
        produto.setValor(Double.parseDouble(campoValor.getText()));
        ((BomboniereDTO)produto).setCalorias(Integer.parseInt(campoCalorias.getText()));
        ((BomboniereDTO)produto).setCusto(Double.parseDouble(campoCusto.getText()));
        ProdutoDAO produtoDAO = new BomboniereDAO();
        produtoDAO.adicionarProduto(produto);

    }
}
