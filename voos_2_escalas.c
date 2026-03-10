#include "escalas.h"

LISTA_RT2* criar_lista_voos_com_duas_escalas(BLOCO* voos_diretos, char partida[], char chegada[]) {
    LISTA_RT2* voos_com_duas_escalas = NULL;
    BLOCO *voo_direto, *rota_escala, *rota_chegada_final;

    for (voo_direto = voos_diretos; voo_direto != NULL; voo_direto = voo_direto->prox) {
        if (strcmp(voo_direto->rota.IATA_p, partida) == 0) {
            for (rota_escala = voos_diretos; rota_escala != NULL; rota_escala = rota_escala->prox) {
                if (strcmp(rota_escala->rota.IATA_p, voo_direto->rota.IATA_c) == 0) {
                    for (rota_chegada_final = voos_diretos; rota_chegada_final != NULL; rota_chegada_final = rota_chegada_final->prox) {
                        if ((strcmp(rota_chegada_final->rota.IATA_c, chegada) == 0) && (strcmp(rota_chegada_final->rota.IATA_p, rota_escala->rota.IATA_c) == 0)
                        && (strcmp(rota_chegada_final->rota.IATA_p, partida)!=0 && (strcmp(rota_chegada_final->rota.IATA_c, voo_direto->rota.IATA_c)!=0))) {
                            
                            LISTA_RT2* novo_voo = (LISTA_RT2*)malloc(sizeof(LISTA_RT2));
                            if (novo_voo != NULL) {
                                novo_voo->voo_c_escala_1.partida = voo_direto->rota; 
                                novo_voo->voo_c_escala_1.chegada = rota_escala->rota;
                                novo_voo->rota = rota_chegada_final->rota; 
                                novo_voo->prox = voos_com_duas_escalas; 
                                voos_com_duas_escalas = novo_voo; 
                            }
                        }
                    }
                }
            }
        }
    }
    return voos_com_duas_escalas;
}

void imprimir_lista_voos_com_duas_escalas(LISTA_RT2* topo) {
    printf("Lista de voos com duas escalas:\n");
    LISTA_RT2* atual = topo;
	
	if (atual == NULL) printf("--> Não há voos disponíveis que atendam aos requisitos.\n");
	
    for (atual = topo; atual != NULL; atual = atual->prox) {
        printf("Voos: --------------------------------------------\n");
        printf("Voo 1: %s %s %02d:%02d %s %02d:%02d Dist: %.2lf KM\n", atual->voo_c_escala_1.partida.codigo, atual->voo_c_escala_1.partida.IATA_p, atual->voo_c_escala_1.partida.hora_p, atual->voo_c_escala_1.partida.min_p, atual->voo_c_escala_1.partida.IATA_c, atual->voo_c_escala_1.partida.hora_c, atual->voo_c_escala_1.partida.min_c, atual->voo_c_escala_1.partida.distancia);
        printf("Voo 2: %s %s %02d:%02d %s %02d:%02d Dist: %.2lf KM\n", atual->voo_c_escala_1.chegada.codigo, atual->voo_c_escala_1.chegada.IATA_p, atual->voo_c_escala_1.chegada.hora_p, atual->voo_c_escala_1.chegada.min_p, atual->voo_c_escala_1.chegada.IATA_c, atual->voo_c_escala_1.chegada.hora_c, atual->voo_c_escala_1.chegada.min_c, atual->voo_c_escala_1.chegada.distancia);
        printf("Voo 3: %s %s %02d:%02d %s %02d:%02d Dist: %.2lf KM\n", atual->rota.codigo, atual->rota.IATA_p, atual->rota.hora_p, atual->rota.min_p, atual->rota.IATA_c, atual->rota.hora_c, atual->rota.min_c, atual->rota.distancia);
        printf("\n");
    }
}

