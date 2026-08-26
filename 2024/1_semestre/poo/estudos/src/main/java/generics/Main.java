package Generics;

public class Main<P> {
    public static void main(String[] args) {
      Pessoa pessoa = new Pessoa("Bruna", 15);
      Pessoa pessoa1 = new Pessoa("Felipe", 100);

      Animal animal = new Animal("Cadela", "Zebra", "Mamifero");

      Insere insere = new Insere();

      insere.insere(pessoa);
      insere.insere(pessoa1);
      insere.insere(animal);

      insere.imprime();

    }
}
