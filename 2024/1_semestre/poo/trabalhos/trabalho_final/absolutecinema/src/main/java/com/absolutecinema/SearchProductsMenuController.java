/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import DAO.BomboniereDAO;
import DAO.Conexao;
import java.io.IOException;
import java.net.URL;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import DAO.ProdutoDAO;
import DTO.BomboniereDTO;
import DTO.ProdutoDTO;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

/**
 * FXML Controller class
 *
 * @author Win11
 */
public class SearchProductsMenuController implements Initializable {

    @FXML
    private TextField campoNome;
    @FXML
    private RadioButton botaoID;
    @FXML
    private RadioButton botaoNome;
    @FXML
    private RadioButton botaoSala;
    @FXML
    private TableView tabelaSnackBar;
    @FXML
    private TableColumn IDcol;
    @FXML
    private TableColumn nomeCol;
    @FXML
    private TableColumn descricaoCol;
    @FXML
    private TableColumn valorCol;
    @FXML
    private TableColumn estoqueCol;
    @FXML
    private Button botaoCancelar;
    private String sql;
    private PreparedStatement preparedStatement;
    private ResultSet rs;
    private ProdutoDTO produto = new BomboniereDTO();
    private List<ProdutoDTO> listaProduto = new ArrayList<>();
    private ObservableList<ProdutoDTO> observableProdutos;
    private Conexao conexao;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        ToggleGroup grupoBotao = new ToggleGroup();

        botaoID.setToggleGroup(grupoBotao);
        botaoID.setOnAction(event -> campoNome.setPromptText("Digite o ID do funcionário"));

        botaoNome.setToggleGroup(grupoBotao);
        botaoNome.setOnAction(event -> campoNome.setPromptText("Digite o nome do funcionário"));
    }

    public void pesquisarProduto() {
        if (!botaoID.isSelected() && !botaoNome.isSelected()) {
            return;
        }

        if (botaoID.isSelected()) {
            sql = "SELECT * FROM produtosbomboniere WHERE id = ? ";
        } else if (botaoNome.isSelected()) {
            sql = "SELECT * FROM produtosbomboniere WHERE nome = ? ";
        }
        try {
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            preparedStatement.setString(1, campoNome.getText());
            rs = preparedStatement.executeQuery();

            while (rs.next()) {
                produto = new BomboniereDTO();
                int id = rs.getInt("id");
                produto.setId(id);
                String nome = rs.getString("nome");
                produto.setNome(nome);
                String descricao = rs.getString("descricao");
                produto.setDescricao(descricao);
                int caloria = rs.getInt("caloria");
                ((BomboniereDTO) produto).setCalorias(caloria);
                double custo = rs.getDouble("custo");
                ((BomboniereDTO) produto).setCusto(custo);
                int estoque = rs.getInt("totalemestoque");
                produto.setQuantidadeDeProdutos(estoque);
                double valor = rs.getDouble("valordosprodutos");
                produto.setValor(valor);
                listaProduto.add((BomboniereDTO)produto);
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
        }
        observableProdutos = FXCollections.observableArrayList(listaProduto);
        Platform.runLater(() -> {
            tabelaSnackBar.setItems(observableProdutos);
            IDcol.setCellValueFactory(new PropertyValueFactory<>("id"));
            nomeCol.setCellValueFactory(new PropertyValueFactory<>("nome"));
            descricaoCol.setCellValueFactory(new PropertyValueFactory<>("descricao"));
            estoqueCol.setCellValueFactory(new PropertyValueFactory<>("quantidadeDeProdutos"));
            valorCol.setCellValueFactory(new PropertyValueFactory<>("valor"));
            tabelaSnackBar.refresh();
        });
    }

    public void cancelarOperacao(ActionEvent event) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }

    public void editarProduto(ActionEvent event) {
        String elementoAlterado = " ";
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("EditProduct.fxml"));
            Parent root = loader.load();
            Scene editScene = new Scene(root);
            Stage editStage = new Stage();
            editStage.setScene(editScene);
            editStage.initStyle(StageStyle.UNDECORATED);
            EditProductController controller = loader.getController();
            controller.carregarProduto(sql, elementoAlterado);
            editStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar a tela");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoCancelar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void apagarProduto(ActionEvent event) {
        ProdutoDAO produtoDAO = new BomboniereDAO();
        produtoDAO.removerProduto(produto);
    }
}
