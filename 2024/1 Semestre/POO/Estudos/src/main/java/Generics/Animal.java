package Generics;

public class Animal {
    private String nome;
    private String especie;
    private String classificacao;

    public Animal(String nome, String especie, String classificacao) {
        this.nome = nome;
        this.especie = especie;
        this.classificacao = classificacao;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getEspecie() {
        return especie;
    }

    public void setEspecie(String especie) {
        this.especie = especie;
    }

    public String getClassificacao() {
        return classificacao;
    }

    public void setClassificacao(String classificacao) {
        this.classificacao = classificacao;
    }
}
