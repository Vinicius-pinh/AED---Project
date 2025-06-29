#include<stdio.h>
#include <string.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>


struct dados
{
    char nome[12];
    int idade;
    char paiOumae[12];
};

//**************Funções******************
void entradaDados(int x, int y, int corFundo, int corBorda, int qtdCarateres, char valorDigitado[]);
void jogo(int x1, int y1, int corFundo, int corBorda, char valor[10]);
void palavras(char vet[5][10]);
void nome (struct dados fd1[5]);
void atividadeSoma();
void atividadeSubtracao();
void atividadeOrdenar();
void atividadeCompletar();
void atividadeQuantidade();
void iniciarMatematica();
void moverQuadradoComTeclado();
void faseFormasGeometricas();
void faseObstaculos();
void faseDificil();
void jogoDasFases();

int main()
{
    char vetor[5][10];
    palavras(vetor);
    struct dados d1[5];
    char startoptions[3][22] = {"nome", "idade", "nome do pai ou da mae"};
    int largtel = getmaxwidth();
    int alttel = getmaxheight();
    char entrada[30];
    int botao=13;

    initwindow(300,200,"Dados do aluno",450,180);
    int i;
    for (i=0; i<3; i++)
    {
        outtextxy(20, 20 + i * 60, startoptions[i]);
        entradaDados(20, 40 + i * 60, 2, 7, 10, entrada);
        if(i == 0) strcpy(d1[0].nome, entrada);
        if(i == 1) d1[0].idade = atoi(entrada);
        if (i == 2) strcpy(d1[0].paiOumae, entrada);
    }
    closegraph();

    initwindow(largtel, alttel,"Jogo",0,0);
    readimagefile("fundo.jpg",0,0,largtel,alttel);
    nome(d1);
    iniciarMatematica();


    jogoDasFases();


    getch();
    closegraph();
    return 0;
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
    do
    {
        tecla = getch();
        if (tecla >= 32 && tecla <= 127 && indice < qtdCarateres)
        {
            valorDigitado[indice++] = (char) tecla;
            valorDigitado[indice] = '\0';
        }
        if (tecla == 8 && indice > 0)
        {
            valorDigitado[--indice] = '\0';
        }
        setfillstyle(1,corFundo);
        bar(x,y,x+(qtdCarateres*14),y+30);
        outtextxy(x+4,y+6,valorDigitado);
    }
    while (tecla != 13);
}

void jogo(int x1, int y1, int corFundo, int corBorda, char valor[10])
{
    setfillstyle(1, 0);
    bar(x1, y1+2, x1+100, y1+32);
    setlinestyle(0,0,2);
    setcolor(corBorda);
    rectangle(x1, y1+2, x1+100, y1+32);
    outtextxy(x1+2, y1+2, valor);
}

void palavras(char vet[5][10])
{
    char vet1[5][10] = {"Bola", "Correr", "Pipa", "Familia", "Escola"};
    for (int i = 0; i < 5; i++)
    {
        strcpy(vet[i], vet1[i]);
    }
}

