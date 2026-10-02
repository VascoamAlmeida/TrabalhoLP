/* 
 * @file:   encomendas.c
 *          Vasco Almeida
 * @brief várias funções relativas as encomendas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "strings.h"
#include "clientes.h"
#include "input.h"
#include "produtos.h"
#include "encomendas.h"
#include "materiais.h"

/**
 * Verifica se um ano e bissexto.
 */
static int ano_bissexto(int ano) {
    return (ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0);
}

/**
 * Devolve o numero de dias de um mes.
 */
static int dias_do_mes(int mes, int ano) {
    static const int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && ano_bissexto(ano)) {
        return 29;
    }
    return dias[mes - 1];
}

/**
 * Valida uma data do calendario.
 */
static int data_valida(Data data) {
    if (data.ano < 1900 || data.mes < 1 || data.mes > 12 || data.dia < 1) {
        return 0;
    }
    return data.dia <= dias_do_mes(data.mes, data.ano);
}

/**
 * Le a data de entrega pretendida para uma encomenda.
 */
static int data_anterior(Data data, Data referencia) {
    if (data.ano != referencia.ano) {
        return data.ano < referencia.ano;
    }
    if (data.mes != referencia.mes) {
        return data.mes < referencia.mes;
    }
    return data.dia < referencia.dia;
}

/**
 * Le a data de entrega pretendida para uma encomenda.
 */
static Data obter_data_entrega(Data data_pedido) {
    Data data;
    int invalida;
    do {
        data.dia = obterInt(1, 31, "Indique o dia de entrega pretendida: ");
        data.mes = obterInt(1, 12, "Indique o mes de entrega pretendida: ");
        data.ano = obterInt(1900, 50000, "Indique o ano de entrega pretendida: ");
        invalida = !data_valida(data) || data_anterior(data, data_pedido);
        if (invalida) {
            printf("Data invalida ou anterior a data do pedido. Tente novamente.\n");
        }
    } while (invalida);
    return data;
}

/**
 * Calcula o dia da semana (segunda=1, ..., domingo=7).
 */
