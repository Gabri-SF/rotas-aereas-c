#include "escalas.h"

ROTA encontrar_rota_partida(char partida[], BLOCO* topo_rotas) {
    BLOCO* rota_partida = topo_rotas;
    ROTA rp, rota_vazia;

    while (rota_partida != NULL) {
        rp = rota_partida->rota;
        if (strcmp(rp.IATA_p, partida) == 0) return rp;
        rota_partida = rota_partida->prox;
    }
    sprintf(rota_vazia.codigo, "%s", "");
    return rota_vazia;
}

ROTA encontrar_rota_chegada(char chegada[], BLOCO* topo_rotas) {
    BLOCO* rota_chegada = topo_rotas;
    ROTA rc, rota_vazia;
	
    while (rota_chegada != NULL) {
        rc = rota_chegada->rota;
        if (strcmp(rc.IATA_c, chegada) == 0) return rc;
        rota_chegada = rota_chegada->prox;
    }
    sprintf(rota_vazia.codigo, "%s", "");
    return rota_vazia;
}

int rota_adicionada(LISTA_RT1* lista, ROTA rp, ROTA rc) {
	LISTA_RT1* atual;
    for (atual = lista; atual != NULL; atual = atual->prox) {
        if (strcmp(atual->voo_c_escala.partida.codigo, rp.codigo) == 0 &&
            strcmp(atual->voo_c_escala.chegada.codigo, rc.codigo) == 0)
            return 1;
    }
    return 0;
}

LISTA_RT1* preencher_lista_voos_com_escala_1(char partida[], char chegada[], BLOCO* topo_rotas) {
    LISTA_RT1* topo_voos_com_escala_1 = NULL;
	BLOCO *atual_partida, *atual_chegada;
	ROTA rp, rc;
	LISTA_RT1* novo_voo;
	
    for (atual_partida = topo_rotas; atual_partida != NULL; atual_partida = atual_partida->prox) {
        rp = encontrar_rota_partida(partida, atual_partida);
        if (strcmp(rp.codigo, "") == 0) continue;

        for (atual_chegada = topo_rotas; atual_chegada != NULL; atual_chegada = atual_chegada->prox) {
            rc = encontrar_rota_chegada(chegada, atual_chegada);
            if (strcmp(rc.codigo, "") == 0) continue;

            if (strcmp(rp.IATA_c, rc.IATA_p) == 0 && !rota_adicionada(topo_voos_com_escala_1, rp, rc)) {
                novo_voo = calloc(1, sizeof(LISTA_RT1));
                if (novo_voo == NULL) {
                    printf("\nERRO - calloc - preencher_lista_voos_com_escala_1\n");
                    return NULL;
                }
                novo_voo->voo_c_escala.partida = rp;
                novo_voo->voo_c_escala.chegada = rc;
                novo_voo->prox = topo_voos_com_escala_1;
                topo_voos_com_escala_1 = novo_voo;
            }
        }
    }
    return topo_voos_com_escala_1;
}

void imprime_lista_voos_com_escala(LISTA_RT1* topo_rotas_com_escala_1) {
    LISTA_RT1* atual = topo_rotas_com_escala_1;
    printf("Lista de voos com escala disponiveis:\n");
    if (atual == NULL) printf("--> Não existem voos atendentes aos requisitos\n");

    while (atual != NULL) {
    	printf("Voo:--------------------------------------\n");
        printf("%s %s %02d:%02d %s %02d:%02d Dist: %.2f KM\n",
            atual->voo_c_escala.partida.codigo, atual->voo_c_escala.partida.IATA_p, atual->voo_c_escala.partida.hora_p, 
            atual->voo_c_escala.partida.min_p, atual->voo_c_escala.partida.IATA_c, atual->voo_c_escala.partida.hora_c, 
            atual->voo_c_escala.chegada.min_c, atual->voo_c_escala.partida.distancia);
        printf("%s %s %02d:%02d %s %02d:%02d Dist: %.2f KM\n",
            atual->voo_c_escala.chegada.codigo, atual->voo_c_escala.chegada.IATA_p, atual->voo_c_escala.chegada.hora_p, 
            atual->voo_c_escala.chegada.min_p, atual->voo_c_escala.chegada.IATA_c, atual->voo_c_escala.chegada.hora_c, 
            atual->voo_c_escala.partida.min_c, atual->voo_c_escala.chegada.distancia);
        printf("\n");
        atual = atual->prox;
    }
}

