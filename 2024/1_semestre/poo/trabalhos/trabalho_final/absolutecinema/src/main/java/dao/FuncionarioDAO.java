package DAO;

import DTO.FuncionarioBomboniereDTO;
import DTO.FuncionarioCinemaDTO;
import DTO.FuncionarioDTO;
import Interfaces.Pagamento;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javafx.scene.control.Alert;

/**
 *
 * @author felip
 */
public abstract class FuncionarioDAO implements Pagamento {

    private Conexao conexao;

    /**
     *
     * @author Felipe Lauria
     * @param novoFuncionario
     */
    public <F> void contratarFuncionario(F novoFuncionario) {

        try {
            String sql;
            PreparedStatement declaracao;

            if (novoFuncionario instanceof FuncionarioCinemaDTO) {
                sql = "INSERT INTO funcionariosCinema(nome, cpf, vinculoEmpregativo, horarioDeTrabalho, salarioHora, faxina) VALUES(?,?,?,?,?,?)";
                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setString(1, ((FuncionarioCinemaDTO) novoFuncionario).getNomeCompleto());
                declaracao.setString(2, ((FuncionarioCinemaDTO) novoFuncionario).getCpf());
                declaracao.setString(3, ((FuncionarioCinemaDTO) novoFuncionario).getVinculoEmpregativo());
                declaracao.setInt(4, ((FuncionarioCinemaDTO) novoFuncionario).getCargaHoraria());
                declaracao.setDouble(5, ((FuncionarioCinemaDTO) novoFuncionario).getSalarioHora());
                declaracao.setString(6, ((FuncionarioCinemaDTO) novoFuncionario).getFaxina());

                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText("Funcionario Cadastro com Sucesso!");
                alerta.showAndWait();
            } else if (novoFuncionario instanceof FuncionarioBomboniereDTO) {
                sql = "INSERT INTO funcionariosBomboniere(nome, cpf, vinculoEmpregativo, horarioDeTrabalho, salarioHora, meta) VALUES(?,?,?,?,?,?)";
                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setString(1, ((FuncionarioBomboniereDTO) novoFuncionario).getNomeCompleto());
                declaracao.setString(2, ((FuncionarioBomboniereDTO) novoFuncionario).getCpf());
                declaracao.setString(3, ((FuncionarioBomboniereDTO) novoFuncionario).getVinculoEmpregativo());
                declaracao.setInt(4, ((FuncionarioBomboniereDTO) novoFuncionario).getCargaHoraria());
                declaracao.setDouble(5, ((FuncionarioBomboniereDTO) novoFuncionario).getSalarioHora());
                declaracao.setDouble(6, ((FuncionarioBomboniereDTO) novoFuncionario).getMeta());

                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText("Funcionario Cadastro com Sucesso!");
                alerta.showAndWait();
            } else {
                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText("Não foi possivel adicionar o funcionario!");
                alerta.showAndWait();
            }
        } catch (SQLException e) {
            Alert alerta = new Alert(Alert.AlertType.INFORMATION);
            alerta.setTitle("Erro");
            alerta.setHeaderText(null);
            alerta.setContentText("Não foi possivel adicionar o funcionario!" + e.getMessage());
            alerta.showAndWait();
        }
    }

    public <F> void demitirFuncionario(F funcionario) {

        try {
            String sql;
            PreparedStatement declaracao;

            if (funcionario instanceof FuncionarioCinemaDTO) {
                int id = ((FuncionarioCinemaDTO) funcionario).getId();
                sql = "DELETE FROM funcionarioscinema WHERE id = ?";

                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setInt(1, id);

                declaracao.executeUpdate();

                sql = "UPDATE funcionarioscinema SET id = id - 1 WHERE id >= ?";
                declaracao = conexao.getConexao().prepareStatement(sql);
                declaracao.setInt(1, id);
                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText("Funcionario Removido com Sucesso!");
                alerta.showAndWait();

            } else if (funcionario instanceof FuncionarioBomboniereDTO) {
                int id = ((FuncionarioBomboniereDTO) funcionario).getId();
                sql = "DELETE FROM funcionarioscinema WHERE id = ?";

                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setInt(1, id);

                declaracao.executeUpdate();

                sql = "UPDATE funcionariosbomboniere SET id = id - 1 WHERE id >= ?";
                declaracao = conexao.getConexao().prepareStatement(sql);
                declaracao.setInt(1, id);
                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText("Funcionario Removido com Sucesso!");
                alerta.showAndWait();

            } else {
                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText("Não foi possivel demitir o funcionario!");
                alerta.showAndWait();
            }
        } catch (SQLException e) {
            Alert alerta = new Alert(Alert.AlertType.INFORMATION);
            alerta.setTitle("Erro");
            alerta.setHeaderText(null);
            alerta.setContentText("Não foi possivel demitir o funcionario!" + e.getMessage());
            alerta.showAndWait();
        }
    }