static int dia_da_semana(Data data) {
    static const int tabela[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int ano = data.ano;
    int domingo_zero;

    if (data.mes < 3) {
        ano--;
    }
    domingo_zero = (ano + ano / 4 - ano / 100 + ano / 400 +
            tabela[data.mes - 1] + data.dia) % 7;
    return domingo_zero == 0 ? 7 : domingo_zero;
}

/**
 * Calcula o dia ordinal dentro do ano.
 */
static int dia_do_ano(Data data) {
    int mes, total = data.dia;
    for (mes = 1; mes < data.mes; mes++) {
        total += dias_do_mes(mes, data.ano);
    }
    return total;
}

/**
 * Devolve o numero de semanas ISO existentes num ano.
 */
static int semanas_no_ano(int ano) {
    Data janeiro = {1, 1, ano};
    int dia = dia_da_semana(janeiro);
    return (dia == 4 || (dia == 3 && ano_bissexto(ano))) ? 53 : 52;
}

/**
 * Calcula a semana ISO e o respetivo ano ISO de uma data.
 */
static void semana_iso(Data data, int *semana, int *ano_semana) {
    int valor = (dia_do_ano(data) - dia_da_semana(data) + 10) / 7;
    int ano = data.ano;

    if (valor < 1) {
        ano--;
        valor = semanas_no_ano(ano);
    } else if (valor > semanas_no_ano(ano)) {
        ano++;
        valor = 1;
    }

    *semana = valor;
    *ano_semana = ano;
}

/**
 * Imprime os produtos efetivamente associados a uma encomenda.
 */
static void imprimir_produtos_encomenda(Encomenda *encomenda, Produtos *produtos) {
    int i, indice_produto;

    for (i = 0; i < encomenda->quantProduto; i++) {
        indice_produto = verificacao_procurar_produto(produtos, encomenda->codProduto[i]);
        if (indice_produto != -1) {
            imprimir_produto(&produtos->produtos[indice_produto]);
        } else {
            printf("Codigo do produto: %d |Produto indisponivel no catalogo atual.\\n",
                    encomenda->codProduto[i]);
            printf(SEPARACAO);
        }
    }
}

/**
 * Função que apresenta todas as opções sobre listagem de encomenda
 * 
 * 1- Ver todas encomendas
 * 2- Ver as encomendas entregues
 * 3- Ver as encomendas por entregar
 * 0- Sair
 * @return return valor escolhido pelo utilizador
 */
int encomenda_admin() {
    int opcao;
    opcao = leitura_menu(ADMIN_ENCOMENDA, 0, 3);
    return opcao;
}

/**
 * Função que apresenta todas as opções das encomendas
 * 
 * 1- Ver encomenda
 * 2- Listar encomenda
 * 3- Terminar encomenda
 * 4- Guardar encomenda
 * @return return valor escolhido pelo utilizador
 */
int gestao_encomendas() {
    int opcao;
    opcao = leitura_menu(GESTAO_ENCOMENDAS, 0, 4);
    return opcao;
}

/**
 * Função que permite carregar o ficheiro das encomendas
 * 
 * @param encomendas estrutura as encomendas
 * @param ficheiro ficheiro onde estão as encomendas
 */
void carregar_encomendas(Encomendas *encomendas, char *ficheiro) {
    typedef struct {
        int codEncomenda;
        int codCliente;
        int quantProduto;
        int codProduto[MAX_QUANTIDADE_PRODUTO];
        int quantPagar;
        Data data_pedido;
        Data data_entrega;
    } EncomendaLegacy;

    int i;
    long tamanho_ficheiro = 0;
    FILE *fp = fopen(ficheiro, "rb");

    encomendas->contador = 0;
    encomendas->tamanho_array = 0;
    encomendas->encomenda = NULL;

    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        tamanho_ficheiro = ftell(fp);
        rewind(fp);

        if (fread(&encomendas->contador, sizeof (int), 1, fp) == 1 && encomendas->contador > 0) {
            int formato_antigo = tamanho_ficheiro ==
                    (long) sizeof (int) + (long) encomendas->contador * (long) sizeof (EncomendaLegacy);

            encomendas->tamanho_array = encomendas->contador;
            encomendas->encomenda = (Encomenda *) calloc(
                    encomendas->tamanho_array, sizeof (Encomenda));
            if (encomendas->encomenda == NULL) {
                fclose(fp);
                exit(EXIT_FAILURE);
            }

            for (i = 0; i < encomendas->contador; i++) {
                if (formato_antigo) {
                    EncomendaLegacy antiga;
                    if (fread(&antiga, sizeof (EncomendaLegacy), 1, fp) != 1) {
                        encomendas->contador = i;
                        encomendas->tamanho_array = i;
                        break;
                    }
                    encomendas->encomenda[i].codEncomenda = antiga.codEncomenda;
                    encomendas->encomenda[i].codCliente = antiga.codCliente;
                    encomendas->encomenda[i].quantProduto = antiga.quantProduto;
                    memcpy(encomendas->encomenda[i].codProduto, antiga.codProduto,
                            sizeof (antiga.codProduto));
                    encomendas->encomenda[i].quantPagar = antiga.quantPagar;
                    encomendas->encomenda[i].data_pedido = antiga.data_pedido;
                    encomendas->encomenda[i].data_entrega = antiga.data_entrega;
                    encomendas->encomenda[i].estado =
                            antiga.data_entrega.dia != 0 ? 'E' : 'P';
                } else if (fread(&encomendas->encomenda[i], sizeof (Encomenda), 1, fp) != 1) {
                    encomendas->contador = i;
                    encomendas->tamanho_array = i;
                    break;
                } else if (encomendas->encomenda[i].estado != 'E' &&
                        encomendas->encomenda[i].estado != 'P') {
                    encomendas->encomenda[i].estado = 'P';
                }
            }
        }
        fclose(fp);
    }
}

