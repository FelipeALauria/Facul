#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para contar quantos caracteres são dígitos em uma string.
int contador(const char *cont);

// Função para converter uma string em um número de ponto flutuante.
double strd(const char *str);

// Função para contar as casas decimais.
int countdc(double num);

int main() {
  int d;
  char m[16];

  // Abre os arquivos para leitura e escrita.
  FILE *ent = fopen("entrada.dat", "r");
  FILE *inte = fopen("inteiros.dat", "w");
  FILE *re = fopen("reais.dat", "w");

  // Verifica se os arquivos foram abertos corretamente.
  if (ent == NULL || inte == NULL || re == NULL) {
    printf("Não é possível abrir um dos arquivos!");
    return 1;
  }

  // Ler valores do arquivo de entrada
  while (fscanf(ent, "%s", m) == 1) {
    d = 0;
    // Conta quantos caracteres são dígitos na string 'm'.
    int count = contador(m);

    for (int i = 0; m[i] != '\0'; i++) {
      if (m[i] == '.') {
        d = 1;
        break;
      }
    }

    // Se todos os caracteres são dígitos, é um número inteiro.
    double num = strd(m);
    if (d == 0) {
      if (num >= 0) {
        fprintf(inte, "%.0lf %.0lf\n", num, 1000000 - num);
      } else {
        fprintf(inte, "%.0lf %.0lf\n", num, -(num + 100000));
      }
    } else {
      // Se não são todos dígitos, é um número real.
      int casas_decimais = countdc(num);
      double aux = 0;
      fprintf(re, "%.*lf ", casas_decimais, num);
      if (num > 0) {
        aux = 1000000.0 - num;
        casas_decimais = countdc(aux);
        fprintf(re, "%.*lf\n", casas_decimais, aux);
      } else {
        aux = -(num + 1000000.0);
        casas_decimais = countdc(aux);
        fprintf(re, "%.*lf\n", casas_decimais, aux);
      }
    }
  }

  // Fecha os arquivos.
  fclose(ent);
  fclose(inte);
  fclose(re);

  return 0;
}

// Função para contar quantos caracteres são dígitos em uma string.
int contador(const char *cont) {
  int con = 0;
  for (int i = 0; i < 16; i++) {
    // Verifica se o caractere é um dígito ou o sinal de positivo/negativo.
    if (isdigit(cont[i]) || (i == 0 && (cont[i] == '+' || cont[i] == '-'))) {
      con++;
    }
  }
  return con;
}

// Função para converter uma string em um double.
double strd(const char *str) {
  double res = 0.0;
  double fat = 0.1;
  int po = 0;
  int negativo = 0;

  // Verifica se a string começa com sinal de negativo.
  if (str[0] == '-') {
    negativo = 1;
  } else {
    negativo = 0;
  }

  for (int i = negativo; str[i] != '\0'; i++) {
    // Verifica se o caractere é um dígito.
    if (isdigit(str[i])) {
      if (po == 1) {
        res += fat * (str[i] - 48);
        fat *= 0.1;
      } else {
        res = res * 10 + (str[i] - 48);
      }
    } else if (str[i] == '.') {
      po = 1;
    }
  }

  // Se o número for negativo, multiplica por -1.
  if (negativo) {
    res = -res;
  }

  return res;
}

// Função para contar as casas decimais.
int countdc(double num) {
  char str[16];
  snprintf(str, sizeof(str), "%lf", num);

  int count = 0;
  int flag = 0; // Flag para indicar que um dígito não-zero foi encontrado.

  for (int i = 0; str[i] != '\0'; i++) {
    flag = 0;
    if (str[i] == '.') {
      flag = 0; // Reinicie a flag quando encontrar o ponto decimal.
      count = 0;
    } else if (str[i] != '0') {
      flag = 1;
    }

    if (flag && count < 6) {
      count++;
    }
  }

  return count;
}
