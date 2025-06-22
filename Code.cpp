#include<stdio.h>
#include <string.h>
#include <graphics.h>
#include <stdlib.h>
//***************************************
//**************Functions****************
//---janela de entrada--------------
void entradaDados(int x1, int y1, int corFundo, int corBorda, int qtdCarateres, char valorDigitado[]);
//---Jogos--------------------------
void jogo(int x1, int y1, int corFundo, int corBorda);
//---Soma---------------------------
int soma(int a, int b);
//---subtrai------------------------
int subtrai(int a, int b);
//**************Structs******************
//---struct para dados da criança---
struct dados
{
    char nome[12];
    int idade;
    char paiOumae[12];
};
//---struct para o jogo de palavras---
struct alfabeto
{
    char palavras[15];
};
//***************************************
//***************************************


int main()
{
    //structs
    struct dados d1;
    //variables
    char startoptions[3][22] = {"nome", "idade", "nome do pai ou da mae"};
    int largtel = getmaxwidth();
    int alttel = getmaxheight();
    char entrada[30];

    initwindow(300,200,"Dados do aluno",450,180);
    int i;
    for (i=0; i<3; i++)
    {
        outtextxy(20, 20, startoptions[i]);
        entradaDados(20, 40, 2, 7, 10, entrada);
        if(i == 0)
        {
            strcpy(d1.nome, entrada);
        }
        if(i == 1)
        {
            d1.idade = atoi(entrada);
        }
        if (i == 2)
        {
            strcpy(d1.paiOumae, entrada);
        }

    }
    printf("nome %s, idade %d, pais %s", d1.nome, d1.idade, d1.paiOumae);

    initwindow(largtel, alttel,"Jogo",0,0);
    readimagefile("fundo.jpg",0,0,largtel,alttel);
    jogo(150, 200,2, 7);
    for (i=0; i<3; i){
    printf("teste");
    }




    /*printf("Digite os dados da criança\n\n");
    printf("===============================\n");
    printf("digite o nome\n");
    scanf("%s", d1.nome);
    printf("digite a idade\n");
    scanf("%d", &d1.idade);
    printf("digite o nome do pai ou mae da criança\n");
    scanf("%s", d1.paiOuMae);
    */
//printf("Nome %s\n, idade %d\n, pai ou mae %s\n", p1.nome, p1.idade, p1.paiOuMae);
    struct alfabeto p[5];

    strcpy(p[0].palavras, "Bola");
    strcpy(p[1].palavras, "Correr");
    strcpy(p[2].palavras, "Pipa");
    strcpy(p[3].palavras, "Familia");
    strcpy(p[4].palavras, "Escola");
}

void entradaDados(int x, int y, int corFundo, int corBorda, int qtdCarateres, char valorDigitado[])
{
    int indice = 0, tecla;
    setfillstyle(1, corFundo);
    bar(x,y,x+(qtdCarateres*14),y+30);
    setlinestyle(0,0,2);
    setcolor(corBorda);
    rectangle(x-3,y-3,x+(qtdCarateres*14)+2,y+32);
    setbkcolor(corFundo);
    strcpy(valorDigitado, "");
    indice = 0;
    tecla = 0;

    do
    {
        tecla = getch();
// Teclas do teclado e existentes na Tabela ASCII
        if (tecla >= 32 && tecla <= 127)
        {
            valorDigitado[indice] = (char) tecla;
            indice++;
            valorDigitado[indice] = '\0';
            setfillstyle(1,corFundo);
            bar(x,y,x+(qtdCarateres*14),y+30);
            outtextxy(x+4,y+6,valorDigitado);
        }
        if (tecla == 8) //BackSpace
        {
            if (indice > 0)
            {
                indice--;
                valorDigitado[indice] = '\0';
                setfillstyle(1,corFundo);
                bar(x,y,x+(qtdCarateres*14),y+30);
                outtextxy(x+4,y+6,valorDigitado);
            }
        }
    }
    while (tecla != 13 && indice < qtdCarateres);
// ENTER ou atingiu a quantidade de caracteres
}

void jogo(int x1, int y1, int corFundo, int corBorda){
setfillstyle(1, 0);
bar(x1, y1, x1+50, y1+30);
}
