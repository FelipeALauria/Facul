/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import DAO.Conexao;
import DAO.FilmesDAO;
import DTO.FilmesDTO;
import DTO.FuncionarioBomboniereDTO;
import DTO.FuncionarioCinemaDTO;
import DTO.FuncionarioDTO;
import java.io.IOException;
import java.net.URL;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.ResourceBundle;
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
public class SearchMoviesMenuController implements Initializable {

    @FXML
    private TextField campo;
    @FXML
    private RadioButton botaoID;
    @FXML
    private RadioButton botaoNome;
    @FXML
    private RadioButton botaoSala;
    @FXML
    private TableView tabelaEscala;
    @FXML
    private TableColumn IDcol;
    @FXML
    private TableColumn nomeCol;
    @FXML
    private TableColumn descricaoCol;
    @FXML
    private TableColumn salaCol;
    @FXML
    private TableColumn ingressoCol;
    @FXML
    private TableColumn idiomaCol;
    @FXML
    private Button botaoCancelar;
    private String sql;
    private PreparedStatement preparedStatement;
    private ResultSet rs;
    List<FilmesDTO> listaFilme = new LinkedList<>();
    FilmesDTO filme;
    ObservableList observableMovies = FXCollections.observableArrayList(listaFilme);
    private Conexao conexao;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        ToggleGroup grupoBotao = new ToggleGroup();

        botaoID.setToggleGroup(grupoBotao);
        botaoID.setOnAction(event -> campo.setPromptText("Digite o ID do funcionário"));

        botaoNome.setToggleGroup(grupoBotao);
        botaoNome.setOnAction(event -> campo.setPromptText("Digite o nome do funcionário"));

        botaoSala.setToggleGroup(grupoBotao);
        botaoSala.setOnAction(event -> campo.setPromptText("Digite o CPF do funcionário"));
    }

    public void pesquisarFilme() {
        if (!botaoID.isSelected() && !botaoNome.isSelected() && !botaoSala.isSelected()) {
            return;
        }

        if (botaoID.isSelected()) {
            sql = "SELECT * FROM catalogodefilmes WHERE id = ? ";
        } else if (botaoNome.isSelected()) {
            sql = "SELECT * FROM catalogodefilmes WHERE nome = ? ";
        } else if (botaoSala.isSelected()) {
            sql = "SELECT * FROM catalogodefilmes WHERE saladeexibicao = ? ";
        }

        try {
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            preparedStatement.setString(1, campo.getText());
            rs = preparedStatement.executeQuery();

            while (rs.next()) {
                filme = new FilmesDTO();
                int id = rs.getInt("id");
                filme.setId(id);
                String nome = rs.getString("nome");
                filme.setNome(nome);
                String descricao = rs.getString("descricao");
                filme.setDescricao(descricao);
                String idioma = rs.getString("idioma");
                filme.setIdioma(idioma);
                String diretor = rs.getString("diretor");
                filme.setDiretor(diretor);
                int duracao = rs.getInt("duracaofilme");
                filme.setDuracaoDoFilme(duracao);
                int sala = rs.getInt("saladeexibicao");
                filme.setSalaDeExibicao(sala);
                int ingressos = rs.getInt("totaldeingressos");
                filme.setQuantidadeDeProdutos(ingressos);
                double valor = rs.getDouble("valordosingressos");
                filme.setValor(valor);
                listaFilme.add(filme);
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
        observableMovies = FXCollections.observableArrayList(listaFilme);
        Platform.runLater(() -> {
            tabelaEscala.setItems(observableMovies);
            IDcol.setCellValueFactory(new PropertyValueFactory<>("id"));
            nomeCol.setCellValueFactory(new PropertyValueFactory<>("nome"));
            descricaoCol.setCellValueFactory(new PropertyValueFactory<>("descricao"));
            idiomaCol.setCellValueFactory(new PropertyValueFactory<>("idioma"));
            salaCol.setCellValueFactory(new PropertyValueFactory<>("saladeDeEibicao"));
            ingressoCol.setCellValueFactory(new PropertyValueFactory<>("quantidadeDeProdutos"));
            tabelaEscala.refresh();
        });

    }

    public void cancelarOperacao(ActionEvent event) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }

    public void editarFilme(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("EditMovie.fxml"));
            Parent root = loader.load();
            Scene editScene = new Scene(root);
            Stage editStage = new Stage();
            editStage.setScene(editScene);
            editStage.initStyle(StageStyle.UNDECORATED);
            EditMovieController controller = loader.getController();
            controller.carregarFilme(sql, campo.getText());
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

    public void apagarFilme(ActionEvent event) {
        FilmesDAO filmesDAO = new FilmesDAO();
        filmesDAO.removerProduto(filme);
    }

}
