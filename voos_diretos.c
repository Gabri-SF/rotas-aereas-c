#include "aeroportos_rotas.h"

void insere_na_lista_rotas(BLOCO **topo, ROTA rota, LISTA *aeroportos, int escreve) {
    LISTA *partida = NULL, *chegada = NULL, *aux_lista = aeroportos;
    BLOCO *aux_bloco, *novo;

    while (aux_lista != NULL) {
    	if (strcmp(aux_lista->aer.IATA, rota.IATA_p) == 0) { partida = aux_lista; break; }
        aux_lista = aux_lista->prox;
    }

    aux_lista = aeroportos;
    while (aux_lista != NULL) {
        if (strcmp(aux_lista->aer.IATA, rota.IATA_c) == 0) { chegada = aux_lista; break; }
        aux_lista = aux_lista->prox;
    }

    if (partida != NULL && chegada != NULL) { 
        novo = (BLOCO*) calloc(1, sizeof(BLOCO));
        if (novo != NULL) {
            novo->rota = rota;
            novo->prox = NULL;
            if (*topo == NULL) *topo = novo;
            else {
                aux_bloco = *topo;
                while (aux_bloco->prox) aux_bloco = aux_bloco->prox;
                aux_bloco->prox = novo;
            }
        } else {
            printf("Erro -- calloc -- insere_na_lista_rotas!\n");
          }
    } else {
    	if(escreve){
        	printf("Aeroportos de partida ou chegada não encontrados para a rota:\n");
        	printf("%s %s %02d:%02d %s %02d:%02d\n\n", rota.codigo, rota.IATA_p, rota.hora_p, rota.min_p, rota.IATA_c, rota.hora_c, rota.min_c);
        	}
    }
}

void imprime_lista_rotas(BLOCO* topo) {
    printf("Voos: \n");
    if(topo == NULL) printf("--> Não existem voos atendentes aos requisitos\n");
    while (topo != NULL) { 
        printf("%s %s %02d:%02d %s %02d:%02d Dist: %.2lf KM\n", 
                topo->rota.codigo, topo->rota.IATA_p, topo->rota.hora_p, topo->rota.min_p, 
                topo->rota.IATA_c, topo->rota.hora_c, topo->rota.min_c, topo->rota.distancia);
        topo = topo->prox;
    }
    printf("\n");
}

BLOCO* voos_diretos_A_B(char A[], char B[], BLOCO* topo_rotas) {
    BLOCO *topo = NULL, *novo = NULL, *aux = NULL;

    while (topo_rotas != NULL) {
        if ((strcmp( A, topo_rotas->rota.IATA_p) == 0) && (strcmp( B, topo_rotas->rota.IATA_c) == 0)) {
            novo = (BLOCO*)malloc(sizeof(BLOCO));
            if (novo != NULL) {
                novo->rota = topo_rotas->rota;
                novo->prox = NULL; 
                if (topo == NULL) topo = novo;
                else {
                    aux = topo;
                    while (aux->prox) aux = aux->prox;
                    aux->prox = novo;
                }
            } else {
                printf("Erro -- malloc -- voos_diretos_A_B!\n");
            }
        }
        topo_rotas = topo_rotas->prox;
    }
    return topo;
}

void ordenar_crescente(BLOCO** topo) {
    BLOCO *atual, *proximo;
    ROTA temp;

    if (*topo == NULL || (*topo)->prox == NULL) return;

    for (atual = *topo; atual != NULL; atual = atual->prox) {
        for (proximo = atual->prox; proximo != NULL; proximo = proximo->prox) {
            if (atual->rota.hora_p > proximo->rota.hora_p || (atual->rota.hora_p == proximo->rota.hora_p && atual->rota.min_p > proximo->rota.min_p)) {
                temp = atual->rota;
                atual->rota = proximo->rota;
                proximo->rota = temp;
            }
        }
    }
}

void ordenar_decrescente(BLOCO** topo) {
	BLOCO *atual, *proximo;
    ROTA temp;

    if (*topo == NULL || (*topo)->prox == NULL) return;

    for (atual = *topo; atual != NULL; atual = atual->prox) {
        for (proximo = atual->prox; proximo != NULL; proximo = proximo->prox) {
            if (atual->rota.hora_p < proximo->rota.hora_p || (atual->rota.hora_p == proximo->rota.hora_p && atual->rota.min_p < proximo->rota.min_p)) {
                temp = atual->rota;
                atual->rota = proximo->rota;
                proximo->rota = temp;
            }
        }
    }
}