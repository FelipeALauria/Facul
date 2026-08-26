package com.absolutecinema;

import DTO.*;
import DAO.*;
import java.io.IOException;
import java.net.URL;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

import javafx.collections.FXCollections;
import javafx.util.Duration;
import java.util.ResourceBundle;
import javafx.animation.TranslateTransition;
import javafx.application.Platform;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

/**
 * FXML Controller class
 *
 * @author Win11
 */
public class MainscreenController implements Initializable {

    @FXML
    private Button botaoFechar;
    @FXML
    private Label mensagemGerente;
    @FXML
    private Label mensagemUsuario;
    @FXML
    private Label numeroVendas;
    @FXML
    private Label numeroPipocas;
    @FXML
    private Label numeroHoras;
    @FXML
    private Label numeroLucro;
    @FXML
    private Label numeroIngressos;
    @FXML
    private Label infoSala1;
    @FXML
    private Label infoSala2;
    @FXML
    private Pane slideBarGerencia;
    @FXML
    private Pane slideBarPesquisa;
    @FXML
    private Pane slideBarVendas;
    @FXML
    private TableView tabelaEscala;
    @FXML
    private TableColumn IDcol;
    @FXML
    private TableColumn nomeCol;
    @FXML
    private TableColumn escalaCol;
    @FXML
    private TableColumn areaCol;
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
        int numVendas = -1, numBaldes = -1, numIngressos = -1;
        double valorVendas = -1;
        String nomeGerente = null, menGerente = null, horaFilme = null, sala1 = null, sala2 = null, sql;
        LocalTime horaAtual;
        List<? super FuncionarioDTO> listaFuncionario = new ArrayList<>();
        ObservableList<? super FuncionarioDTO> observableFuncionarios;
        PreparedStatement preparedStatement;
        ResultSet rs;

        try {
            sql = "SELECT * from gerentes where loginGerente = ? and senhaGerente = ? ";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            preparedStatement.setString(1, gerente.getLoginGerente());
            preparedStatement.setString(2, gerente.getSenhaGerente());
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
                nomeGerente = rs.getString("loginGerente");
                String[] partesNome = nomeGerente.split(" ");
                menGerente = "Olá " + partesNome[0];
            }