    @Override
    public <F> double calcularSalario(F funcionario) {
        double pagamento = 0;
        String sql;
        PreparedStatement declaracao;
        FuncionarioDAO funcionarioDAO;
        ResultSet resultado;

        try {
            if (funcionario instanceof FuncionarioCinemaDTO) {
                sql = "SELECT horarioDeTrabalho, salarioHora, faxina FROM funcionarioscinema WHERE id = ?";
                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setInt(1, ((FuncionarioCinemaDTO) funcionario).getId());
                resultado = declaracao.executeQuery();

                if(resultado.next()) {
                    funcionarioDAO = new FuncionarioCinemaDAO();
                    int cargaHoraria = resultado.getInt("horarioDeTrabalho");
                    double salario = resultado.getDouble("salarioHora");
                    if ("Sim".equals(resultado.getString("faxina"))) {
                        double periculosidade = ((FuncionarioCinemaDAO) funcionarioDAO).adicionalDePericulosidade(((FuncionarioCinemaDTO) funcionario));
                        pagamento = (salario * cargaHoraria) + periculosidade;
                        Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                        alerta.setTitle("Informação");
                        alerta.setHeaderText(null);
                        alerta.setContentText("O salário a ser pago é de:" + pagamento);
                        alerta.showAndWait();
                    }else {
                        pagamento = salario * cargaHoraria;
                        Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                        alerta.setTitle("Informação");
                        alerta.setHeaderText(null);
                        alerta.setContentText("O salário a ser pago é de:" + pagamento);
                        alerta.showAndWait();
                    }
                }

            } else if (funcionario instanceof FuncionarioBomboniereDTO) {
                sql = "SELECT salarioHora FROM funcionariosbomboniere WHERE id = ?";
                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setInt(1, ((FuncionarioBomboniereDTO) funcionario).getId());
                resultado = declaracao.executeQuery();

                if(resultado.next()){
                    funcionarioDAO = new FuncionarioBomboniereDAO();
                    double salario = resultado.getDouble("salarioHora");
                    double meta = ((FuncionarioBomboniereDAO) funcionarioDAO).baterMeta((FuncionarioBomboniereDTO)funcionario);
                    pagamento = salario + meta;
                    Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                    alerta.setTitle("Informação");
                    alerta.setHeaderText(null);
                    alerta.setContentText("O salário a ser pago é de: " + pagamento);
                    alerta.showAndWait();
                    }

            } else {
                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText("Não foi possivel calcular o salario do funcionario!");
                alerta.showAndWait();
            }
        } catch (SQLException e) {
            Alert alerta = new Alert(Alert.AlertType.INFORMATION);
            alerta.setTitle("Erro");
            alerta.setHeaderText(null);
            alerta.setContentText("Não foi possivel calcular o salário do funcionario!" + e.getMessage());
            alerta.showAndWait();
        }

        return pagamento;
    }

    public <F> void escalaFuncionario(F funcionario) {
        String sql;
        PreparedStatement declaracao;
        ResultSet resultado;

        try {
            sql = "SELECT horarioDeTrabalho, salarioHora, faxina FROM funcionarioscinemas WHERE id = ?";
            declaracao = conexao.getConexao().prepareStatement(sql);
            ((FuncionarioDTO)funcionario).getId();

        } catch (SQLException e) {
            Alert alerta = new Alert(Alert.AlertType.INFORMATION);
            alerta.setTitle("Erro");
            alerta.setHeaderText(null);
            alerta.setContentText("Não foi possivel alterar a escala!" + e.getMessage());
            alerta.showAndWait();
        }
    }
}