void nome (struct dados fd1[5])
{
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

void atividadeSoma()
{
    cleardevice();
    readimagefile("fundo.jpg", 0, 0, getmaxwidth(), getmaxheight());
    int a = rand()%10, b = rand()%10;
    char pergunta[50], respostaUsuario[5];
    sprintf(pergunta, "Quanto é %d + %d?", a, b);
    outtextxy(100, 100, pergunta);
    entradaDados(100, 140, 15, 7, 3, respostaUsuario);
    int resposta = atoi(respostaUsuario);
    if (resposta == a + b) outtextxy(100, 180, "Muito bem!");
    else outtextxy(100, 180, "Tente novamente!");
    getch();
}

void atividadeSubtracao()
{
    cleardevice();
    readimagefile("fundo.jpg", 0, 0, getmaxwidth(), getmaxheight());
    int a = rand()%10 + 5, b = rand()%5;
    char pergunta[50], respostaUsuario[5];
    sprintf(pergunta, "Quanto é %d - %d?", a, b);
    outtextxy(100, 100, pergunta);
    entradaDados(100, 140, 15, 7, 3, respostaUsuario);
    int resposta = atoi(respostaUsuario);
    if (resposta == a - b) outtextxy(100, 180, "Muito bem!");
    else outtextxy(100, 180, "Tente novamente!");
    getch();
}

void atividadeOrdenar()
{
    cleardevice();
    readimagefile("fundo.jpg", 0, 0, getmaxwidth(), getmaxheight());
    int nums[3];
    char entrada[10];
    nums[0] = rand()%10;
    nums[1] = rand()%10;
    nums[2] = rand()%10;
    char pergunta[100];
    sprintf(pergunta, "Ordene: %d, %d, %d", nums[0], nums[1], nums[2]);
    outtextxy(100, 100, pergunta);
    outtextxy(100, 140, "Digite em ordem ex: 1 2 3");
    entradaDados(100, 180, 15, 7, 9, entrada);
    outtextxy(100, 220, "Ordem recebida: ");
    outtextxy(100, 240, entrada);
    getch();
}

void atividadeCompletar()
{
    cleardevice();
    readimagefile("fundo.jpg", 0, 0, getmaxwidth(), getmaxheight());
    int faltando = rand()%9 + 1;
    char pergunta[100], resposta[5];
    sprintf(pergunta, "%d, __, %d", faltando, faltando + 2);
    outtextxy(100, 100, "Qual número falta?");
    outtextxy(100, 130, pergunta);
    entradaDados(100, 160, 15, 7, 2, resposta);
    if (atoi(resposta) == faltando + 1) outtextxy(100, 200, "Muito bem!");
    else outtextxy(100, 200, "Tente novamente!");
    getch();
}

void atividadeQuantidade()
{
    cleardevice();
    readimagefile("fundo.jpg", 0, 0, getmaxwidth(), getmaxheight());
    int qtd = rand()%5 + 1;
    char simbolo[] = "* ";
    char pergunta[100], resposta[3];
    sprintf(pergunta, "Quantos asteriscos tem: ");
    outtextxy(100, 100, pergunta);
    for (int i = 0; i < qtd; i++)
    {
        outtextxy(100 + i*20, 130, simbolo);
    }
    entradaDados(100, 170, 15, 7, 2, resposta);
    if (atoi(resposta) == qtd) outtextxy(100, 210, "Muito bem!");
    else outtextxy(100, 210, "Tente novamente!");
    getch();
}

void iniciarMatematica()
{
    srand(time(NULL));
    atividadeSoma();
    atividadeSubtracao();
    atividadeOrdenar();
    atividadeCompletar();
    atividadeQuantidade();
}

//--------------- Noção Espacial ------------------------------------------------

void jogoDasFases()
{
    moverQuadradoComTeclado();
    faseFormasGeometricas();
    faseObstaculos();
    faseDificil();
}

// FASE 1:
void moverQuadradoComTeclado()
{
    int x = 100, y = 100;
    int tam = 50;
    int alvoX = 500, alvoY = 300;
    int venceu = 0;

    while (!venceu)
    {
        cleardevice();
        //quadrado verde
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        rectangle(alvoX, alvoY, alvoX + tam, alvoY + tam);
        floodfill(alvoX + 1, alvoY + 1, GREEN);

        // Quadrado rosa
        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        rectangle(x, y, x + tam, y + tam);
        floodfill(x + 1, y + 1, LIGHTMAGENTA);

        outtextxy( 20, 20, "1 FASE: Use as setas para levar o quadrado rosa ao quadrado verde!");

        if (kbhit())
        {
            int tecla = getch();
            if (tecla == 0 || tecla == 224)
            {
                tecla = getch();
                switch (tecla)
                {
                case 72:
                    y -= 10;
                    break;
                case 80:
                    y += 10;
                    break;
                case 75:
                    x -= 10;
                    break;
                case 77:
                    x += 10;
                    break;
                }
            }
        }

        if (x >= alvoX && x <= alvoX + tam &&
                y >= alvoY && y <= alvoY + tam)
        {
            setcolor(WHITE);
            outtextxy(250, 550, "Muito bem! Acertou o quadrado!");
            venceu = 1;
        }

        delay(50);
    }

    getch();
}

// FASE 2:
void faseFormasGeometricas()
{
    cleardevice();

    int tam = 50;
    int cx = 200, cy = 300;
    int tx = 400, ty = 300;
    int rx = 600, ry = 300;
    int x = 100, y = 100;
    int venceu = 0;

    while (!venceu)
    {
        cleardevice();

        outtextxy(10, 10, " 2 Fase: Leve o quadrado rosa ate a forma: TRIANGULO");

        // Círculo
        setcolor(CYAN);
        setfillstyle(SOLID_FILL, CYAN);
        fillellipse(cx + 25, cy + 25, 30, 30);

        // Triângulo
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        int pontos[6] = { tx + 25, ty, tx, ty + 50, tx + 50, ty + 50 };
        fillpoly(3, pontos);

        // Retângulo
        setcolor(LIGHTBLUE);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        bar(rx, ry, rx + 60, ry + 40);

        // Quadrado rosa
        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        rectangle(x, y, x + tam, y + tam);
        floodfill(x + 1, y + 1, LIGHTMAGENTA);

        if (kbhit())
        {
            int tecla = getch();
            if (tecla == 0 || tecla == 224)
            {
                tecla = getch();
                switch (tecla)
                {
                case 72:
                    y -= 10;
                    break;
                case 80:
                    y += 10;
                    break;
                case 75:
                    x -= 10;
                    break;
                case 77:
                    x += 10;
                    break;
                }
            }
        }

        if (x + tam > tx && x < tx + 50 &&
                y + tam > ty && y < ty + 50)
        {
            setcolor(WHITE);
            outtextxy(250, 550, "Muito bem! Você acertou o TRIÂNGULO!");
            venceu = 1;
        }

        delay(50);
    }

    getch();
}

// FASE 3:
void faseObstaculos()
{
    cleardevice();

    int x = 50, y = 500;
    int tam = 40;
    int estrelaX = 700, estrelaY = 50;
    int venceu = 0;

    struct Obstacle
    {
        int x1, y1, x2, y2;
    } obs[3] =
    {
        {200, 200, 400, 230},
        {300, 400, 500, 430},
        {150, 100, 300, 130}
    };

    while (!venceu)
    {
        cleardevice();

        outtextxy(10, 10, " Fase 3: Leve o quadrado rosa ate a ESTRELA sem encostar nos obstáculos!");

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        for (int i = 0; i < 3; i++)
        {
            bar(obs[i].x1, obs[i].y1, obs[i].x2, obs[i].y2);
        }

        setcolor(YELLOW);
        setlinestyle(0, 0, 3);
        line(estrelaX, estrelaY, estrelaX + 30, estrelaY + 30);
        line(estrelaX + 30, estrelaY, estrelaX, estrelaY + 30);

        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        rectangle(x, y, x + tam, y + tam);
        floodfill(x + 1, y + 1, LIGHTMAGENTA);

        if (kbhit())
        {
            int tecla = getch();
            if (tecla == 0 || tecla == 224)
            {
                tecla = getch();
                switch (tecla)
                {
                case 72:
                    y -= 10;
                    break;
                case 80:
                    y += 10;
                    break;
                case 75:
                    x -= 10;
                    break;
                case 77:
                    x += 10;
                    break;
                }
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (x + tam > obs[i].x1 && x < obs[i].x2 &&
                    y + tam > obs[i].y1 && y < obs[i].y2)
            {
                setcolor(WHITE);
                outtextxy(300, 570, "Tente novamente! Você encostou no obstáculo.");
                delay(1000);
                x = 50;
                y = 500;
            }
        }

        if (x + tam > estrelaX && x < estrelaX + 30 &&
                y + tam > estrelaY && y < estrelaY + 30)
        {
            setcolor(WHITE);
            outtextxy(300, 500, "Parabéns! Você venceu a fase dos obstáculos!");
            venceu = 1;
        }

        delay(50);
    }

    getch();
}

// FASE 4:
void faseDificil()
{
    cleardevice();

    int x = 50, y = 550;
    int tam = 40;
    int estrelaX = 720, estrelaY = 30;
    int venceu = 0;

    struct Obstacle
    {
        int x1, y1, x2, y2;
    };

    struct Obstacle obs[8] =
    {
        {150, 100, 220, 130},
        {250, 200, 320, 230},
        {350, 350, 410, 380},
        {470, 150, 530, 180},
        {600, 300, 660, 330},
        {180, 450, 240, 480},
        {400, 500, 460, 530},
        {550, 420, 610, 450}
    };

    while (!venceu)
    {
        cleardevice();

        outtextxy(10, 10, " 4 FASE : Leve o quadrado rosa ate a ESTRELA sem encostar!");

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        for (int i = 0; i < 8; i++)
        {
            bar(obs[i].x1, obs[i].y1, obs[i].x2, obs[i].y2);
        }

        setcolor(YELLOW);
        setlinestyle(0, 0, 3);
        line(estrelaX, estrelaY + 15, estrelaX + 30, estrelaY + 45);
        line(estrelaX + 30, estrelaY + 15, estrelaX, estrelaY + 45);
        line(estrelaX + 15, estrelaY, estrelaX + 15, estrelaY + 45);
        line(estrelaX, estrelaY + 30, estrelaX + 30, estrelaY + 30);

        setcolor(LIGHTMAGENTA);
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        rectangle(x, y, x + tam, y + tam);
        floodfill(x + 1, y + 1, LIGHTMAGENTA);

        if (kbhit())
        {
            int tecla = getch();
            if (tecla == 0 || tecla == 224)
            {
                tecla = getch();
                switch (tecla)
                {
                case 72:
                    y -= 10;
                    break;
                case 80:
                    y += 10;
                    break;
                case 75:
                    x -= 10;
                    break;
                case 77:
                    x += 10;
                    break;
                }
            }
        }

        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + tam > getmaxwidth()) x = getmaxwidth() - tam;
        if (y + tam > getmaxheight()) y = getmaxheight() - tam;

        for (int i = 0; i < 8; i++)
        {
            if (x + tam > obs[i].x1 && x < obs[i].x2 &&
                    y + tam > obs[i].y1 && y < obs[i].y2)
            {
                setcolor(WHITE);
                outtextxy(250, 570, "Voce encostou no obstaculo! Tente novamente.");
                delay(1000);
                x = 50;
                y = 550;
            }
        }

        if (x + tam > estrelaX && x < estrelaX + 30 &&
                y + tam > estrelaY && y < estrelaY + 45)
        {
            setcolor(WHITE);
            outtextxy(250, 500, "Parabens! Voce venceu a 4 fase !");
            venceu = 1;
        }

        delay(50);
    }

    getch();
}
