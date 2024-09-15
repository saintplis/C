#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CLEAR "\033[H\033[2J"

typedef struct {
  int x;
  int y;
} posicao;

typedef struct {
  int x;
  int o;
} ponto;

// função pra dar clear
void clear() {
  printf(CLEAR);
  return;
}

// computador facil posicoes
posicao computadorFacil() {
  posicao comp;
  srand(time(NULL));
  comp.x = rand() % 3;
  comp.y = rand() % 3;
  return comp;
}

// tabuleiro
void imprime_tabuleiro(char tabuleiro[3][3]) {

  clear();

  printf("\t\tJogo da Velha\n");
  printf("Player 1: X\n");
  printf("Player 2: O\n");

  printf("+---+---+---+\n");
  printf("|_%c_|_%c_|_%c_|\n", tabuleiro[0][0], tabuleiro[0][1],
         tabuleiro[0][2]);
  printf("+---+---+---+\n");
  printf("|_%c_|_%c_|_%c_|\n", tabuleiro[1][0], tabuleiro[1][1],
         tabuleiro[1][2]);
  printf("+---+---+---+\n");
  printf("|_%c_|_%c_|_%c_|\n", tabuleiro[2][0], tabuleiro[2][1],
         tabuleiro[2][2]);
  printf("+---+---+---+\n");
  printf("\n");
  return;
}

// verifica se algum jogador ganhou
int verificadorVitoria(char tabuleiro[3][3]) {

  int verificador = 0;

  if (tabuleiro[0][0] != '_' && tabuleiro[0][0] == tabuleiro[0][1] &&
      tabuleiro[0][1] == tabuleiro[0][2]) {
    verificador = 1;
  } else if (tabuleiro[1][0] != '_' && tabuleiro[1][0] == tabuleiro[1][1] &&
             tabuleiro[1][1] == tabuleiro[1][2]) {
    verificador = 1;
  } else if (tabuleiro[2][0] != '_' && tabuleiro[2][0] == tabuleiro[2][1] &&
             tabuleiro[2][1] == tabuleiro[2][2]) {
    verificador = 1;
  } else if (tabuleiro[0][0] != '_' && tabuleiro[0][0] == tabuleiro[1][0] &&
             tabuleiro[1][0] == tabuleiro[2][0]) {
    verificador = 1;
  } else if (tabuleiro[0][1] != '_' && tabuleiro[0][1] == tabuleiro[1][1] &&
             tabuleiro[1][1] == tabuleiro[2][1]) {
    verificador = 1;
  } else if (tabuleiro[0][2] != '_' && tabuleiro[0][2] == tabuleiro[1][2] &&
             tabuleiro[1][2] == tabuleiro[2][2]) {
    verificador = 1;
  } else if (tabuleiro[0][0] != '_' && tabuleiro[0][0] == tabuleiro[1][1] &&
             tabuleiro[1][1] == tabuleiro[2][2]) {
    verificador = 1;
  } else if (tabuleiro[0][2] != '_' && tabuleiro[0][2] == tabuleiro[1][1] &&
             tabuleiro[1][1] == tabuleiro[2][0]) {
    verificador = 1;
  }
  return verificador;
}

// funcao do final do jogo
void final(ponto *pts) {
  clear();
  printf("Fim de Jogo!\n");
  printf(">> Pontos X: %d\n", pts->x);
  printf(">> Pontos O: %d\n", pts->o);
  if (pts->x > pts->o) {
    printf(">> Jogador X venceu!\n");
  } else if (pts->x < pts->o) {
    printf(">> Jogador O venceu!\n");
  } else {
    printf("Empate!\n");
  }
}

// funcao para resetar o tabuleiro
void reset_tabuleiro(char tabuleiro[3][3]) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      tabuleiro[i][j] = '_';
    }
  }
}

// funcao para atribuir os pontos
ponto resultado(int jogador, char tabuleiro[3][3], ponto *pts, int contador) {
  if (verificadorVitoria(tabuleiro) == 1) {
    if (jogador == 0) {
      pts->x += 2;
      clear();
      printf(">> Jogador X venceu!\n");
    } else {
      pts->o += 2;
      clear();
      printf(">> Jogador O venceu!\n");
    }
  } else if (contador == 8) {
    pts->x += 1;
    pts->o += 1;
    clear();
    printf(">> Empate\n");
  }
  reset_tabuleiro(tabuleiro);
  return *pts;
}

