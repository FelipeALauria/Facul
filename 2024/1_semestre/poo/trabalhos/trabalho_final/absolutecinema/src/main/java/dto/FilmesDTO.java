/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DTO;

/**
 *
 * @author felip
 */
public class FilmesDTO extends ProdutoDTO {
    private String horariosDeExibicao, idioma, diretor;
    private int duracaoDoFilme, salaDeExibicao;

    /**
     * @return the horariosDeExibicao
     */
    public String getHorariosDeExibicao() {
        return horariosDeExibicao;
    }

    /**
     * @param horariosDeExibicao the horariosDeExibicao to set
     */
    public void setHorariosDeExibicao(String horariosDeExibicao) {
        this.horariosDeExibicao = horariosDeExibicao;
    }

    /**
     * @return the idioma
     */
    public String getIdioma() {
        return idioma;
    }

    /**
     * @param idioma the idioma to set
     */
    public void setIdioma(String idioma) {
        this.idioma = idioma;
    }

    /**
     * @return the duracaoDoFilme
     */
    public int getDuracaoDoFilme() {
        return duracaoDoFilme;
    }

    /**
     * @param duracaoDoFilme the duracaoDoFilme to set
     */
    public void setDuracaoDoFilme(int duracaoDoFilme) {
        this.duracaoDoFilme = duracaoDoFilme;
    }

    /**
     * @return the salaDeExibicao
     */
    public int getSalaDeExibicao() {
        return salaDeExibicao;
    }

    /**
     * @param salaDeExibicao the salaDeExibicao to set
     */
    public void setSalaDeExibicao(int salaDeExibicao) {
        this.salaDeExibicao = salaDeExibicao;
    }

    /**
     * @return the diretor
     */
    public String getDiretor() {
        return diretor;
    }

    /**
     * @param diretor the diretor to set
     */
    public void setDiretor(String diretor) {
        this.diretor = diretor;
    }
    
}
