#include<stdio.h>
#include <string.h>
#include <graphics.h>
#include <stdlib.h>
//**************Structs******************
//***************************************
//---struct para dados da criança---
struct dados
{
    char nome[12];
    int idade;
    char paiOumae[12];
};
//---struct para o jogo de palavras---
//***************************************
//**************Functions****************
//---janela de entrada--------------
void entradaDados(int x1, int y1, int corFundo, int corBorda, int qtdCarateres, char valorDigitado[]);
//---Jogos--------------------------
void jogo(int x1, int y1, int corFundo, int corBorda, char valor[10]);
//---Soma---------------------------
int soma(int a, int b);
//---subtrai------------------------
int subtrai(int a, int b);
//---palavras vetor-----------------
void palavras(char vet[5][10]);
//---nome---------------------------
void nome (struct dados fd1[5]);
//***************************************

int main()
{
    char vetor[5][10];
    palavras(vetor);
    //printf("%s, %s, %s, %s, %s", vetor[0], vetor[1], vetor[2], vetor[3], vetor[4]);
    //structs
    struct dados d1[5];
    //variables
    char startoptions[3][22] = {"nome", "idade", "nome do pai ou da mae"};
    int largtel = getmaxwidth();
    int alttel = getmaxheight();
    char entrada[30];
    int botao=13;

    initwindow(300,200,"Dados do aluno",450,180);
    int i;
    for (i=0; i<3; i++)
    {
        outtextxy(20, 20, startoptions[i]);
        entradaDados(20, 40, 2, 7, 10, entrada);
        if(i == 0)
        {
            strcpy(d1[0].nome, entrada);
        }
        if(i == 1)
        {
            d1[0].idade = atoi(entrada);
        }
        if (i == 2)
        {
            strcpy(d1[0].paiOumae, entrada);
        }

    }

    printf("nome %s, idade %d, pais %s", d1[0].nome, d1[0].idade, d1[0].paiOumae);

    // Fecha primeira janela antes de abrir outra
    closegraph();



    initwindow(largtel, alttel,"Jogo",0,0);
    readimagefile("fundo.jpg",0,0,largtel,alttel);
    nome(d1);


    do{
    getch();
    int i=0;
    int n=100;
    jogo(150, 200,2, 7, d1[i].nome);
    n++;
    i++;
    }while (botao == 13 );


    printf("%s, %d, %s\n", d1[0].nome, d1[0].idade, d1[0].paiOumae);
    printf("%s, %d, %s\n", d1[1].nome, d1[1].idade, d1[1].paiOumae);
    printf("%s, %d, %s\n", d1[2].nome, d1[2].idade, d1[2].paiOumae);
    printf("%s, %d, %s\n", d1[3].nome, d1[3].idade, d1[3].paiOumae);
    printf("%s, %d, %s\n", d1[4].nome, d1[4].idade, d1[4].paiOumae);




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

void jogo(int x1, int y1, int corFundo, int corBorda, char valor[10]){
setfillstyle(1, 0);
bar(x1, y1+2, x1+100, y1+32);
setlinestyle(0,0,2);
setcolor(corBorda);
rectangle(x1, y1+2, x1+100, y1+32);
outtextxy(x1+2, y1+2, valor);
}
void palavras(char vet[5][10]) {
    char vet1[5][10] = {
        "Bola",
        "Correr",
        "Pipa",
        "Familia",
        "Escola"
    };
        for (int i = 0; i < 5; i++) {
        strcpy(vet[i], vet1[i]);
    }
}
void nome (struct dados fd1[5]){
strcpy(fd1[1].nome, "Caio");
strcpy(fd1[2].nome, "Fabio");
strcpy(fd1[3].nome, "Ana");
strcpy(fd1[4].nome, "Gabi");
fd1[1].idade = atoi("14");
fd1[2].idade = atoi("2");
fd1[3].idade = atoi("10");
fd1[4].idade = atoi("7");
strcpy(fd1[1].paiOumae, "Clara");
strcpy(fd1[2].paiOumae, "Pedro");
strcpy(fd1[3].paiOumae, "Antonio");
strcpy(fd1[4].paiOumae, "Augusta");
}
