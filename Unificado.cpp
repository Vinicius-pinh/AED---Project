
#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

//-------------------Structs-------------------------------
struct dados
{
    char nome[12];
    int idade;
    char paiOumae[12];
};

//--------------------- Declarações das funções------------------------------
void entradaDados(int x1, int y1, int corFundo, int corBorda, int qtdCarateres, char valorDigitado[]);
void jogo(int x1, int y1, int corFundo, int corBorda, char valor[10]);
void palavras_com_descricoes(char vet[5][10], char descricoes[5][40]);
void nome(struct dados fd1[5]);
void cria_matriz(struct dados fd1[5]);
void clique(int *x, int *y);
void embaralha_campos(struct dados vet[5], struct dados meusDados);
void desenha_colunas();
void desenha_jogo_palavras(char palavras[5][10], char descricoes[5][40]);
void embaralha_descricoes(char descricoes[5][40]);
void ligar_pontos(int x1, int y1, int x2, int y2);
int encontrar_indice_descricao_original(char descricoes_embaralhadas[5][40], char descricoes_originais[5][40], int index);
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
    srand(time(NULL));
    struct dados d1[5];
    struct dados meusDados;
    char entrada[30];
    int largtel = getmaxwidth();
    int alttel = getmaxheight();

    //------------------- Coleta os dados do aluno ------------------------
    initwindow(300, 200, "Dados do aluno", 450, 180);
    char startoptions[3][22] = {"nome", "idade", "nome do pai ou da mae"};

    for (int i = 0; i < 3; i++)
    {
        outtextxy(20, 20 + i * 60, startoptions[i]);
        entradaDados(20, 40 + i * 60, 2, 7, 10, entrada);
        if (i == 0)strcpy(d1[0].nome, entrada);
        if (i == 1) d1[0].idade = atoi(entrada);
        if (i == 2) strcpy(d1[0].paiOumae, entrada);
    }
    meusDados = d1[0];
    closegraph();

    //-------------- Jogo 1: Identificação dos dados--------------------
    initwindow(largtel, alttel, "Jogo 1 - Identifique seus dados", 0, 0);
    readimagefile("fundo.jpg", 0, 0, largtel, alttel);
    nome(d1);
    embaralha_campos(d1, meusDados);
    desenha_colunas();
    cria_matriz(d1);

    int mx, my;
    int acertouNome = 0, acertouIdade = 0, acertouResponsavel = 0;

    while (!(acertouNome && acertouIdade && acertouResponsavel))
    {
        clique(&mx, &my);
        int col = (mx - 150) / 150;
        int lin = (my - 200) / 65;

        if (col >= 0 && col < 3 && lin >= 0 && lin < 5)
        {
            int x1 = 150 + col * 150;
            int y1 = 200 + lin * 65;
            int x2 = x1 + 100;
            int y2 = y1 + 30;

            if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2)
            {
                int acerto = 0;

                if (col == 0 && strcmp(meusDados.nome, d1[lin].nome) == 0)
                {
                    acertouNome = 1;
                    acerto = 1;
                }
                else if (col == 1 && meusDados.idade == d1[lin].idade)
                {
                    acertouIdade = 1;
                    acerto = 1;
                }
                else if (col == 2 && strcmp(meusDados.paiOumae, d1[lin].paiOumae) == 0)
                {
                    acertouResponsavel = 1;
                    acerto = 1;
                }

                int cor = acerto ? GREEN : RED;
                setfillstyle(SOLID_FILL, cor);
                bar(x1 + 1, y1 + 1, x1 + 99, y1 + 29);
                setcolor(BLACK);
                rectangle(x1, y1, x1 + 100, y1 + 30);
                setbkcolor(cor);

                char texto[20];
                if (col == 0) strcpy(texto, d1[lin].nome);
                else if (col == 1) sprintf(texto, "%d", d1[lin].idade);
                else strcpy(texto, d1[lin].paiOumae);
                outtextxy(x1 + 2, y1 + 8, texto);

                if (!acerto)
                {
                    delay(800);
                    readimagefile("fundo.jpg", 0, 0, largtel, alttel);
                    desenha_colunas();
                    cria_matriz(d1);
                }
            }
        }
    }

    //-------------------------- Tela de parabéns ----------------------------
    cleardevice();
    setbkcolor(WHITE);
    setcolor(BLUE);
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    outtextxy(largtel / 2 - 250, alttel / 2 - 50, "Parabéns!");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(largtel / 2 - 180, alttel / 2 + 20, "Você encontrou todos os seus dados!");
    delay(3000);
    closegraph();

    //-------------------------- Jogo 2: Associação de Palavras----------------
    initwindow(largtel, alttel, "Jogo 2 - Associe Palavras", 0, 0);
    readimagefile("fundo.jpg", 0, 0, largtel, alttel);

    char palavrasVet[5][10];
    char descricoesOriginais[5][40];
    char descricoes[5][40];

    palavras_com_descricoes(palavrasVet, descricoesOriginais);
    memcpy(descricoes, descricoesOriginais, sizeof(descricoes));
    embaralha_descricoes(descricoes);
    desenha_jogo_palavras(palavrasVet, descricoes);

    int px = 0, py = 0, sel1 = -1, sel2 = -1;
    int acertos = 0;
    int acertosFeitos[5] = {0, 0, 0, 0, 0}; // Evita contar o mesmo acerto várias vezes

    while (1)
    {
        clique(&px, &py);

        for (int i = 0; i < 5; i++)
        {
            if (px > 100 && px < 300 && py > 150 + i * 60 && py < 180 + i * 60)
                sel1 = i;
            if (px > 600 && px < 850 && py > 150 + i * 60 && py < 180 + i * 60)
                sel2 = i;
        }

        if (sel1 != -1 && sel2 != -1)
        {
            int indiceOriginal = encontrar_indice_descricao_original(descricoes, descricoesOriginais, sel2);
            int cor = (sel1 == indiceOriginal) ? GREEN : RED;
            if (sel1 == indiceOriginal && !acertosFeitos[sel1])
            {
                acertos++;
                acertosFeitos[sel1] = 1;
            }
            setcolor(cor);
            ligar_pontos(300, 165 + sel1 * 60, 600, 165 + sel2 * 60);

            delay(800);
            if (cor == RED)
            {
                readimagefile("fundo.jpg", 0, 0, largtel, alttel);
                palavras_com_descricoes(palavrasVet, descricoesOriginais);
                memcpy(descricoes, descricoesOriginais, sizeof(descricoes));
                embaralha_descricoes(descricoes);
                desenha_jogo_palavras(palavrasVet, descricoes);
            }

            sel1 = sel2 = -1;
            if (acertos == 5)
            {
                delay(1000);
                cleardevice();
                setbkcolor(WHITE);
                setcolor(BLUE);
                settextstyle(BOLD_FONT, HORIZ_DIR, 5);
                outtextxy(largtel / 2 - 320, alttel / 2 - 50, "Parabéns!");
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                outtextxy(largtel / 2 - 280, alttel / 2 + 20, "Você ligou todos os objetos corretamente!");
                delay(3000);
                break;
            }
        }
    }

    //---------------------Jogo 3: Atividades Matemáticas--------------------------------
    iniciarMatematica();

    getch();
    closegraph();


    initwindow(largtel, alttel,"Jogo",0,0);

    //-------------------Jogo 4: Fases--------------------------------------------------
    jogoDasFases();


    getch();
    closegraph();
    return 0;

}

