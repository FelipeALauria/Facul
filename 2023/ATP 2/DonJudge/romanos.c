#include <stdio.h>
#include <string.h>

void romanoParaNumero(int *soma);
void numeroParaRomano();
int valorRomano(char c);
char caracterRomano(int *x);

void romanoParaNumero(int *soma){
    char str[20], c, aux;
    int len, n;
    scanf("%s", str);

    len = strlen(str);
    n = 0;

    c = str[0];
    n += valorRomano(c);
    aux = c;

    for (int i = 1; i < len; i++)
    {
        c = str[i];

        if (valorRomano(aux) <  valorRomano(c))
        {
            n -= valorRomano(aux);
            n += valorRomano(c) - valorRomano(aux);
        }
        else
            n += valorRomano(c);

        aux = c;
    }

    *soma += n;

    printf("%d\n", n);
}

void numeroParaRomano(){
    int num;
    scanf("%d", &num);
    char roman[20];
    int i = 0;

    while (num > 0)
    {
        if (num >= 1000)
        {
            roman[i++] = 'M';
            num -= 1000;
        }
        else if (num >= 900)
        {
            roman[i++] = 'C';
            roman[i++] = 'M';
            num -= 900;
        }
        else if (num >= 500)
        {
            roman[i++] = 'D';
            num -= 500;
        }
        else if (num >= 400)
        {
            roman[i++] = 'C';
            roman[i++] = 'D';
            num -= 400;
        }
        else if (num >= 100)
        {
            roman[i++] = 'C';
            num -= 100;
        }
        else if (num >= 90)
        {
            roman[i++] = 'X';
            roman[i++] = 'C';
            num -= 90;
        }
        else if (num >= 50)
        {
            roman[i++] = 'L';
            num -= 50;
        }
        else if (num >= 40)
        {
            roman[i++] = 'X';
            roman[i++] = 'L';
            num -= 40;
        }
        else if (num >= 10)
        {
            roman[i++] = 'X';
            num -= 10;
        }
        else if (num >= 9)
        {
            roman[i++] = 'I';
            roman[i++] = 'X';
            num -= 9;
        }
        else if (num >= 5)
        {
            roman[i++] = 'V';
            num -= 5;
        }
        else if (num >= 4)
        {
            roman[i++] = 'I';
            roman[i++] = 'V';
            num -= 4;
        }
        else
        {
            roman[i++] = 'I';
            num--;
        }
    }

    roman[i] = '\0';
    printf("%s\n", roman);
}

int valorRomano(char c){
    if (c == 'I')
        return 1;
    else if (c == 'V')
        return 5;
    else if (c == 'X')
        return 10;
    else if (c == 'L')
        return 50;
    else if (c == 'C')
        return 100;
    else if (c == 'D')
        return 500;
    else if (c == 'M')
        return 1000;
}

char caracterRomano(int *x){
    if (*x >= 1000)
    {
        *x -= 1000;
        return 'M';
    }
    else if (*x >= 500)
    {
        *x -= 500;
        return 'D';
    }
    else if (*x >= 100)
    {
        *x -= 100;
        return 'C';
    }
   else if (*x >= 50)
    {
        *x -= 50;
        return 'L';
    }
    else if (*x >= 10)
    {
        *x -= 10;
        return 'X';
    }
    else if (*x >= 5)
    {
        *x -= 5;
        return 'V';
    }
    else if (*x >= 1)
    {
        *x -= 1;
        return 'I';
    }
}

int main()
{
    int N, soma;
    scanf("%d", &N);

    soma = 0;

    for (int i = 0; i < N; i++)
    {
        int C;
        scanf("%d", &C);

        if (C == 1)
            romanoParaNumero(&soma);
        else if (C == 2)
            numeroParaRomano();
    }

    printf("%d\n", soma);

    return 0;
}