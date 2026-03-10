#include "memoria.h"
#include <stdlib.h>

void limpa_listas(CONTEXTO *ctx) {
    LISTA *temp_1;
    BLOCO *temp_2, *temp_3;
    LISTA_RT1 *temp_4;
    LISTA_RT2 *temp_5;
    
    /* Limpa a lista de aeroportos */
    while (ctx->aeroportos != NULL) {
        temp_1 = ctx->aeroportos;
        ctx->aeroportos = ctx->aeroportos->prox;
        free(temp_1);
    }

    /* Limpa a lista de rotas */
    while (ctx->rotas != NULL) {
        temp_2 = ctx->rotas;
        ctx->rotas = ctx->rotas->prox;
        free(temp_2);
    }

    /* Limpa a lista de rotas diretas */
    while (ctx->rotas_diretas != NULL) {
        temp_3 = ctx->rotas_diretas;
        ctx->rotas_diretas = ctx->rotas_diretas->prox;
        free(temp_3);
    }

    /* Limpa a lista de rotas com uma escala */
    while (ctx->rotas_escala_1 != NULL) {
        temp_4 = ctx->rotas_escala_1;
        ctx->rotas_escala_1 = ctx->rotas_escala_1->prox;
        free(temp_4);
    }

    /* Limpa a lista de rotas com duas escalas */
    while (ctx->rotas_escala_2 != NULL) {
        temp_5 = ctx->rotas_escala_2;
        ctx->rotas_escala_2 = ctx->rotas_escala_2->prox;
        free(temp_5);
    }
}