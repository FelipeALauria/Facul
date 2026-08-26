#!/usr/bin/env bash
set -euo pipefail

# Uso: ./bench_omp.sh [arquivo_entrada] [repeticoes] [arquivo_saida]
# - arquivo_entrada: default linear10.dat
# - repeticoes: default 3
# - arquivo_saida: default bench_<basename>_<YYYYmmdd-HHMMSS>.txt

IN=${1:-linear10.dat}
REPS=${2:-3}
BASE=$(basename "$IN")
STAMP=$(date +%Y%m%d-%H%M%S)
OUT=${3:-bench_${BASE%.*}_$STAMP.txt}

echo "Gerando benchmark em: $OUT"
echo "Entrada: $IN" | tee "$OUT" >/dev/null
echo "Repetições por caso: $REPS" | tee -a "$OUT" >/dev/null

cases=()

# static sem chunk
for th in 2 4 8; do
  cases+=("--threads $th --schedule static")
done

# static com chunk 25
for th in 2 4 8; do
  cases+=("--threads $th --schedule static --chunk 25")
done

# dynamic com chunk 25
for th in 2 4 8; do
  cases+=("--threads $th --schedule dynamic --chunk 25")
done

# guided com chunk 25
for th in 2 4 8; do
  cases+=("--threads $th --schedule guided --chunk 25")
done

idx=0
for args in "${cases[@]}"; do
  idx=$((idx+1))
  echo "" | tee -a "$OUT" >/dev/null
  echo "==== Caso #$idx: $args" | tee -a "$OUT" >/dev/null
  for r in $(seq 1 "$REPS"); do
    echo "-- Execução $r/$REPS" | tee -a "$OUT" >/dev/null
    # Redireciona stdout (solução) para /dev/null.
    # Captura stderr, filtra apenas a linha de tempo do OMP (evita avisos confundir o log)
    __tmp=".__bench_tmp_$$.$RANDOM"
    ./jacobi_omp --in "$IN" $args 1>/dev/null 2>"$__tmp" || true
    grep -F "[omp]" "$__tmp" >>"$OUT" || true
    rm -f "$__tmp"
  done
done

echo "" | tee -a "$OUT" >/dev/null
echo "Concluído. Resultados em: $OUT" | tee -a "$OUT" >/dev/null
