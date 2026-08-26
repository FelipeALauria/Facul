package DTO;

/**
 *
 * @author felip
 */
public abstract class ProdutoDTO {

    private int id, quantidadeDeProdutos;
    private static int idAdicionar=1;
    private String nome, descricao;
    private double valor;

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the quantidadeDeProdutos
     */
    public int getQuantidadeDeProdutos() {
        return quantidadeDeProdutos;
    }

    /**
     * @param quantidadeDeProdutos the quantidadeDeProdutos to set
     */
    public void setQuantidadeDeProdutos(int quantidadeDeProdutos) {
        this.quantidadeDeProdutos = quantidadeDeProdutos;
    }

    /**
     * @return the nome
     */
    public String getNome() {
        return nome;
    }

    /**
     * @param nome the nome to set
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * @return the descricao
     */
    public String getDescricao() {
        return descricao;
    }

    /**
     * @param descricao the descricao to set
     */
    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    /**
     * @return the valor
     */
    public double getValor() {
        return valor;
    }

    /**
     * @param valor the valor to set
     */
    public void setValor(double valor) {
        this.valor = valor;
    }
}
