/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/javafx/FXMLController.java to edit this template
 */
package com.absolutecinema;

import DAO.*;
import DTO.*;
import java.io.IOException;
import java.net.URL;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.ResourceBundle;
import javafx.animation.TranslateTransition;
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
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.util.Duration;

/**
 * FXML Controller class
 *
 * @author Win11
 */
public class ManagementMoviesController implements Initializable {

    @FXML
    private Button botaoFechar;
    @FXML
    private Pane slideBarGerencia;
    @FXML
    private Pane slideBarPesquisa;
    @FXML
    private Pane slideBarVendas;
    @FXML
    private TableView tabelaFilmes;
    @FXML
    private TableColumn IDcol;
    @FXML
    private TableColumn nomeCol;
    @FXML
    private TableColumn descricaoCol;
    @FXML
    private TableColumn idiomaCol;
    @FXML
    private TableColumn duracaoCol;
    @FXML
    private TableColumn salasCol;
    @FXML
    private TableColumn ingressosCol;
    @FXML
    private TableColumn valorCol;
    private GerenteDTO gerente;
    private Conexao conexao;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        slideBarGerencia.setTranslateX(-200);
    }

    public void fecharJanela(ActionEvent e) {
        Stage stage = (Stage) botaoFechar.getScene().getWindow();
        stage.close();
    }

    public void mostrarInformacoes(GerenteDTO gerente) {
        this.gerente = gerente;
        String sql;
        List<FilmesDTO> listaFilmes = new LinkedList<>();
        ObservableList <FilmesDTO> observableMovies;
        PreparedStatement preparedStatement;
        ResultSet rs;

        try {
            sql = "SELECT * FROM catalogodefilmes;";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            while (rs.next()) {
                FilmesDTO filme = new FilmesDTO();
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
                listaFilmes.add(filme);
            }
            preparedStatement.close();
            rs.close();
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
            observableMovies = FXCollections.observableArrayList(listaFilmes);
            Platform.runLater(() -> {
                tabelaFilmes.setItems(observableMovies);
                IDcol.setCellValueFactory(new PropertyValueFactory<>("id"));
                nomeCol.setCellValueFactory(new PropertyValueFactory<>("nome"));
                descricaoCol.setCellValueFactory(new PropertyValueFactory<>("descricao"));
                idiomaCol.setCellValueFactory(new PropertyValueFactory<>("idioma"));
                duracaoCol.setCellValueFactory(new PropertyValueFactory<>("duracaoDoFilme"));
                salasCol.setCellValueFactory(new PropertyValueFactory<>("salaDeExibicao"));
                ingressosCol.setCellValueFactory(new PropertyValueFactory<>("quantidadeDeProdutos"));
                valorCol.setCellValueFactory(new PropertyValueFactory<>("valor"));
            });
        }
    }

    public void menuGerenciar(ActionEvent event) {
        if (slideBarVendas.isVisible() || slideBarPesquisa.isVisible()) {
            if (slideBarVendas.isVisible()) {
                retornarVendas(event);
            } else {
                retornarPesquisar(event);
            }
        }
        slideBarGerencia.setVisible(true);
        TranslateTransition slide = new TranslateTransition();
        slide.setDuration(Duration.seconds(0.4));
        slide.setNode(slideBarGerencia);
        slide.setToX(0);
        slide.play();

        slideBarGerencia.setTranslateX(-200);
    }

    public void retornarGerenciar(ActionEvent event) {
        TranslateTransition slide = new TranslateTransition();
        slide.setDuration(Duration.seconds(0.2));
        slide.setNode(slideBarGerencia);
        slide.setToX(-200);
        slide.play();
        slide.setOnFinished(e -> {
            slideBarGerencia.setVisible(false);
            slideBarGerencia.setTranslateX(0);
        });
    }

    public void menuPesquisar(ActionEvent event) {
        if (slideBarGerencia.isVisible() || slideBarVendas.isVisible()) {
            if (slideBarGerencia.isVisible()) {
                retornarGerenciar(event);
            } else {
                retornarVendas(event);
            }
        }
        slideBarPesquisa.setVisible(true);
        TranslateTransition slide = new TranslateTransition();
        slide.setDuration(Duration.seconds(0.4));
        slide.setNode(slideBarPesquisa);
        slide.setToX(0);
        slide.play();

        slideBarPesquisa.setTranslateX(-200);
    }

    public void retornarPesquisar(ActionEvent event) {
        TranslateTransition slide = new TranslateTransition();
        slide.setDuration(Duration.seconds(0.2));
        slide.setNode(slideBarPesquisa);
        slide.setToX(-200);
        slide.play();
        slide.setOnFinished(e -> {
            slideBarPesquisa.setVisible(false);
            slideBarPesquisa.setTranslateX(0);
        });
    }

    public void menuVendas(ActionEvent event) {
        if (slideBarGerencia.isVisible() || slideBarPesquisa.isVisible()) {
            if (slideBarGerencia.isVisible()) {
                retornarGerenciar(event);
            } else {
                retornarPesquisar(event);
            }
        }
        slideBarVendas.setVisible(true);
        TranslateTransition slide = new TranslateTransition();
        slide.setDuration(Duration.seconds(0.4));
        slide.setNode(slideBarVendas);
        slide.setToX(0);
        slide.play();

        slideBarVendas.setTranslateX(-200);
    }

    public void retornarVendas(ActionEvent event) {
        TranslateTransition slide = new TranslateTransition();
        slide.setDuration(Duration.seconds(0.2));
        slide.setNode(slideBarVendas);
        slide.setToX(-200);
        slide.play();
        slide.setOnFinished(e -> {
            slideBarVendas.setVisible(false);
            slideBarVendas.setTranslateX(0);
        });
    }

    public void telaVendasGeral(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("salesManagement.fxml"));
            Parent root = loader.load();
            Scene salesScene = new Scene(root);
            Stage salesStage = new Stage();
            salesStage.setScene(salesScene);
            salesStage.initStyle(StageStyle.UNDECORATED);
            SalesManagementController controller = loader.getController();
            controller.mostrarInformacoesGeral(gerente);
            salesStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoFechar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void telaVendasBomboniere(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("salesManagement.fxml"));
            Parent root = loader.load();
            Scene salesScene = new Scene(root);
            Stage salesStage = new Stage();
            salesStage.setScene(salesScene);
            salesStage.initStyle(StageStyle.UNDECORATED);
            SalesManagementController controller = loader.getController();
            controller.mostrarInformacoesBomboniere(gerente);
            salesStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoFechar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void telaVendasFilmes(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("salesManagement.fxml"));
            Parent root = loader.load();
            Scene salesScene = new Scene(root);
            Stage salesStage = new Stage();
            salesStage.setScene(salesScene);
            salesStage.initStyle(StageStyle.UNDECORATED);
            SalesManagementController controller = loader.getController();
            controller.mostrarInformacoesFilmes(gerente);
            salesStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoFechar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void telaGerenciarFuncionarios(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("managementEmployees.fxml"));
            Parent root = loader.load();
            Scene salesScene = new Scene(root);
            Stage salesStage = new Stage();
            salesStage.setScene(salesScene);
            salesStage.initStyle(StageStyle.UNDECORATED);
            ManagementEmployeesController controller = loader.getController();
            controller.mostrarInformacoes(gerente);
            salesStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoFechar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void telaGerenciarBomboniere(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("managementSnackBar.fxml"));
            Parent root = loader.load();
            Scene salesScene = new Scene(root);
            Stage salesStage = new Stage();
            salesStage.setScene(salesScene);
            salesStage.initStyle(StageStyle.UNDECORATED);
            ManagementSnackBarController controller = loader.getController();
            controller.mostrarInformacoes(gerente);
            salesStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoFechar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void telaGerenciarFilmes(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("managementMovies.fxml"));
            Parent root = loader.load();
            Scene salesScene = new Scene(root);
            Stage salesStage = new Stage();
            salesStage.setScene(salesScene);
            salesStage.initStyle(StageStyle.UNDECORATED);
            ManagementMoviesController controller = loader.getController();
            controller.mostrarInformacoes(gerente);
            salesStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoFechar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void telaBuscarProdutos(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("searchProductsMenu.fxml"));
            Parent root = loader.load();
            Scene searchScene = new Scene(root);
            Stage searchStage = new Stage();
            searchStage.setScene(searchScene);
            searchStage.initStyle(StageStyle.UNDECORATED);
            searchStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        }
    }

    public void telaBuscarFuncionarios(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("searchEmployeesMenu.fxml"));
            Parent root = loader.load();
            Scene searchScene = new Scene(root);
            Stage searchStage = new Stage();
            searchStage.setScene(searchScene);
            searchStage.initStyle(StageStyle.UNDECORATED);
            searchStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        }
    }

    public void telaBuscarFilmes(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("searchMoviesMenu.fxml"));
            Parent root = loader.load();
            Scene searchScene = new Scene(root);
            Stage searchStage = new Stage();
            searchStage.setScene(searchScene);
            searchStage.initStyle(StageStyle.UNDECORATED);
            searchStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        }
    }

    public void telaMain(MouseEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("mainscreen.fxml"));
            Parent root = loader.load();
            Scene salesScene = new Scene(root);
            Stage salesStage = new Stage();
            salesStage.setScene(salesScene);
            salesStage.initStyle(StageStyle.UNDECORATED);
            MainscreenController controller = loader.getController();
            controller.mostrarInformacoes(gerente);
            salesStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o banco de dados");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
            Stage mainStage = (Stage) botaoFechar.getScene().getWindow();
            mainStage.close();
        }
    }

    public void adicionarFilme(ActionEvent evt) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("addNewMovie.fxml"));
            Parent root = loader.load();
            Scene searchScene = new Scene(root);
            Stage searchStage = new Stage();
            searchStage.setScene(searchScene);
            searchStage.initStyle(StageStyle.UNDECORATED);
            searchStage.show();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o menu");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(closeEvent -> {
                Platform.exit();
            });
            alert.showAndWait();
        }
    }
}
