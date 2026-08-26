package DAO;

import DTO.FuncionarioBomboniereDTO;
import DTO.FuncionarioDTO;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 *
 * @author felip
 */
public class FuncionarioBomboniereDAO extends FuncionarioDAO {
    Conexao conexao;
    
    public double baterMeta(FuncionarioBomboniereDTO funcionario) {
        double metaEstabelecida = 3000;
        String sql;
        PreparedStatement declaracao;
        ResultSet resultado;
        double metaAtiginda;
        double bonificacao = 100;
        
        try {
            sql = "SELECT meta FROM funcionariosbomboniere WHERE id = ?";


            declaracao = conexao.getConexao().prepareStatement(sql);
            declaracao.setInt(1, funcionario.getId());
            resultado = declaracao.executeQuery();
            
            metaAtiginda = resultado.getDouble("meta");
            
            if(metaAtiginda >= metaEstabelecida) {
                int resto = (int) (metaAtiginda - metaEstabelecida) % 1000;
                
                if(resto > 0)
                    bonificacao = 80 + (resto * 50);
                else
                    bonificacao = 80 ;               
            }
            
        } catch (SQLException e) {
            
        }
        
        return bonificacao;
    }
}
