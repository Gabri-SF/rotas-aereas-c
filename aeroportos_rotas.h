#ifndef AEROPORTOS_ROTAS_H
#define AEROPORTOS_ROTAS_H

#include "tipos.h"

/* Gestão de Aeroportos */
void insere_na_lista_aeroportos(LISTA **topo, AEROPORTO aer, int escreve);
void imprime_lista_aeroportos(LISTA* topo);

/* Gestão de Voos/Rotas Base e Voos Diretos */
void insere_na_lista_rotas(BLOCO **topo, ROTA rota, LISTA *aeroportos, int escreve);
void imprime_lista_rotas(BLOCO* topo);
BLOCO* voos_diretos_A_B(char A[], char B[], BLOCO* topo_rotas);
void ordenar_crescente(BLOCO** topo);
void ordenar_decrescente(BLOCO** topo);

#endif /* AEROPORTOS_ROTAS_H */