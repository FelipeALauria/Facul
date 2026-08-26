package Colections;

public class Pessoa implements Comparable <Pessoa>{
    private String nome;
    private String CPF;
    private String nacionalidade;

    public Pessoa(String nome, String CPF, String nacionalidade) {
        this.nome = nome;
        this.CPF = CPF;
        this.nacionalidade = nacionalidade;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCPF() {
        return CPF;
    }

    public void setCPF(String CPF) {
        this.CPF = CPF;
    }

    public String getNacionalidade() {
        return nacionalidade;
    }

    public void setNacionalidade(String nacionalidade) {
        this.nacionalidade = nacionalidade;
    }

    @Override
    public int compareTo(Pessoa outra) {
        return this.nome.compareTo(outra.getNome());
    }
}