// ------------------------- Funções Auxiliares para os Jogos ---------------------------
void entradaDados(int x, int y, int corFundo, int corBorda, int qtdCarateres, char valorDigitado[])
{
    int indice = 0, tecla;
    setfillstyle(1, corFundo);
    bar(x, y, x + (qtdCarateres * 14), y + 30);
    setlinestyle(0, 0, 2);
    setcolor(corBorda);
    rectangle(x - 3, y - 3, x + (qtdCarateres * 14) + 2, y + 32);
    setbkcolor(corFundo);
    strcpy(valorDigitado, "");

    do
    {
        tecla = getch();
        if (tecla >= 32 && tecla <= 127)
        {
            valorDigitado[indice++] = (char)tecla;
            valorDigitado[indice] = '\0';
            bar(x, y, x + (qtdCarateres * 14), y + 30);
            outtextxy(x + 4, y + 6, valorDigitado);
        }
        if (tecla == 8 && indice > 0)
        {
            valorDigitado[--indice] = '\0';
            bar(x, y, x + (qtdCarateres * 14), y + 30);
            outtextxy(x + 4, y + 6, valorDigitado);
        }
    }
    while (tecla != 13 && indice < qtdCarateres);
}

void jogo(int x1, int y1, int corFundo, int corBorda, char valor[10])
{
    setfillstyle(1, 0);
    setlinestyle(0, 0, 2);
    setcolor(corBorda);
    rectangle(x1, y1 + 2, x1 + 100, y1 + 32);
    setbkcolor(15);
    outtextxy(x1 + 2, y1 + 2, valor);
}

