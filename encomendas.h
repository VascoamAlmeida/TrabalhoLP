/* 
 * @File:   encomendas.h
 *          Vasco Almeida
 *
 */
#ifndef ENCOMENDAS_H
#define ENCOMENDAS_H

#ifdef __cplusplus
extern "C" {
#endif

#define MSG_NAO_ENCOMENDAS          "Não existem encomendas!"
#define MSG_OBTER_COD_ENCOMENDA     "Indique o codigo da encomenda: " 
#define MAX_QUANTIDADE_PRODUTO      10000

    /**
     * @struct Data
     * Estrutura de dados da data
     */
    typedef struct {
        int dia, mes, ano;
    } Data;

    /**
     * @struct Encomenda
     * Estrutura de dados do encomenda
     */
    typedef struct {
        int codEncomenda;
        int codCliente;
        int quantProduto;
        int codProduto[MAX_QUANTIDADE_PRODUTO];
        int quantPagar;
        Data data_pedido;
        Data data_entrega;
        char estado;
    } Encomenda;

    /**
     * @struct Encomendas
     * Estrutura de dados do encomendas
     */
    typedef struct Encomendas {
        int contador;
        Encomenda *encomenda;
        int tamanho_array;
    } Encomendas;
    
    int encomenda_admin();
    int gestao_encomendas();
    int inserir_encomendas(Encomendas *encomendas, Produtos *produtos, int codigo);
    void carregar_encomendas(Encomendas *encomendas, char *ficheiro);
    int verificacao_procurar_encomendas(Encomendas *encomendas, int codigo);
    void procurar_encomendas(Encomendas *encomendas, Produtos *produto);
    void imprimir_encomendas(Encomenda *encomendas, Produtos *produtos);
    void listar_encomendas(Encomendas *encomendas, Produtos *produto);
    void atualizar_encomendas(Encomendas *encomendas);
    void mudanca_dados_encomendas(Encomenda *encomendas);
    void guardar_encomendas(Encomendas *encomenda, char *ficheiro);
    void listar_encomendas_cliente(Encomendas *encomendas, Produtos *produtos, int codigo);
    void imprimir_encomendas_cliente(Encomenda *encomendas, Produtos *produtos, int codigo);
    void imprimir_encomendas_terminadas(Encomenda *encomendas, Produtos *produtos);
    void imprimir_encomendas_por_terminar(Encomenda *encomendas, Produtos *produtos);
    void listar_encomendas_terminadas(Encomendas *encomendas, Produtos *produtos);
    void listar_encomendas_por_terminar(Encomendas *encomendas, Produtos *produtos);
    int cliente_tem_encomendas(Encomendas *encomendas, int codigo_cliente);
    int produto_tem_encomendas(Encomendas *encomendas, int codigo_produto);
    void gestao_producao(Encomendas *encomendas, Produtos *produtos, Materiais *materiais);



#ifdef __cplusplus
}
#endif

#endif /* ENCOMENDAS_H */