            sql = "SELECT sum(quantidade) AS numeroVendas from vendas";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
                numVendas = rs.getInt("numeroVendas");
            }

            sql = "SELECT SUM(custo) AS valorVendas from vendas";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
                valorVendas = rs.getDouble("valorVendas");
            }

            sql = "SELECT SUM(quantidade) AS numBaldes " +
                    "FROM vendas " +
                    "WHERE nome LIKE 'Balde%' OR nome LIKE 'balde%'";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
                numBaldes = rs.getInt("numBaldes");
            }

            sql = "SELECT SUM(duracaofilme) AS duracaoFilme FROM catalogodefilmes";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
                int duracaoTotalMinutos = rs.getInt("duracaoFilme");
                int horas = duracaoTotalMinutos / 60;
                int minutos = duracaoTotalMinutos % 60;
                LocalTime tempo = LocalTime.of(horas, minutos);
                horaFilme = tempo.format(DateTimeFormatter.ofPattern("HH:mm"));
            }

            sql = "SELECT SUM(quantidade) AS numIngressos " +
                    "FROM vendas " +
                    "WHERE nome LIKE 'Ingresso%' OR nome LIKE 'ingresso%'";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
                numIngressos = rs.getInt("numIngressos");
            }

            sql = "SELECT nome FROM catalogodefilmes WHERE saladeexibicao = '1';";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
                sala1 = rs.getString("nome");
            }
            sql = "SELECT nome FROM catalogodefilmes WHERE saladeexibicao = '2';";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            if (rs.next()) {
            sala2 = rs.getString("nome");
            }

            sql = "SELECT * FROM funcionarioscinema;";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            horaAtual = LocalTime.now();
            FuncionarioCinemaDTO funcionarioCinema = new FuncionarioCinemaDTO();
            while (rs.next()) {
                int id = rs.getInt("id");
                funcionarioCinema.setId(id);
                String nome = rs.getString("nome");
                funcionarioCinema.setNomeCompleto(nome);
                String cpf = rs.getString("cpf");
                funcionarioCinema.setCpf(cpf);
                String vinculo = rs.getString("vinculoEmpregativo");
                funcionarioCinema.setVinculoEmpregativo(vinculo);
                int escala = rs.getInt("horarioDeTrabalho");
                funcionarioCinema.setCargaHoraria(escala);
                double salario = rs.getDouble("salarioHora");
                funcionarioCinema.setSalarioHora(salario);
                String faxina = rs.getString("faxina");
                funcionarioCinema.setFaxina(faxina);
                int min = escala % 60;
                int h = escala / 60;
                if (horaAtual.isAfter(LocalTime.of(h, min)) && horaAtual.isBefore(LocalTime.of(h + 8, min))) {
                    listaFuncionario.add(funcionarioCinema);
                }
            }
            sql = "SELECT * FROM funcionariosbomboniere;";
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            rs = preparedStatement.executeQuery();
            FuncionarioBomboniereDTO funcionarioBomboniere = new FuncionarioBomboniereDTO();
            while (rs.next()) {
                int id = rs.getInt("id");
                funcionarioBomboniere.setId(id);
                String nome = rs.getString("nome");
                funcionarioBomboniere.setNomeCompleto(nome);
                String cpf = rs.getString("cpf");
                funcionarioBomboniere.setCpf(cpf);
                String vinculo = rs.getString("vinculoEmpregativo");
                funcionarioBomboniere.setVinculoEmpregativo(vinculo);
                int escala = rs.getInt("horarioDeTrabalho");
                funcionarioBomboniere.setCargaHoraria(escala);
                double salario = rs.getDouble("salarioHora");
                funcionarioBomboniere.setSalarioHora(salario);
                double meta = rs.getDouble("meta");
                funcionarioBomboniere.setMeta(meta);
                int min = escala % 60;
                int h = escala / 60;
                if (horaAtual.isAfter(LocalTime.of(h, min)) && horaAtual.isBefore(LocalTime.of(h + 8, min))) {
                    listaFuncionario.add(funcionarioBomboniere);
                }
            }
            preparedStatement.close();
            rs.close();
        } catch (SQLException e) {
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Erro");
            alert.setHeaderText("Ocorreu um erro ao acessar o banco de dados");
            alert.setContentText("Detalhes do erro: " + e.getMessage() + "\nEntre em contato com a assistência técnica");
            alert.setOnCloseRequest(event -> {
                Platform.exit();
            });
            alert.showAndWait();
        } finally {
             observableFuncionarios = FXCollections.observableList(listaFuncionario);
            String finalNomeGerente = nomeGerente;
            String finalMenGerente = menGerente;
            int finalNumVendas = numVendas;
            double finalValorVendas = valorVendas;
            int finalNumBaldes = numBaldes;
            String finalHoraFilme = horaFilme;
            int finalNumIngressos = numIngressos;
            String finalSala1 = sala1;
            String finalSala2 = sala2;
            Platform.runLater(() -> {
                mensagemGerente.setText(finalNomeGerente);
                mensagemUsuario.setText(finalMenGerente);
                numeroVendas.setText(finalNumVendas != -1 ? Integer.toString(finalNumVendas) : "Erro");
                numeroLucro.setText(finalValorVendas != -1 ? Double.toString(finalValorVendas) : "Erro");
                numeroPipocas.setText(finalNumBaldes != -1 ? Integer.toString(finalNumBaldes) : "Erro");
                numeroHoras.setText(finalHoraFilme != null ? finalHoraFilme : "Erro");
                numeroIngressos.setText(finalNumIngressos != -1 ? Integer.toString(finalNumIngressos) : "Erro");
                infoSala1.setText(finalSala1 != null ? finalSala1 : "Erro");
                infoSala2.setText(finalSala2 != null ? finalSala2 : "Erro");
                tabelaEscala.setItems(observableFuncionarios);
                nomeCol.setCellValueFactory(new PropertyValueFactory<>("nomeCompleto"));
                escalaCol.setCellValueFactory(new PropertyValueFactory<>("cargaHoraria"));
                areaCol.setCellValueFactory(new PropertyValueFactory<>("area"));
                IDcol.setCellValueFactory(new PropertyValueFactory<>("id"));
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
}
