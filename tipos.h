#ifndef TIPOS_H
#define TIPOS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DIM 100
#define PI 3.14159

/* Estrutura para armazenar informação relativa a um aeroporto */
typedef struct aeroporto {
    char ICAO[10];
    char IATA[10];
    char CIDADE[30];
    int lat_deg, lat_min, lat_seg;
    char lat_dir;
    int lon_deg, lon_min, lon_seg;
    char lon_dir;
    int tz;
} AEROPORTO;

/* Estrutura para armazenar dados de um voo/rota */
typedef struct rota {
    char codigo[10];
    char IATA_p[10];
    int hora_p, min_p;
    char IATA_c[10];
    int hora_c, min_c;
    double distancia;
} ROTA;

/* Lista ligada de aeroportos */
typedef struct lista {
    AEROPORTO aer;
    struct lista* prox;
} LISTA;

/* Lista ligada de rotas (voos) */
typedef struct bloco {
    ROTA rota;
    struct bloco* prox;
} BLOCO;

/* Estruturas para voos com 1 escala */
typedef struct rota_escala_1 {
    ROTA partida;
    ROTA chegada;
} RT1;

typedef struct lista_de_voos_com_escala_1 {
    RT1 voo_c_escala;
    struct lista_de_voos_com_escala_1 *prox;
} LISTA_RT1;

/* Estrutura para voos com 2 escalas */
typedef struct lista_de_voos_com_escala_2 {
    RT1 voo_c_escala_1;
    ROTA rota;
    struct lista_de_voos_com_escala_2* prox;
} LISTA_RT2;

/* Estrutura que guarda o contexto/estado de todas as listas do programa */
typedef struct contexto {
    LISTA* aeroportos;
    BLOCO* rotas;
    BLOCO* rotas_diretas;
    LISTA_RT1* rotas_escala_1;
    LISTA_RT2* rotas_escala_2;
} CONTEXTO;

#endif /* TIPOS_H */