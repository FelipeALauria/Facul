package DAO;

import DTO.GerenteDTO;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

public class GerenteDAO {

    public ResultSet autenticacaoGerente(GerenteDTO gerente) {
        Connection conexao = Conexao.getConexao();

        if (conexao == null) {
            Alert alerta = new Alert(AlertType.INFORMATION);
            alerta.setTitle("Informação");
            alerta.setHeaderText(null);
            alerta.setContentText("Não foi possível estabelecer conexão!");
            alerta.showAndWait();
            return null;
        }

        try {
            String sql = "SELECT * FROM gerentes WHERE loginGerente = ? AND senhaGerente = ?";
            PreparedStatement preparedStatement = conexao.prepareStatement(sql);
            preparedStatement.setString(1, gerente.getLoginGerente());
            preparedStatement.setString(2, gerente.getSenhaGerente());

            return preparedStatement.executeQuery();

        } catch (SQLException e) {
            Alert alerta = new Alert(AlertType.INFORMATION);
            alerta.setTitle("Informação");
            alerta.setHeaderText(null);
            alerta.setContentText("Erro ao executar a consulta!");
            alerta.showAndWait();
            e.printStackTrace();
            return null;
        }
    }
}
