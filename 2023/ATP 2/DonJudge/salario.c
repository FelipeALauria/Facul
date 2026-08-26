#include "stdio.h"
#include "string.h"

typedef struct{
    char name[19];
    int ident, hour;
    double salh, salbr, desc, salliq;
}employe;

int main(){
    int n, m, i, a, aux;
    char comp[19];
    printf("");
    scanf("%d %d", &n, &m);
    employe emp[n];
    for(i = 0; i < n; i++){
        printf("");
        scanf("%s %d %lf %d", emp[i].name, &emp[i].ident, &emp[i].salh, &emp[i].hour);
        emp[i].salbr = emp[i].salh * emp[i].hour;
        if(emp[i].salbr < 2000){
          emp[i].desc = 0.00;
        } 
        else if(emp[i].salbr >= 2000 && emp[i].salbr < 5000){
          emp[i].desc = (0.1 * emp[i].salbr) - 200.00;
        }
        else if(emp[i].salbr >= 5000){
          emp[i].desc = (emp[i].salbr * (0.25)) - 950;
        }
        emp[i].salliq = emp[i].salbr - emp[i].desc;
    }
    for(i = 0; i < m; i++){ 
        printf("");
        scanf("%d", &a);
        switch(a){
            case 1 :{
                printf("");
                scanf("%d", &aux);
                for(int j = 0; j < n; j++){
                if(aux == emp[j].ident){
                    printf("%s %d\n", emp[j].name, emp[j].hour);
                    }
                }
              break;
            }
            case 2 :{
                printf("");
                scanf("%s", comp);
                for(int j = 0; j < n; j++){
                    if(strcmp(comp, emp[j].name) == 0){
                        printf("%d %.2lf\n", emp[j].ident, emp[j].salbr);
                    }
                }
              break;
            }
            case 3 :{
                printf("");
                scanf("%d", &aux);
                for(int j = 0; j < n; j++){
                    if(aux == emp[j].ident){
                        printf("%s %.2lf %.2lf\n", emp[j].name, emp[j].desc, emp[j].salliq);
                    }
                }
              break;
            }
        }
    }

    return 0;
}