// função para escolha do modo de jogo
int modoJogo() {
  int modo;
  printf("Para encerrar o jogo, digite 9 9\n");
  printf("Escolha o modo de jogo \n-> PVP(1)\n-> PVC(2)\nModo: ");
  scanf("%d", &modo);
  clear();
  return modo;
}

// função para escolha da dificuldade do modo PVC
int dificuldadeJogo() {
  int dificuldade;
  printf("Escolha a dificuldade: \n-> Fácil(1)\n-> Difícil(2)\nModo: ");
  scanf("%d", &dificuldade);
  clear();
  return dificuldade;
}

// função para leitura das posições
posicao read() {
  posicao pos;
  printf("-> Digite a posição usando o seguinte formato (linha coluna)\n"),
  printf("Posição: "), scanf("%d %d", &pos.x, &pos.y);
  return pos;
}

// função para rejogar
int rejogar() {

  int continuar;
  printf("Fim da rodada\n\n");
  printf("Escolha\n");
  printf("1: Outra rodada\n");
  printf("2: Finalizar jogo\n");
  printf("Digite: ");
  scanf("%d", &continuar);
  clear();

  return continuar;
}

// funcao do jogo em si
int main(void) {

  posicao cmp, pos;
  ponto pts = {0, 0};
  char tabuleiro[3][3] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};
  char player[2] = {'X', 'O'};
  int jogador = 0, continuar = 0, contador = 0;

  if (modoJogo() == 2) {

    if (dificuldadeJogo() == 1) {
      // Modo PVC Fácil

      imprime_tabuleiro(tabuleiro);
      while (pos = read(), verificadorVitoria(tabuleiro) != 1) {

        jogador = 0;
        if (tabuleiro[pos.x][pos.y] != '_') {
          printf("-> Posição inválida! Jogue novamente:\n");
          continue;
        }

        tabuleiro[pos.x][pos.y] = player[jogador];

        imprime_tabuleiro(tabuleiro);

        if (verificadorVitoria(tabuleiro) != 1 && contador < 8) {
          while (cmp = computadorFacil(), tabuleiro[cmp.x][cmp.y] != '_') {
          }
          
          jogador = 1;
          // joga para o computador
          tabuleiro[cmp.x][cmp.y] = player[jogador];

          contador++;

          imprime_tabuleiro(tabuleiro);
        }
        
        if (verificadorVitoria(tabuleiro) == 1 || contador == 8) {
          resultado(jogador, tabuleiro, &pts, contador);

          contador = 0;
          continuar = rejogar();
          if (continuar == 1) {
            imprime_tabuleiro(tabuleiro);
            continue;
          } else {
            break;
          }
        }
        contador++;
      }

    } else {
      // Modo PVC Díficil

      while (pos = read(), verificadorVitoria(tabuleiro) != 1) {
      }
    }
  } else {
    // Modo PVP
    
    imprime_tabuleiro(tabuleiro);
    while (pos = read(), verificadorVitoria(tabuleiro) != 1) {

      imprime_tabuleiro(tabuleiro);

      // alternacia
      // jogador 0 = X
      // jogador 1 = O (bolinha)
      if (contador % 2 == 0)
        jogador = 0;
      else
        jogador = 1;

      // verificando se já foi jogado naquela posicao
      if (tabuleiro[pos.x][pos.y] != '_') {
        printf("-> Posição inválida! Jogue novamente:\n");
        continue;
      }

      // marcando a jogada do jogador
      tabuleiro[pos.x][pos.y] = player[jogador];

      imprime_tabuleiro(tabuleiro);

      // atribuição de pontos e reset do jogo
      if (verificadorVitoria(tabuleiro) == 1 || contador == 8) {
        resultado(jogador, tabuleiro, &pts, contador);

        contador = 0;
        continuar = rejogar();
        if (continuar == 1) {
          imprime_tabuleiro(tabuleiro);
          continue;
        } else {
          break;
        }
      }
      contador++;
    }
  }
  final(&pts);
  return 0;
}

// jogo normal
// O O -

// defesa
// X X O

// ataque
// O O O
