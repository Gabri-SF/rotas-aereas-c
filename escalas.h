#ifndef ESCALAS_H
#define ESCALAS_H

#include "tipos.h"

/* --- Voos com 1 Escala --- */
ROTA encontrar_rota_partida(char partida[], BLOCO* topo_rotas);
ROTA encontrar_rota_chegada(char chegada[], BLOCO* topo_rotas);
int rota_adicionada(LISTA_RT1* lista, ROTA rp, ROTA rc);
LISTA_RT1* preencher_lista_voos_com_escala_1(char partida[], char chegada[], BLOCO* topo_rotas);
void imprime_lista_voos_com_escala(LISTA_RT1* topo_rotas_com_escala_1);
void ordenar_crescente_com_escala(LISTA_RT1 **topo);
void ordenar_decrescente_com_escala(LISTA_RT1 **topo);
void remover_voos_escala_1(LISTA_RT1 **topo);
void ordenar_distancia_escala_1(LISTA_RT1* topo);

/* --- Voos com 2 Escalas --- */
LISTA_RT2* criar_lista_voos_com_duas_escalas(BLOCO* voos_diretos, char partida[], char chegada[]);
void imprimir_lista_voos_com_duas_escalas(LISTA_RT2* topo);
void remover_voos_escala_2(LISTA_RT2 **topo);
int comparar_horas_escala_2(ROTA rota1, ROTA rota2);
void trocar_voos_escala_2(LISTA_RT2 *voo1, LISTA_RT2 *voo2);
void ordenar_crescente_escala_2(LISTA_RT2 **topo);
void ordenar_decrescente_escala_2(LISTA_RT2 **topo);
void ordenar_distancia_escala_2(LISTA_RT2 *topo);

#endif /* ESCALAS_H */