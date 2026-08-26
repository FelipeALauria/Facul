package DTO;

/**
 *
 * @author felip
 */
public abstract class FuncionarioDTO {
    private int id, cargaHoraria;
    private String nomeCompleto, cpf, vinculoEmpregativo;
    private double salarioHora;

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
     * @return the cargaHoraria
     */
    public int getCargaHoraria() {
        return cargaHoraria;
    }

    /**
     * @param cargaHoraria the cargaHoraria to set
     */
    public void setCargaHoraria(int cargaHoraria) {
        this.cargaHoraria = cargaHoraria;
    }

    /**
     * @return the nomeCompleto
     */
    public String getNomeCompleto() {
        return nomeCompleto;
    }

    /**
     * @param nomeCompleto the nomeCompleto to set
     */
    public void setNomeCompleto(String nomeCompleto) {
        this.nomeCompleto = nomeCompleto;
    }

    /**
     * @return the cpf
     */
    public String getCpf() {
        return cpf;
    }

    /**
     * @param cpf the cpf to set
     */
    public void setCpf(String cpf) {
        this.cpf = cpf;
    }

    /**
     * @return the vinculoEmpregativo
     */
    public String getVinculoEmpregativo() {
        return vinculoEmpregativo;
    }

    /**
     * @param vinculoEmpregativo the vinculoEmpregativo to set
     */
    public void setVinculoEmpregativo(String vinculoEmpregativo) {
        this.vinculoEmpregativo = vinculoEmpregativo;
    }

    /**
     * @return the salarioHora
     */
    public double getSalarioHora() {
        return salarioHora;
    }

    /**
     * @param salarioHora the salarioHora to set
     */
    public void setSalarioHora(double salarioHora) {
        this.salarioHora = salarioHora;
    }
}