/**
 * Função verifica se a encomenda foi encontrada ou não no sistema
 * 
 * @param encomendas estrutura as encomendas
 * @param codigo da encomenda que se pretende
 * @return valor -1 se encomenda nao existe, outro valor se existe
 */
int verificacao_procurar_encomendas(Encomendas *encomendas, int codigo) {
    int i;
    for (i = 0; i < encomendas->contador; i++) {
        if (encomendas->encomenda[i].codEncomenda == codigo) {
            return i;
        }
    }
    return -1;
}

/**
 * Função que pede o codigo do produto e procura se o produto existe no programa
 * 
 * @param produtos estrutura relativa aos produtos
 */
void procurar_encomendas(Encomendas *encomendas, Produtos *produtos) {
    int codigo, indice_encomendas;
    printf(MSG_OBTER_COD_ENCOMENDA);
    scanf("%d", &codigo);
    cleanInputBuffer();
    indice_encomendas = verificacao_procurar_encomendas(encomendas, codigo);

    if (indice_encomendas != -1) {
        imprimir_encomendas(&encomendas->encomenda[indice_encomendas], produtos);
    } else {
        printf("Essa encomenda não existe");
    }
}

/**
 * Função que imprime o produtos na ecrã
 * 
 * @param produto estrutura relativa aos produtos
 */
void imprimir_encomendas(Encomenda *encomendas, Produtos *produtos) {
    printf(SEPARACAO);
    if (encomendas->data_entrega.dia != 0) {
        printf("\nCodigo da encomenda: %d |Codigo de Cliente: %d "
                "|Data de pedido: %d/%d/%d |Entrega pretendida: %d/%d/%d "
                "|Estado: %s |Total: %dEuros\n",
                encomendas->codEncomenda, encomendas->codCliente,
                encomendas->data_pedido.dia, encomendas->data_pedido.mes,
                encomendas->data_pedido.ano, encomendas->data_entrega.dia,
                encomendas->data_entrega.mes, encomendas->data_entrega.ano,
                encomendas->estado == 'E' ? "Entregue" : "Por entregar",
                encomendas->quantPagar);
    } else {
        printf("\nCodigo da encomenda: %d |Codigo de Cliente: %d "
                "|Data de pedido: %d/%d/%d |Entrega pretendida: nao definida "
                "|Estado: %s |Total: %dEuros\n",
                encomendas->codEncomenda, encomendas->codCliente,
                encomendas->data_pedido.dia, encomendas->data_pedido.mes,
                encomendas->data_pedido.ano,
                encomendas->estado == 'E' ? "Entregue" : "Por entregar",
                encomendas->quantPagar);
    }
    printf(SEPARACAO);
    imprimir_produtos_encomenda(encomendas, produtos);
}

/**
 * Função que imprimte todas as encomenda que estão por terminar
 * 
 * @param encomendas estrutura as encomendas
 * @param produtos estrutura dos produtos
 */
void imprimir_encomendas_por_terminar(Encomenda *encomendas, Produtos *produtos) {
    if (encomendas->estado == 'P') {
        imprimir_encomendas(encomendas, produtos);
    }
}

/**
 * Função que imprime todas as encomendas que se encontram terminadas
 * 
 * @param encomendas estrutura as encomendas
 * @param produtos estrutura dos produtos
 */
void imprimir_encomendas_terminadas(Encomenda *encomendas, Produtos *produtos) {
    if (encomendas->estado == 'E') {
        imprimir_encomendas(encomendas, produtos);
    }
}

/**
 * Função que lista todas as encomendas terminadas
 * 
 * @param encomendas estrutura as encomendas
 * @param produtos estrutura dos produtos
 */