void ordenar_crescente_com_escala(LISTA_RT1 **topo) {
    LISTA_RT1 *atual, *proximo;
    RT1 aux;

    if (*topo == NULL || (*topo)->prox == NULL) return;

    for (atual = *topo; atual != NULL; atual = atual->prox) {
        for (proximo = atual->prox; proximo != NULL; proximo = proximo->prox) {
            if (atual->voo_c_escala.partida.hora_p > proximo->voo_c_escala.partida.hora_p || 
               (atual->voo_c_escala.partida.hora_p == proximo->voo_c_escala.partida.hora_p && atual->voo_c_escala.partida.min_p > proximo->voo_c_escala.partida.min_p)) {
                aux = atual->voo_c_escala;
                atual->voo_c_escala = proximo->voo_c_escala;
                proximo->voo_c_escala = aux;
            }
        }
    }
}

void ordenar_decrescente_com_escala(LISTA_RT1 **topo) {
    LISTA_RT1 *atual, *proximo;
    RT1 aux;

    if (*topo == NULL || (*topo)->prox == NULL) return;

    for (atual = *topo; atual != NULL; atual = atual->prox) {
        for (proximo = atual->prox; proximo != NULL; proximo = proximo->prox) {
            if (atual->voo_c_escala.partida.hora_p < proximo->voo_c_escala.partida.hora_p || 
               (atual->voo_c_escala.partida.hora_p == proximo->voo_c_escala.partida.hora_p && atual->voo_c_escala.partida.min_p < proximo->voo_c_escala.partida.min_p)) {
                aux = atual->voo_c_escala;
                atual->voo_c_escala = proximo->voo_c_escala;
                proximo->voo_c_escala = aux;
            }
        }
    }
}

void remover_voos_escala_1(LISTA_RT1 **topo) {
    LISTA_RT1 *atual = *topo, *anterior = NULL, *proximo;
    ROTA chegada_atual, partida_proximo;
    int hora_chegada_partida, hora_partida_chegada, diferenca_minutos;
    
    while (atual != NULL) {
        chegada_atual = atual->voo_c_escala.chegada;
        partida_proximo = atual->voo_c_escala.partida;

        hora_chegada_partida = partida_proximo.hora_c * 60 + partida_proximo.min_c;
        hora_partida_chegada = chegada_atual.hora_p * 60 + chegada_atual.min_p;

        diferenca_minutos = hora_partida_chegada - hora_chegada_partida;
        if (diferenca_minutos < 0) diferenca_minutos += 24 * 60;

        if (diferenca_minutos < 60 || diferenca_minutos > 12 * 60) {
            proximo = atual->prox;
            free(atual);
            if (anterior != NULL) anterior->prox = proximo;
            else *topo = proximo;
            atual = proximo;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

void ordenar_distancia_escala_1(LISTA_RT1* topo){ 
	LISTA_RT1 *atual, *proximo;
	RT1 aux;
	for (atual = topo; atual != NULL ; atual = atual->prox){
		for(proximo = atual->prox; proximo != NULL; proximo = proximo->prox){
			if((atual->voo_c_escala.partida.distancia + atual->voo_c_escala.chegada.distancia) > 
               (proximo->voo_c_escala.partida.distancia + proximo->voo_c_escala.chegada.distancia)){
				aux = atual->voo_c_escala;
				atual->voo_c_escala = proximo->voo_c_escala;
				proximo->voo_c_escala = aux;
			}
		}
	}
}