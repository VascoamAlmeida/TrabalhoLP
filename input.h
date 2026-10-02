/* 
 * @File:   input.h
 *          Vasco Almeida
 *
 */
#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif


    int menu_cliente();
    void menu_admin();
    void menu_principal();

    void lerString(char *string, unsigned int tamanho, char *msg);
    int obterInt(int minValor, int maxValor, char *msg);
    void cleanInputBuffer();
    int leitura_menu(char mensagem[], int limite_inferior, int limite_superior);
    float obterFloat(float minValor, float maxValor, char *msg);



#ifdef __cplusplus
}
#endif

#endif /* INPUT_H */

