# Jacobi OpenMP

Implementação do método de Jacobi paralelizado com OpenMP.

## Requisitos
- GCC com suporte a OpenMP (flag `-fopenmp`).
- Ambiente POSIX (Linux/WSL/macOS com GCC e OpenMP instalados).

## Compilação

Com GCC:

```
gcc -O2 -std=c11 -fopenmp jacobi_omp.c -lm -o jacobi_omp
```

## Formato de entrada
- Arquivo texto com `N` números por linha.
- As primeiras `N` linhas são a matriz `A` (`N x N`).
- A última linha é o vetor `b` (com `N` números).
- O programa detecta `N` automaticamente a partir da primeira linha.

Exemplo `linear2.dat` (2x2):

```
4 1
2 3
6 8
```

## Execução

Parâmetros suportados:
- `--in <arquivo>`: caminho do arquivo de entrada (obrigatório).
- `--threads <N>`: quantidade de threads (padrão: 2).
- `--schedule <static|dynamic|guided>`: estratégia de escalonamento do OpenMP.
- `--chunk <C>`: tamanho do chunk (opcional, aplicável para os schedules acima).

Exemplos:

```
./jacobi_omp --in linear2.dat --threads 4 --schedule static
./jacobi_omp --in sistlinear2k.dat --threads 8 --schedule guided --chunk 25
```

Saída:
- `stdout`: linha com a solução (`N` valores com 4 casas decimais).
- `stderr`: log de desempenho no formato `[omp] thr=<T> iter=<K> tempo=<segundos> s`.

Observações:
- Se a matriz não for estritamente diagonalmente dominante, o programa emitirá um aviso (Jacobi pode convergir ou não nessas condições).
- Em caso de divergência (NaN/Inf), o programa aborta a iteração, imprime uma linha de zeros em `stdout` e retorna código de erro.

## Benchmark (script)

O script `bench_omp.sh` executa combinações de `threads` e `schedule` múltiplas vezes e registra somente as linhas de tempo em um `.txt`.

Uso:

```
bash bench_omp.sh [arquivo_entrada] [repeticoes] [arquivo_saida]

# exemplos
bash bench_omp.sh linear2.dat 3 bench_linear2.txt
bash bench_omp.sh sistlinear2k.dat 3 bench_sistlinear2k.txt
```

O arquivo gerado conterá blocos por caso (combinação) e, para cada repetição, uma linha `[omp] … tempo=… s`.