void remover_voos_escala_2(LISTA_RT2 **topo) {
    LISTA_RT2 *atual = *topo, *anterior = NULL, *proximo;
    ROTA voo1, voo2, voo3;
    int hora_c_voo_1, hora_p_voo_2, hora_c_voo_2, hora_p_voo_3;
    int diferenca_min_v1_v2, diferenca_min_v2_v3;
    
    while (atual != NULL) {
        voo1 = atual->voo_c_escala_1.partida; voo2 = atual->voo_c_escala_1.chegada; voo3 = atual->rota;

        hora_c_voo_1 = voo1.hora_c * 60 + voo1.min_c;
        hora_p_voo_2 = voo2.hora_p * 60 + voo2.min_p;
        hora_c_voo_2 = voo2.hora_c * 60 + voo2.min_c;
        hora_p_voo_3 = voo3.hora_p * 60 + voo3.min_p;

        diferenca_min_v1_v2 = hora_p_voo_2 - hora_c_voo_1;
        diferenca_min_v2_v3 = hora_p_voo_3 - hora_c_voo_2;
        
        if (diferenca_min_v1_v2 < 0) diferenca_min_v1_v2 += 24 * 60;
        if (diferenca_min_v2_v3 < 0) diferenca_min_v2_v3 += 24 * 60;

        if (diferenca_min_v1_v2 < 60 || diferenca_min_v1_v2 > 12 * 60 || diferenca_min_v2_v3 < 60 || diferenca_min_v2_v3 > 12 * 60) {
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

int comparar_horas_escala_2(ROTA rota1, ROTA rota2) {
    if (rota1.hora_p < rota2.hora_p) return -1;
    else if (rota1.hora_p > rota2.hora_p) return 1;
    else { 
        if (rota1.min_p < rota2.min_p) return -1;
        else if (rota1.min_p > rota2.min_p) return 1;
        else return 0;
    }
}

void trocar_voos_escala_2(LISTA_RT2 *voo1, LISTA_RT2 *voo2) {
    RT1 temp_voo = voo1->voo_c_escala_1;
    ROTA temp_rota = voo1->rota;

    voo1->voo_c_escala_1 = voo2->voo_c_escala_1;
    voo1->rota = voo2->rota;

    voo2->voo_c_escala_1 = temp_voo;
    voo2->rota = temp_rota;
}

void ordenar_crescente_escala_2(LISTA_RT2 **topo) { 
    if (*topo == NULL || (*topo)->prox == NULL) return; 

    int trocado; LISTA_RT2 *atual, *proximo = NULL;
    do {
        trocado = 0; atual = *topo;
        while (atual->prox != proximo) {
        	if (comparar_horas_escala_2(atual->voo_c_escala_1.partida, atual->prox->voo_c_escala_1.partida) > 0) {
                trocar_voos_escala_2(atual, atual->prox);
                trocado = 1;
            }
            atual = atual->prox;
        }
        proximo = atual;
    } while (trocado);
}

void ordenar_decrescente_escala_2(LISTA_RT2 **topo) {
    if (*topo == NULL || (*topo)->prox == NULL) return; 

    int trocado; LISTA_RT2 *atual, *proximo = NULL;
    do {
        trocado = 0; atual = *topo;
        while (atual->prox != proximo) {
            if (comparar_horas_escala_2(atual->voo_c_escala_1.partida, atual->prox->voo_c_escala_1.partida) < 0) {
                trocar_voos_escala_2(atual, atual->prox);
                trocado = 1;
            }
            atual = atual->prox;
        }
        proximo = atual;
    } while (trocado);
}

void ordenar_distancia_escala_2(LISTA_RT2 *topo) {
    if (topo == NULL) return;

    int trocado; LISTA_RT2 *atual, *anterior = NULL;
    double distancia_atual, distancia_proximo;
	
    do {
        trocado = 0; atual = topo;

        while (atual->prox != anterior) {
            distancia_atual = atual->voo_c_escala_1.partida.distancia + atual->voo_c_escala_1.chegada.distancia + atual->rota.distancia;
            distancia_proximo = atual->prox->voo_c_escala_1.partida.distancia + atual->prox->voo_c_escala_1.chegada.distancia + atual->prox->rota.distancia;

            if (distancia_atual > distancia_proximo) {
                trocar_voos_escala_2(atual, atual->prox);
                trocado = 1;
            }
            atual = atual->prox;
        }
        anterior = atual;
    } while (trocado);
}