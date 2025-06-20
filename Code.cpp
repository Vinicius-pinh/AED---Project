#include<stdio.h>
#include <string.h>
#include <graphics.h>
//---struct para dados da criança---//
struct dados{
char nome[30];
int idade;
char paiOuMae[30];
};
//---struct para o jogo de palavras---//
struct alfabeto{
char palavras[15];
};


int main(){

struct dados d1;

printf("Digite os dados da criança\n\n");
printf("===============================\n");
printf("digite o nome\n");
scanf("%s", d1.nome);
printf("digite a idade\n");
scanf("%d", &d1.idade);
printf("digite o nome do pai ou mae da criança\n");
scanf("%s", d1.paiOuMae);

//printf("Nome %s\n, idade %d\n, pai ou mae %s\n", p1.nome, p1.idade, p1.paiOuMae);
struct alfabeto p[5];

strcpy(p[0].palavras, "Bola");
strcpy(p[1].palavras, "Correr");
strcpy(p[2].palavras, "Pipa");
strcpy(p[3].palavras, "Familia");
strcpy(p[4].palavras, "Escola");
int i;
for(i=0; i<5; i++){
printf("%s\n", p[i].palavras);
}

}