void listar_encomendas_terminadas(Encomendas *encomendas, Produtos *produtos) {
    if (encomendas->contador > 0) {
        int i;
        for (i = 0; i < encomendas->contador; i++) {
            imprimir_encomendas_terminadas(&encomendas->encomenda[i], produtos);
        }
    } else {
        printf(MSG_NAO_ENCOMENDAS);
    }
}

/**
 * Função que lista todas as encomendas por terminar
 * 
 * @param encomendas estrutura as encomendas
 * @param produtos estrutura dos produtos
 */
void listar_encomendas_por_terminar(Encomendas *encomendas, Produtos *produtos) {
    if (encomendas->contador > 0) {
        int i;
        for (i = 0; i < encomendas->contador; i++) {
            imprimir_encomendas_por_terminar(&encomendas->encomenda[i], produtos);
        }
    } else {
        printf(MSG_NAO_ENCOMENDAS);
    }
}

/**
 * Função que lista todos os produtos que existem na estrutura
 * 
 * @param produtos estrutura relativa aos produtos
 */
void listar_encomendas(Encomendas *encomendas, Produtos *produtos) {
    if (encomendas->contador > 0) {
        int i;
        for (i = 0; i < encomendas->contador; i++) {
            imprimir_encomendas(&encomendas->encomenda[i], produtos);
        }
    } else {
        printf(MSG_NAO_ENCOMENDAS);
    }
}

/**
 * Função que pede o código e verifica se o código existe ou não para atualizar
 *  o produto
 * 
 * @param produtos estrutura relativa aos produtos
 */
void atualizar_encomendas(Encomendas *encomendas) {
    int codigo, indice_encomenda;
    printf(MSG_OBTER_COD_ENCOMENDA);
    scanf("%d", &codigo);
    cleanInputBuffer();
    indice_encomenda = verificacao_procurar_encomendas(encomendas, codigo);

    if (indice_encomenda != -1) {
        mudanca_dados_encomendas(&encomendas->encomenda[indice_encomenda]);
    } else {
        printf("Essa encomenda nao existe!\n");
    }
}

/**
 * Função que permite alterar a data de entrega das encomendas
 * 
 * @param encomendas estrutura as encomendas
 */
void mudanca_dados_encomendas(Encomenda *encomendas) {
    if (encomendas->estado == 'E') {
        printf("A encomenda ja se encontra entregue.\n");
        return;
    }
    encomendas->estado = 'E';
    printf("Encomenda marcada como entregue.\n");
}

/**
 * Função que permite guardar a encomenda no ficheiro
 * 
 * @param encomendas estrutura as encomendas
 * @param ficheiro ficheiro de encomendas
 */
void guardar_encomendas(Encomendas *encomendas, char *ficheiro) {
    int i;
    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&encomendas->contador, sizeof (int), 1, fp);
    for (i = 0; i < encomendas->contador; i++) {
        fwrite(&encomendas->encomenda[i], sizeof (Encomenda), 1, fp);
    }
    fclose(fp);
}

/**
 * Função que permite criar encomendas
 * 
 * @param encomendas estrutura as encomendas
 * @param produtos estrutura dos produtos
 * @param codigo referente do cliente
 * @return 
 */
