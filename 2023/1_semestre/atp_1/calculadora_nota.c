#include <stdio.h>

int main(){
    double nota1, nota2, media;
    
    printf("Digite a primeira nota(0-10):  ");
    scanf("%lf", &nota1);

    printf("\n");

    printf("Digite a segunda nota(0-10):  ");
    scanf("%lf", &nota2);

    printf("\n");

    if(nota1 < 0 || nota2 < 0){
        printf("Notas negativas não existem!!");
        return 0;
    }

    media = (nota1 + nota2) / 2;

    if(media >= 5)
        printf("Sua media e: %.2f\t Aprovado!", media);
    else
        printf("Sua media e: %.2f\t Reprovado!", media);

    return 0;
}