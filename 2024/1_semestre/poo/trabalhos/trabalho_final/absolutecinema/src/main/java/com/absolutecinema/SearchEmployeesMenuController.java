package com.absolutecinema;

import DAO.*;
import DTO.*;
import java.io.IOException;
import java.net.URL;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
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
public class SearchEmployeesMenuController implements Initializable {

    @FXML
    private TextField campo;
    @FXML
    private RadioButton botaoID;
    @FXML
    private RadioButton botaoNome;
    @FXML
    private RadioButton botaoCPF;
    @FXML
    private TableView tabelaFucionarios;
    @FXML
    private TableColumn IDcol;
    @FXML
    private TableColumn nomeCol;
    @FXML
    private TableColumn escalaCol;
    @FXML
    private TableColumn cpfCol;
    @FXML
    private TableColumn salarioCol;
    @FXML
    private TableColumn areaCol;
    @FXML
    private Button botaoCancelar;
    private String sql;
    private PreparedStatement preparedStatement;
    private ResultSet rs;
    FuncionarioDTO funcionario;
    List<? super FuncionarioDTO> listaFuncionario = new ArrayList<>();
    ObservableList<? super FuncionarioDTO> observableFuncionarios = FXCollections.observableArrayList(listaFuncionario);
    private Conexao conexao;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        ToggleGroup grupoBotao = new ToggleGroup();

        botaoID.setToggleGroup(grupoBotao);
        botaoID.setOnAction(event -> campo.setPromptText("Digite o ID do funcionário"));

        botaoNome.setToggleGroup(grupoBotao);
        botaoNome.setOnAction(event -> campo.setPromptText("Digite o nome do funcionário"));

        botaoCPF.setToggleGroup(grupoBotao);
        botaoCPF.setOnAction(event -> campo.setPromptText("Digite o CPF do funcionário"));
    }

    public void pesquisarFuncionario() {
        if (!botaoID.isSelected() && !botaoNome.isSelected() && !botaoCPF.isSelected()) {
            return;
        }

        if (botaoID.isSelected()) {
            sql = "SELECT * FROM funcionarioscinema WHERE id = ? "
                    + "UNION "
                    + "SELECT * FROM funcionariosbomboniere WHERE id = ?";
        } else if (botaoNome.isSelected()) {
            sql = "SELECT * FROM funcionarioscinema WHERE nome = ? "
                    + "UNION "
                    + "SELECT * FROM funcionariosbomboniere WHERE nome = ?";
        } else if (botaoCPF.isSelected()) {
            sql = "SELECT * FROM funcionarioscinema WHERE cpf = ? "
                    + "UNION "
                    + "SELECT * FROM funcionariosbomboniere WHERE cpf = ?";
        }

        try {
            preparedStatement = (conexao.getConexao()).prepareStatement(sql);
            preparedStatement.setString(1, campo.getText());
            preparedStatement.setString(2, campo.getText());
            rs = preparedStatement.executeQuery();

            while (rs.next()) {
                String nome = rs.getString("nome");
                String cpf = rs.getString("cpf");
                String vinculo = rs.getString("vinculoEmpregativo");
                int escala = rs.getInt("horarioDeTrabalho");
                double salario = rs.getDouble("salarioHora");

                if (sql.contains("funcionarioscinema")) {
                    funcionario = new FuncionarioCinemaDTO();
                    int id = rs.getInt("id");
                    funcionario.setId(id);
                    funcionario.setNomeCompleto(nome);
                    funcionario.setCpf(cpf);
                    funcionario.setVinculoEmpregativo(vinculo);
                    funcionario.setCargaHoraria(escala);
                    funcionario.setSalarioHora(salario);

                    String faxina = rs.getString("faxina");
                    ((FuncionarioCinemaDTO)funcionario).setFaxina(faxina);

                    listaFuncionario.add((FuncionarioCinemaDTO)funcionario);
                } else {
                    funcionario = new FuncionarioBomboniereDTO();
                    int id = rs.getInt("id");
                    funcionario.setId(id);
                    funcionario.setNomeCompleto(nome);
                    funcionario.setCpf(cpf);
                    funcionario.setVinculoEmpregativo(vinculo);
                    funcionario.setCargaHoraria(escala);
                    funcionario.setSalarioHora(salario);

                    double meta = rs.getDouble("meta");
                    ((FuncionarioBomboniereDTO)funcionario).setMeta(meta);

                    listaFuncionario.add((FuncionarioBomboniereDTO)funcionario);
                }
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
            observableFuncionarios = FXCollections.observableArrayList(listaFuncionario);
            Platform.runLater(() -> {
                tabelaFucionarios.setItems(observableFuncionarios);
                IDcol.setCellValueFactory(new PropertyValueFactory<>("id"));
                nomeCol.setCellValueFactory(new PropertyValueFactory<>("nomeCompleto"));
                escalaCol.setCellValueFactory(new PropertyValueFactory<>("cargaHoraria"));
                cpfCol.setCellValueFactory(new PropertyValueFactory<>("cpf"));
                salarioCol.setCellValueFactory(new PropertyValueFactory<>("salarioHora"));
                areaCol.setCellValueFactory(new PropertyValueFactory<>("classificacao"));
                tabelaFucionarios.refresh();
            });
        }
    }

    public void cancelarOperacao(ActionEvent event) {
        Stage stage = (Stage) botaoCancelar.getScene().getWindow();
        stage.close();
    }

    public void editarFuncionario(ActionEvent event) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("EditEmployee.fxml"));
            Parent root = loader.load();
            Scene editScene = new Scene(root);
            Stage editStage = new Stage();
            editStage.setScene(editScene);
            editStage.initStyle(StageStyle.UNDECORATED);
            EditEmployeeController controller = loader.getController();
            controller.carregarFuncionario(sql, campo.getText());
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

    public void demitirFuncionario(ActionEvent event) {
        FuncionarioDAO funcionarioDAO;
        if (funcionario instanceof FuncionarioCinemaDTO) {
            funcionarioDAO = new FuncionarioCinemaDAO();
        } else {
            funcionarioDAO = new FuncionarioBomboniereDAO();
        }
        funcionarioDAO.demitirFuncionario(funcionario);
    }

    public void pagarSalario(ActionEvent event) {
        if(funcionario instanceof FuncionarioCinemaDTO) {
            FuncionarioDAO funcionarioDAO = new FuncionarioCinemaDAO();
            funcionarioDAO.calcularSalario(funcionario);
        }
        else{
            FuncionarioDAO funcionarioDAO = new FuncionarioBomboniereDAO();
            funcionarioDAO.calcularSalario(funcionario);
        }
    }

}