int inserir_encomendas(Encomendas *encomendas, Produtos *produtos, int codigo) {
    int i, quantProd, preco = 0, codprod, indice_produto;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    Encomenda *temp = (Encomenda *) realloc(encomendas->encomenda,
            (encomendas->contador + 1) * sizeof (Encomenda));
    if (temp == NULL) {
        return -1;
    }
    encomendas->encomenda = temp;
    encomendas->tamanho_array = encomendas->contador + 1;

    if (encomendas->contador == 0) {
        encomendas->encomenda[encomendas->contador].codEncomenda = 1;
    } else {
        encomendas->encomenda[encomendas->contador].codEncomenda =
                encomendas->encomenda[encomendas->contador - 1].codEncomenda + 1;
    }

    encomendas->encomenda[encomendas->contador].codCliente = codigo;
    encomendas->encomenda[encomendas->contador].quantProduto =
            quantProd = obterInt(MIN_QUANTIDADE_PRODUTO,
            MAX_QUANTOS_MATERIAS, QUANTIDADE_PRODUTOS);

    for (i = 0; i < quantProd; i++) {
        do {
            codprod = obterInt(MIN_COD_PRODUTO, MAX_COD_PRODUTO,
                    "Indique o codigo do produto: ");
            indice_produto = verificacao_procurar_produto(produtos, codprod);
            if (indice_produto == -1 || produtos->produtos[indice_produto].atividade == 'D') {
                puts(ERRO_PRODUTO_NAO_EXISTE);
            }
        } while (indice_produto == -1 || produtos->produtos[indice_produto].atividade == 'D');

        encomendas->encomenda[encomendas->contador].codProduto[i] = codprod;
        preco += produtos->produtos[indice_produto].preco;
    }

    encomendas->encomenda[encomendas->contador].quantPagar = preco;
    encomendas->encomenda[encomendas->contador].data_pedido.dia = tm.tm_mday;
    encomendas->encomenda[encomendas->contador].data_pedido.mes = tm.tm_mon + 1;
    encomendas->encomenda[encomendas->contador].data_pedido.ano = tm.tm_year + 1900;
    encomendas->encomenda[encomendas->contador].data_entrega = obter_data_entrega(
            encomendas->encomenda[encomendas->contador].data_pedido);
    encomendas->encomenda[encomendas->contador].estado = 'P';

    encomendas->contador++;

    printf("Total a pagar: %d\n\n", preco);
    return 0;
}

/**
 * Função que permite expandir o espaço das encomendas
 * 
 * @param encomenda estrutura das encomendas 
 */
void expandir_encomendas(Encomendas *encomenda) {
    if (encomenda->contador >= encomenda->tamanho_array) {
        encomenda->tamanho_array = encomenda->contador + 20;
        encomenda->encomenda = (Encomenda *) realloc(encomenda->encomenda,
                encomenda->tamanho_array * sizeof (Encomenda));
    }
}

/**
 * Função que lista todas as encomendas para o cliente
 * 
 * @param encomendas estrutura das encomendas 
 * @param produto estrutura dos produtos
 * @param codigo referente ao cliente
 */
void listar_encomendas_cliente(Encomendas *encomendas, Produtos *produto, int codigo) {
    if (encomendas->contador > 0) {
        int i;
        for (i = 0; i < encomendas->contador; i++) {
            imprimir_encomendas_cliente(&encomendas->encomenda[i], produto, codigo);
        }
    } else {
        printf(MSG_NAO_ENCOMENDAS);
    }
}

/**
 * Função que imprimir as encomendas para o cliente
 *
 * @param encomendas estrutura das encomendas 
 * @param produtos estrutura dos produtos
 * @param codigo referente ao cliente
 */
void imprimir_encomendas_cliente(Encomenda *encomendas, Produtos *produtos, int codigo) {
    if (encomendas->codCliente == codigo) {
        imprimir_encomendas(encomendas, produtos);
    }
}




/**
 * Verifica se um cliente possui pelo menos uma encomenda registada.
 */
int cliente_tem_encomendas(Encomendas *encomendas, int codigo_cliente) {
    int i;
    for (i = 0; i < encomendas->contador; i++) {
        if (encomendas->encomenda[i].codCliente == codigo_cliente) {
            return 1;
        }
    }
    return 0;
}

/**
 * Verifica se um produto foi usado em pelo menos uma encomenda.
 */