// Funções do Jogo 1
void nome(struct dados fd1[5])
{
    strcpy(fd1[1].nome, "Caio");
    fd1[1].idade = 14;
    strcpy(fd1[1].paiOumae, "Clara");
    strcpy(fd1[2].nome, "Fabio");
    fd1[2].idade = 2;
    strcpy(fd1[2].paiOumae, "Pedro");
    strcpy(fd1[3].nome, "Ana");
    fd1[3].idade = 10;
    strcpy(fd1[3].paiOumae, "Antonio");
    strcpy(fd1[4].nome, "Gabi");
    fd1[4].idade = 7;
    strcpy(fd1[4].paiOumae, "Augusta");
}

void embaralha_campos(struct dados vet[5], struct dados meusDados)
{
    char nomes[5][12], pais[5][12];
    int idades[5];
    for (int i = 0; i < 5; i++)
    {
        strcpy(nomes[i], vet[i].nome);
        strcpy(pais[i], vet[i].paiOumae);
        idades[i] = vet[i].idade;
    }
    for (int i = 4; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char tmp[12];
        int tmpI;
        strcpy(tmp, nomes[i]);
        strcpy(nomes[i], nomes[j]);
        strcpy(nomes[j], tmp);
        strcpy(tmp, pais[i]);
        strcpy(pais[i], pais[j]);
        strcpy(pais[j], tmp);
        tmpI = idades[i];
        idades[i] = idades[j];
        idades[j] = tmpI;
    }
    for (int i = 0; i < 5; i++)
    {
        strcpy(vet[i].nome, nomes[i]);
        vet[i].idade = idades[i];
        strcpy(vet[i].paiOumae, pais[i]);
    }
}

void cria_matriz(struct dados fd1[5])
{
    int k;
    for (int i = 0; i < 5; i++)
    {
        k = 150;
        for (int j = 0; j < 3; j++)
        {
            if (j == 0) jogo(k, 200 + i * 65, 100, 30, fd1[i].nome);
            else if (j == 1)
            {
                char idadeStr[5];
                sprintf(idadeStr, "%d", fd1[i].idade);
                jogo(k, 200 + i * 65, 100, 30, idadeStr);
            }
            else jogo(k, 200 + i * 65, 100, 30, fd1[i].paiOumae);
            k += 150;
        }
    }
}

void desenha_colunas()
{
    outtextxy(165, 170, "Nome");
    outtextxy(315, 170, "Idade");
    outtextxy(465, 170, "Responsavel");
}

void clique(int *x, int *y)
{
    while (!ismouseclick(WM_LBUTTONDOWN)) delay(10);
    getmouseclick(WM_LBUTTONDOWN, *x, *y);
}

// Funções do Jogo 2
void palavras_com_descricoes(char vet[5][10], char descricoes[5][40])
{
    strcpy(vet[0], "Bola");
    strcpy(descricoes[0], "Objeto usado para jogar futebol");
    strcpy(vet[1], "Pipa");
    strcpy(descricoes[1], "Brinquedo que voa com o vento");
    strcpy(vet[2], "Escola");
    strcpy(descricoes[2], "Lugar onde se aprende");
    strcpy(vet[3], "Familia");
    strcpy(descricoes[3], "Conjunto de pessoas que moram juntas");
    strcpy(vet[4], "Correr");
    strcpy(descricoes[4], "Atividade de se mover rapidamente");
}

void embaralha_descricoes(char descricoes[5][40])
{
    for (int i = 4; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp[40];
        strcpy(temp, descricoes[i]);
        strcpy(descricoes[i], descricoes[j]);
        strcpy(descricoes[j], temp);
    }
}

int encontrar_indice_descricao_original(char descricoes_embaralhadas[5][40], char descricoes_originais[5][40], int index)
{
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(descricoes_embaralhadas[index], descricoes_originais[i]) == 0)
            return i;
    }
    return -1;
}

void desenha_jogo_palavras(char palavras[5][10], char descricoes[5][40])
{
    setbkcolor(WHITE);
    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    for (int i = 0; i < 5; i++)
    {
        rectangle(100, 150 + i * 60, 300, 180 + i * 60);
        outtextxy(110, 155 + i * 60, palavras[i]);
        rectangle(600, 150 + i * 60, 850, 180 + i * 60);
        outtextxy(610, 155 + i * 60, descricoes[i]);
    }
    outtextxy(100, 80, "Associe a palavra com sua descricao clicando em ambos!");
}

void ligar_pontos(int x1, int y1, int x2, int y2)
{
    line(x1, y1, x2, y2);
}

// Funções do Jogo 3 (Matemática)
void atividadeSoma()
{
    cleardevice();
    readimagefile("fundo.jpg", 0, 0, getmaxwidth(), getmaxheight());
    int a = rand() % 10, b = rand() % 10;
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
    int a = rand() % 10 + 5, b = rand() % 5;
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
