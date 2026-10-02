/* 
 * @file:   inputs.c
 *          Vasco Almeida
 * @brief várias funções relativas aos inputs utilizados no nosso programa
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "clientes.h"
#include "input.h"
#include "produtos.h"
#include "encomendas.h"
#include "materiais.h"

/**
 * Função que permite a limpeza do buffer
 * 
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * Valida o input de um valor inteiro fornecido pelo utilizador conforme os
 * parâmetros definidos no sistema
 * 
 * @param minValor valor mínimo obrigatório do input
 * @param maxValor valor máximo obrigatório do input
 * @param msg mensagem apresentada ao utilizador para input de valor
 * @return valor inteiro validado
 */
int obterInt(int minValor, int maxValor, char *msg) {
    int valor;
    printf("%s", msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf("%s", msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Valida o input de uma string fornecida pelo utilizador
 * 
 * @param string variável onde a string irá ficar armazenada
 * @param tamanho tamanho alocado à variável onde a string será armazenada
 * @param msg mensagem apresentada ao utilizador para input de string
 */

void lerString(char *string, unsigned int tamanho, char *msg) {
    printf("%s", msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        size_t len = strlen(string);
        if (len > 0 && string[len - 1] == '\n') {
            string[len - 1] = '\0';
        } else if (len == tamanho - 1) {
            cleanInputBuffer();
        }
    }
}

/**
 * Faz a leitura do menu
 * 
 * @param mensagem que vai aparecer na tela
 * @param limite_inferior valor mínimo obrigatório do input
 * @param limite_superior valor máximo obrigatório do input
 * @return valor do perfil selecionado
 */
int leitura_menu(char mensagem[], int limite_inferior, int limite_superior) {
    int perfil;

    while (1) {
        int leitura;
        puts(mensagem);
        leitura = scanf("%d", &perfil);
        if (leitura == EOF) {
            return 0;
        }
        if (leitura == 1 && perfil >= limite_inferior && perfil <= limite_superior) {
            cleanInputBuffer();
            return perfil;
        }
        printf(ERROR);
        cleanInputBuffer();
    }
}

/**
 * Valida o input de um valor fracionário fornecido pelo utilizador conforme os
 * parâmetros definidos no programa 
 * 
 * @param minValor valor mínimo obrigatório do input
 * @param maxValor valor máximo obrigatório do input
 * @param msg mensagem apresentada ao utilizador para input de valor
 * @return valor fracionário validado
 */
float obterFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf("%s", msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf("%s", msg);
    }
    cleanInputBuffer();
    return valor;
}
