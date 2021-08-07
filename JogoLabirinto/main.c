/*
Projeto para a disciplina COM110 - Universidade Federal de Itajub�.
-----------------------------------------------------------------
Equipe de desenvolvimento:
- Augusto Benteu
- Jo�o Lucas Lopes Dias
- Jo�o Victor Gon�alves de Toledo

*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#define H 11
#define W 21
#define L 3

int x = 0, y = 5, currentLevel = 0, points[3] = {5, 5, 5}, finalPoints = 0, highscore, i, j;  // declara��o das vari�veis do tipo int

char  nome[20], recordName[20]; // vetores nome[] e recordName[] que receber�o o nome do jogador

FILE *f;

void draw(int, int); // declara��o da fun��o que desenha o mapa
void control(); // declara��o da fun��o de movimenta��o do personagem
int pontuacao(); // declara��o da fun��o que calcula a pontua��o

void nickname() // fun��o que cria arquivos e guarda o nome e a pontua��o do recordista
{
    f=fopen("highscore.txt","r"); // abre o arquivo txt que guarda o recorde atual
    fscanf(f, "%d", &highscore);
    fclose(f);

    f=fopen("nome.txt","r"); // abre o arquivo txt que guarda o nome do jogador
    fscanf(f, "%s", recordName);
    fclose(f);

    system("cls");
}

void menu() // fun��o do menu inicial que cont�m as op��es para o jogador escolher
{
    nickname();

    int opcao; // vari�vel que controla a op��o escolhida

    printf("Bem-vindo(a) ao Jogo do Labirinto!\n\n------------------------------------\n");
    printf("\nDigite 1 para come�ar o jogo.\n");
    printf("\nDigite 2 para mostrar as instru��es e controles.\n");
    printf("\nDigite 3 para verificar qual � o recorde atual.\n");
    printf("\nDigite 4 para sair.\n\n");

    scanf("%d", &opcao);

    switch(opcao)
    {
    case 1: // inicia o mapa e chama a fun��o control() que permite a movimenta��o do personagem
        draw(0, 0);
        control();
        break;

    case 2: // mostra as regras do jogo
        printf("\nO objetivo do jogo � chegar no portal verde localizado no lado oposto do spawn. \nUse as setinhas do teclado para se mover no mapa.\n\n");
        system("pause");
        printf("\n");
        menu();
        break;

    case 3: // mostra o nome do recordista e quantos pontos ele fez
        printf("\n%s --- %i pontos\n\n", recordName, highscore);
        system("pause");
        printf("\n");
        menu();
        break;

    case 4: // fecha o console
        system("taskkill /IM cb_console_runner.exe");
        break;

    default:
        printf("\nOp��o inv�lida.\n");
        break;
    }
}

void saida() // menu final do jogo que cont�m as op��es de ver o recorde ou sair do jogo
{
    nickname();

    int exit;

    printf("Voc� completou o jogo!\n\n------------------------------------\n");
    printf("\nDigite 1 para verificar o recorde atual.\n");
    printf("\nDigite 2 para sair.\n\n");

    scanf("%d", &exit);

    switch(exit)
    {
    case 1:
        printf("\n%s --- %i pontos\n\n", recordName, highscore);
        system("pause");
        printf("\n");
        saida();
        break;

    case 2:
        system("taskkill /IM cb_console_runner.exe");
        break;

    default:
        printf("\nOp��o inv�lida.\n");
        break;
    }
}

char map[L][H][W] = // mapas do jogo
{
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,5,5,5,5,0,5,5,5,0,5,5,5,5,5,0,5,5,5,4,1},
        {1,0,0,0,0,0,0,0,5,0,5,0,0,0,5,0,0,0,5,0,1},
        {1,0,5,5,5,0,5,5,5,0,5,0,5,0,5,5,5,5,5,5,3},
        {0,0,0,0,5,0,5,0,0,0,5,4,5,0,0,0,0,0,0,0,0},
        {1,0,5,5,5,0,5,0,5,5,5,5,5,0,5,0,5,5,5,0,3},
        {1,0,0,0,5,0,0,0,0,0,0,0,0,0,5,0,0,0,5,0,1},
        {1,5,5,5,5,0,5,5,5,0,5,0,5,5,5,5,5,0,5,0,1},
        {1,0,0,0,0,0,0,4,5,0,5,0,0,0,0,0,5,4,5,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    },

    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,4,5,0,0,0,5,4,0,0,0,0,5,0,0,0,1},
        {1,0,5,5,5,5,5,0,5,5,5,5,5,0,5,0,5,5,5,0,1},
        {1,0,0,0,5,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,1},
        {1,0,5,5,5,5,5,0,5,5,5,5,5,5,5,0,5,5,5,0,3},
        {0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,4,5,0,0},
        {1,0,5,5,5,5,5,5,5,5,5,0,5,0,5,5,5,0,5,0,3},
        {1,0,5,0,5,0,0,0,5,0,0,0,5,0,5,0,5,0,5,0,1},
        {1,0,5,0,5,0,5,0,5,5,5,0,5,0,5,0,5,0,5,0,1},
        {1,0,0,0,0,0,5,4,5,4,0,0,5,0,0,0,0,0,5,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    },

    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,5,0,0,4,5,0,0,0,0,0,0,4,5,0,5,4,0,0,1},
        {1,0,5,0,5,5,5,0,5,5,5,5,5,5,5,0,5,5,5,0,1},
        {1,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,5,5,0,5,5,5,5,5,0,5,0,5,5,5,5,5,5,5,0,3},
        {0,0,0,0,5,0,5,0,5,0,5,0,0,0,0,4,5,0,0,0,0},
        {1,5,5,0,5,0,5,0,5,0,5,0,5,5,5,5,5,5,5,0,3},
        {1,0,0,0,5,0,0,0,0,0,5,0,5,4,5,0,0,0,0,0,1},
        {1,0,5,0,5,0,5,5,5,0,5,0,5,0,5,0,5,0,5,0,1},
        {1,0,5,0,0,0,5,0,0,0,5,0,5,0,0,0,5,0,5,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    },
};

int main() // salva o nome do atual jogador, chama o menu e ativa o jogo
{

    printf("Digite o seu apelido: ");
    scanf("%s", nome);

    menu();

    while(true) // loop para movimenta��o do jogo e condi��o para passar de fase
    {
        control();
        Sleep(200);

        if(map[currentLevel][y-1][x] == 3)
        {
            pontuacao();

            currentLevel++;
            x = 0;
            y = 5;
        }
    }
}

void draw(int py, int px) // fun��o que desenha o mapa e atualiza a posi��o do personagem
{

    map[currentLevel][y][x] = 0;

    x += px;
    y += py;
    map[currentLevel][y][x] = 7;

    system("cls");

    for(i = 0; i < H; i++) // escaneia o mapa e troca n�meros por caracteres ASCII
    {
        for(j = 0; j < W; j++)
        {
            switch(map[currentLevel][i][j])
            {
            case 0:
                printf(" %c ", 255);
                break;
            case 1:
                printf(" %c ", 254);
                break;
            case 3:
                printf("\033[0;32m");
                printf(" %c ", 254);
                printf("\033[0;37m");
                break;
            case 4:
                printf("\033[0;33m");
                printf(" %c ", 004);
                printf("\033[0;37m");
                break;
            case 5:
                printf(" %c ", 254);
                break;
            case 7:
                printf("\033[1;31m");
                printf(" %c ", 254);
                printf("\033[0;37m");
                break;
            }
        }
        printf("\n");
    }
    getch();
}

int pontuacao() // fun��o que calcula a pontua��o por mapa e pontua��o final
{
    if(currentLevel <= 1) // pontua��o dos mapas 1 e 2
    {
        for(i = 0; i < H; i++)
        {
            for(j = 0; j < W; j++)
            {
                if(map[currentLevel][i][j] == 4)
                {
                    points[currentLevel]--;
                }
            }
        }
        printf("\nVoc� chegou no final do mapa %i. Voc� coletou %i pontos. \n\nAperte para a direita com a seta do teclado para ir ao pr�ximo mapa.", currentLevel + 1, points[currentLevel]);
    }
    else // pontua��o final
    {
        for(i = 0; i < H; i++)
        {
            for(j = 0; j < W; j++)
            {
                if(map[currentLevel][i][j] == 4)
                {
                    points[currentLevel]--;
                }
            }
        }

        for(i = 0; i < 3; i++)
        {
            finalPoints += points[i];
        }

        if(finalPoints > highscore) // caso o recorde seja batido mostra a mensagem e atualiza os arquivos
        {

            printf("\nNovo Recorde!!!", finalPoints);

            f=fopen("highscore.txt", "w");
            fprintf(f, "%d", finalPoints);
            fclose(f);

            f=fopen("nome.txt", "w");
            fprintf(f, "%s", nome);
            fclose(f);

            printf("\nVoc� chegou ao final do jogo, parab�ns! Voc� bateu o recorde com %i pontos \n", finalPoints);
        }

        else // caso o recorde n�o seja batido, apenas mostra a pontua��o final
        {
            printf("\nVoc� chegou ao final do jogo, parab�ns! Sua pontua��o final � %i pontos\n", finalPoints);
        }

        system("pause");
        printf("\n");
        saida(); // chama a fun��o do menu do final do jogo
    }
}

void control() // fun��o de movimenta��o e sistema de colis�o
{
         if(GetAsyncKeyState(VK_LEFT)  && (map[currentLevel][y][x-1] == 0 || map[currentLevel][y][x-1] == 2 || map[currentLevel][y][x-1] == 4) ) draw( 0,-1);
    else if(GetAsyncKeyState(VK_RIGHT) && (map[currentLevel][y][x+1] == 0 || map[currentLevel][y][x+1] == 2 || map[currentLevel][y][x+1] == 4) ) draw( 0, 1);
    else if(GetAsyncKeyState(VK_UP)    && (map[currentLevel][y-1][x] == 0 || map[currentLevel][y-1][x] == 2 || map[currentLevel][y-1][x] == 4) ) draw(-1, 0);
    else if(GetAsyncKeyState(VK_DOWN)  && (map[currentLevel][y+1][x] == 0 || map[currentLevel][y+1][x] == 2 || map[currentLevel][y+1][x] == 4) ) draw( 1, 0);
    else if(GetAsyncKeyState(VK_ESCAPE)) exit(0);
}
