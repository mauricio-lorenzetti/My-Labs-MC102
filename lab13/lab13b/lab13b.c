/* Nome: Mauricio Lorenzetti Bezerra
 * RA: 156754
 * Laboratorio 06b - Fruit Crush Saga - Part III */

#include <stdio.h>
#define MAX 51

/* Aplica o efeito gravidade as frutas marcadas, considerando os blocos de gelo */
void aplicaGravidade(int nColunas, int mLinhas, char tabuleiro[][MAX]){
    
    int i, j, aponta;
    
    /* Retira as frutas marcadas e desce as frutas acima de suas posicoes */ 
    for (j = 0; j < nColunas; j++)
        for (i = 0; i < mLinhas; i++)
            if (tabuleiro[i][j] == 'X'){
                for (aponta = i; aponta > 0 && tabuleiro[aponta][j] != '.' && tabuleiro[aponta-1][j] != '*'; aponta--)
                    tabuleiro[aponta][j] = tabuleiro[aponta-1][j];
    /* Retira frutas marcadas sob blocos de gelo e na primeira linha */
                if (aponta == 0 || tabuleiro[aponta-1][j] == '*')
                    tabuleiro[aponta][j] = '.';
            }
}

/* Marca as frutas a serem retiradas e retorna quantas frutas foram marcadas */
int marcaFrutas(int nColunas, int mLinhas, int linJogada, int colJogada, int frutaEscolhida, char tabuleiro[][MAX]){
    
    int i, j, direcao, frutasMarcadas = 0;

    /* Verifica por frutas nas quatro direcoes adjacentes */
    for (direcao = 0; direcao < 4; direcao++){
    /* Incrementa ou decrementa a posicao verificada pelo resultado booleano de dois testes */
        i = linJogada + (direcao == 2) - (direcao == 0);
        j = colJogada + (direcao == 3) - (direcao == 1);
    
    /* Compara a fruta verificada com a escolhida e garante que esteja dentro do tabuleiro */
        if ((i >= 0) && (j >= 0) && (i < mLinhas) && (j < nColunas) && tabuleiro[i][j] == frutaEscolhida){
    /* Se a comparacao for valida, marca essa fruta e verifica suas adjacencias por recursao */        
            tabuleiro[i][j] = 'X';
            frutasMarcadas++;
            frutasMarcadas += marcaFrutas(nColunas, mLinhas, i, j, frutaEscolhida, tabuleiro);
        }
    }
    
    /* Retorna a quantidade de frutas marcadas para serem retiradas */
    return frutasMarcadas;
}

/* Realiza a jogada no tabuleiro e retorna a pontuacao dessa jogada */
int realizaJogada(int nColunas, int mLinhas, char tabuleiro[][MAX]){
    
    int frutaEscolhida, linJogada, colJogada, score = 0;
        
    /* Obtem as coordenadas da jogada e prepara tais variaveis para uso */
    scanf("%d %d", &linJogada, &colJogada);            
    linJogada--;
    colJogada--;
    frutaEscolhida = tabuleiro[linJogada][colJogada];
    
    /* Verifica se ha fruta na casa selecionada para realizar jogada */
    if (frutaEscolhida != '.' && frutaEscolhida != '*'){
        tabuleiro[linJogada][colJogada] = 'X';
        score++;
        score += marcaFrutas(nColunas, mLinhas, linJogada, colJogada, frutaEscolhida, tabuleiro);
        aplicaGravidade(nColunas, mLinhas, tabuleiro);   
    }
    
    /* Contabiliza a pontuacao da jogada e a pontuacao final ate o momento */
    return score*score;
}

int main() {
    
    /* Declaracao das variaveis utilizadas */
    int i, jogAtual, pontFinal = 0;
    int mLinhas, nColunas, maxJogadas;
    char tabuleiro[MAX][MAX];
    
    /* Obtem os a quantidade de jogadas o tamanho e composicao do tabuleiro */
    scanf ("%d %d %d", &mLinhas, &nColunas, &maxJogadas);
    for (i = 0; i < mLinhas; i++)
           scanf ("%s", tabuleiro[i]);
    
    /* Laco que se repetira tantas vezes quantas jogadas forem feitas   */
    for (jogAtual = 0; jogAtual < maxJogadas; jogAtual++){
        pontFinal += realizaJogada(nColunas, mLinhas, tabuleiro);
    }
    
    /* Imprime na tela o estado e a pontuacao final do tabuleiro */
    printf ("Score: %d\n", pontFinal);
    for (i = 0; i < mLinhas; i++)
            printf ("%s\n", tabuleiro[i]);
    
    return 0;
}