int produto_tem_encomendas(Encomendas *encomendas, int codigo_produto) {
    int i, j;
    for (i = 0; i < encomendas->contador; i++) {
        for (j = 0; j < encomendas->encomenda[i].quantProduto; j++) {
            if (encomendas->encomenda[i].codProduto[j] == codigo_produto) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Gera no ecra e num ficheiro de texto o resumo dos componentes necessarios
 * para satisfazer as encomendas por entregar de uma dada semana ISO.
 */
void gestao_producao(Encomendas *encomendas, Produtos *produtos, Materiais *materiais) {
    int semana = obterInt(1, 53, "Indique a semana do ano: ");
    int ano = obterInt(1900, 50000, "Indique o ano: ");
    long *totais;
    int i, j, k, indice_produto, indice_material;
    int encontrou = 0, sem_data = 0;
    char nome_ficheiro[80];
    FILE *fp;

    if (materiais->contador <= 0) {
        printf("Nao existem materiais registados.\n");
        return;
    }

    totais = (long *) calloc((size_t) materiais->contador, sizeof (long));
    if (totais == NULL) {
        printf("Nao foi possivel gerar o resumo de producao.\n");
        return;
    }

    for (i = 0; i < encomendas->contador; i++) {
        int semana_encomenda, ano_semana;
        Encomenda *encomenda = &encomendas->encomenda[i];

        if (encomenda->estado == 'E') {
            continue;
        }
        if (!data_valida(encomenda->data_entrega)) {
            sem_data++;
            continue;
        }

        semana_iso(encomenda->data_entrega, &semana_encomenda, &ano_semana);
        if (semana_encomenda != semana || ano_semana != ano) {
            continue;
        }

        encontrou = 1;
        for (j = 0; j < encomenda->quantProduto; j++) {
            indice_produto = verificacao_procurar_produto(produtos,
                    encomenda->codProduto[j]);
            if (indice_produto == -1) {
                continue;
            }

            for (k = 0; k < produtos->produtos[indice_produto].quantidade_mat; k++) {
                indice_material = verificacao_procurar_material(materiais,
                        produtos->produtos[indice_produto].codmaterial[k]);
                if (indice_material != -1) {
                    totais[indice_material] +=
                            produtos->produtos[indice_produto].quantidade_material[k];
                }
            }
        }
    }

    snprintf(nome_ficheiro, sizeof (nome_ficheiro),
            "producao_semana_%02d_%d.txt", semana, ano);
    fp = fopen(nome_ficheiro, "w");

    printf("\nResumo de producao - Semana %d/%d\n", semana, ano);
    printf(SEPARACAO);
    if (fp != NULL) {
        fprintf(fp, "Resumo de producao - Semana %d/%d\n", semana, ano);
        fprintf(fp, "====================================\n");
    }

    if (!encontrou) {
        printf("Nao existem encomendas por entregar para esta semana.\n");
        if (fp != NULL) {
            fprintf(fp, "Nao existem encomendas por entregar para esta semana.\n");
        }
    } else {
        for (i = 0; i < materiais->contador; i++) {
            if (totais[i] > 0) {
                printf("%d - %s: %ld %s\n",
                        materiais->materiais[i].codMaterial,
                        materiais->materiais[i].nome_material,
                        totais[i], materiais->materiais[i].unidade);
                if (fp != NULL) {
                    fprintf(fp, "%d - %s: %ld %s\n",
                            materiais->materiais[i].codMaterial,
                            materiais->materiais[i].nome_material,
                            totais[i], materiais->materiais[i].unidade);
                }
            }
        }
    }

    if (sem_data > 0) {
        printf("Nota: %d encomenda(s) antiga(s) sem data de entrega pretendida nao foram incluidas.\n",
                sem_data);
        if (fp != NULL) {
            fprintf(fp, "Nota: %d encomenda(s) antiga(s) sem data de entrega pretendida nao foram incluidas.\n",
                    sem_data);
        }
    }

    if (fp != NULL) {
        fclose(fp);
        printf("Resumo exportado para %s\n", nome_ficheiro);
    } else {
        printf("Nao foi possivel exportar o resumo para ficheiro.\n");
    }

    free(totais);
}
