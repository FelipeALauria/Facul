package Generics;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Insere<T> {
    public List<T> lista = new ArrayList<T>();

    public void insere(T t) {
        lista.add(t);
    }

    public void imprime() {
        for (T t : lista) {
            if(t instanceof Pessoa)
                System.out.println(((Pessoa) t).getNome());
            else if(t instanceof Animal)
                System.out.println(((Animal) t).getNome());
            else
                System.out.println("Você é muito burro");
        }
    }

}
