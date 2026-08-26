package DAO;

import DTO.BomboniereDTO;
import DTO.FilmesDTO;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javafx.scene.control.Alert;

/**
 *
 * @author felip
 */
public abstract class ProdutoDAO {

    private Conexao conexao;

    public <P> void adicionarProduto(P novoProduto) {

        try {
            String sql;
            PreparedStatement declaracao;

            if (novoProduto instanceof FilmesDTO) {
                sql = "INSERT INTO catalogodefilmes(nome, descricao, idioma, diretor, duracaofilme, saladeexibicao, totaldeingressos, valordosingressos) VALUES(?,?,?,?,?,?,?,?)";
                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setString(1, ((FilmesDTO) novoProduto).getNome());
                declaracao.setString(2, ((FilmesDTO) novoProduto).getDescricao());
                declaracao.setString(3, ((FilmesDTO) novoProduto).getIdioma());
                declaracao.setString(4, ((FilmesDTO) novoProduto).getDiretor());
                declaracao.setInt(5, ((FilmesDTO) novoProduto).getDuracaoDoFilme());
                declaracao.setInt(6, ((FilmesDTO) novoProduto).getSalaDeExibicao());
                declaracao.setInt(7, ((FilmesDTO) novoProduto).getQuantidadeDeProdutos());
                declaracao.setDouble(8, ((FilmesDTO) novoProduto).getValor());

                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText(((FilmesDTO) novoProduto).getNome() + " cadastro com Sucesso!");
                alerta.showAndWait();
            } else if (novoProduto instanceof BomboniereDTO) {
                sql = "INSERT INTO produtosbomboniere(nome, descricao, calorias, custo, totalemestoque, valordosprodutos) VALUES(?,?,?,?,?,?)";
                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setString(1, ((BomboniereDTO) novoProduto).getNome());
                declaracao.setString(2, ((BomboniereDTO) novoProduto).getNome());
                declaracao.setInt(3, ((BomboniereDTO) novoProduto).getCalorias());
                declaracao.setDouble(4, ((BomboniereDTO) novoProduto).getCusto());
                declaracao.setInt(5, ((BomboniereDTO) novoProduto).getQuantidadeDeProdutos());
                declaracao.setDouble(6, ((BomboniereDTO) novoProduto).getValor());

                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText(((BomboniereDTO) novoProduto).getNome() + " cadastro com Sucesso!");
                alerta.showAndWait();
            } else {
                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Erro");
                alerta.setHeaderText(null);
                alerta.setContentText("Não foi possivel adicionar o produto!");
                alerta.showAndWait();
            }

        } catch (SQLException e) {
            Alert alerta = new Alert(Alert.AlertType.INFORMATION);
            alerta.setTitle("Erro");
            alerta.setHeaderText(null);
            alerta.setContentText("Não foi possivel adicionar o produto!" + e.getMessage());
            alerta.showAndWait();

        }
    }

    public <P> void removerProduto(P produtoASerRemovido) {

        try {
            String sql;
            PreparedStatement declaracao;

            if (produtoASerRemovido instanceof FilmesDTO) {
                int id = ((FilmesDTO) produtoASerRemovido).getId();
                sql = "DELETE FROM catalogodefilmes WHERE id = ?";

                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setInt(1, id);

                declaracao.executeUpdate();

                sql = "UPDATE catalogodefilmes SET id = id - 1 WHERE id >= ?";
                declaracao = conexao.getConexao().prepareStatement(sql);
                declaracao.setInt(1, id);
                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText(((FilmesDTO) produtoASerRemovido).getNome() + " removido com Sucesso!");
                alerta.showAndWait();
            } else if (produtoASerRemovido instanceof BomboniereDTO) {
                int id = ((BomboniereDTO) produtoASerRemovido).getId();
                sql = "DELETE FROM produtosBomboniere WHERE id = ?";

                declaracao = conexao.getConexao().prepareStatement(sql);

                declaracao.setInt(1, id);

                declaracao.executeUpdate();

                sql = "UPDATE produtosBomboniere SET id = id - 1 WHERE id >= ?";
                declaracao = conexao.getConexao().prepareStatement(sql);
                declaracao.setInt(1, id);
                declaracao.executeUpdate();

                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Informação");
                alerta.setHeaderText(null);
                alerta.setContentText(((BomboniereDTO) produtoASerRemovido).getNome() + " removido com Sucesso!");
                alerta.showAndWait();
            } else {
                Alert alerta = new Alert(Alert.AlertType.INFORMATION);
                alerta.setTitle("Erro");
                alerta.setHeaderText(null);
                alerta.setContentText("Não foi possivel remover o produto!");
                alerta.showAndWait();
            }
        } catch (SQLException e) {
            Alert alerta = new Alert(Alert.AlertType.INFORMATION);
            alerta.setTitle("Erro");
            alerta.setHeaderText(null);
            alerta.setContentText("Não foi possivel remover o produto!");
            alerta.showAndWait();
        }
    }
    
}
