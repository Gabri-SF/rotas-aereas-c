#define _POSIX_C_SOURCE 200809L /* Necessário para usar getline() e getopt() */

#include "tipos.h"
#include "ficheiros.h"
#include "aeroportos_rotas.h"
#include "matematica.h"
#include "escalas.h"
#include "memoria.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> /* Necessário para o getopt */

int main(int argc, char* argv[]) {
    FILE *fp1 = NULL; /* Ficheiro aeroportos.txt */
    FILE *fp2 = NULL; /* Ficheiro rotas.txt */
    
    /* Inicializa o nosso contexto (agrupa todas as listas a NULL) */
    CONTEXTO ctx = {NULL, NULL, NULL, NULL, NULL};
    
    int nconv1 = 0, nconv2 = 0;
    AEROPORTO aer;
    ROTA rota;

    /* --- VARIÁVEIS DE ESTADO (FLAGS) --- */
    int flag_aeroportos = 0;
    int flag_voos = 0;
    char *iata_p = NULL;
    char *iata_c = NULL;
    int escalas = -1;       /* -1 significa não definido */
    int ordem_tempo = 0;    /* 1 para Crescente (C), 2 para Decrescente (D) */
    int ordem_dist = 0;     /* 1 se a flag -d for passada */
    int erro_argumentos = 0;
    int opt;

    /* ==========================================================
     * 1. PARSE DE ARGUMENTOS DA LINHA DE COMANDOS (GETOPT)
     * ========================================================== */
    
    /* a, v, d são flags simples. L e t esperam um argumento (:) */
    while ((opt = getopt(argc, argv, "avL:t:d")) != -1) {
        switch (opt) {
            case 'a':
                flag_aeroportos = 1;
                break;
            case 'v':
                flag_voos = 1;
                break;
            case 'L':
                escalas = atoi(optarg);
                if (escalas < 0 || escalas > 2) erro_argumentos = 1;
                break;
            case 't':
                if (strcmp(optarg, "C") == 0) ordem_tempo = 1;
                else if (strcmp(optarg, "D") == 0) ordem_tempo = 2;
                else erro_argumentos = 1;
                break;
            case 'd':
                ordem_dist = 1;
                break;
            case '?':
                erro_argumentos = 1;
                break;
            default:
                break;
        }
    }

    /* Se não for apenas listagem (-a ou -v), precisamos dos aeroportos no fim */
    if (!flag_aeroportos && !flag_voos && !erro_argumentos) {
        if (optind + 2 == argc) {
            iata_p = argv[optind];
            iata_c = argv[optind + 1];
            if (strcmp(iata_p, iata_c) == 0) erro_argumentos = 1;
            if (escalas == -1) erro_argumentos = 1; /* -L é obrigatório para pesquisa */
        } else {
            erro_argumentos = 1;
        }
    }

    if (erro_argumentos) {
        printf("\nERRO: Argumentos invalidos!\n");
        printf("Uso:\n");
        printf("  %s -a                     (Listar aeroportos)\n", argv[0]);
        printf("  %s -v                     (Listar todos os voos)\n", argv[0]);
        printf("  %s -L <0|1|2> [-t C|D] [-d] <ORIGEM> <DESTINO>\n\n", argv[0]);
        return 1;
    }

    /* ==========================================================
     * 2. LEITURA DOS FICHEIROS DE DADOS
     * ========================================================== */
    fp1 = fopen("aeroportos.txt", "r");
    fp2 = fopen("rotas.txt", "r");
    printf("\n"); 

    if (testa_abertura_dos_ficheiros(fp1, fp2)) {
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        return 1;
    }

    /* Carregar aeroportos */
    if (flag_aeroportos) {
        printf("NOTA: Aeroportos com formatacao errada sao descartados.\n\n");
    }
    while (!feof(fp1)) {
        aer = le_dados_aeroportos(fp1, &nconv1);
        if (nconv1 == 12 && validar_aeroporto(&aer) == 1) {
            insere_na_lista_aeroportos(&(ctx.aeroportos), aer, flag_aeroportos);
        }
    }

    /* Carregar rotas e calcular distâncias */
    while (!feof(fp2)) {
        rota = le_dados_rotas(fp2, &nconv2);
        if (nconv2 == 7 && validar_rota(&rota) == 1) {
            insere_na_lista_rotas(&(ctx.rotas), rota, ctx.aeroportos, flag_voos);
        }
    }
    calcula_distancia_rotas(ctx.aeroportos, ctx.rotas);

    /* ==========================================================
     * 3. LÓGICA DE EXECUÇÃO / PESQUISA E ORDENAÇÃO
     * ========================================================== */
    if (flag_aeroportos) {
        imprime_lista_aeroportos(ctx.aeroportos);
    } 
    else if (flag_voos) {
        imprime_lista_rotas(ctx.rotas);
    } 
    else if (escalas == 0) {
        ctx.rotas_diretas = voos_diretos_A_B(iata_p, iata_c, ctx.rotas);
        if (ordem_tempo == 1) ordenar_crescente(&(ctx.rotas_diretas));
        else if (ordem_tempo == 2) ordenar_decrescente(&(ctx.rotas_diretas));
        imprime_lista_rotas(ctx.rotas_diretas);
    } 
    else if (escalas == 1) {
        ctx.rotas_escala_1 = preencher_lista_voos_com_escala_1(iata_p, iata_c, ctx.rotas);
        remover_voos_escala_1(&(ctx.rotas_escala_1));
        if (ordem_tempo == 1) ordenar_crescente_com_escala(&(ctx.rotas_escala_1));
        else if (ordem_tempo == 2) ordenar_decrescente_com_escala(&(ctx.rotas_escala_1));
        if (ordem_dist == 1) ordenar_distancia_escala_1(ctx.rotas_escala_1);
        imprime_lista_voos_com_escala(ctx.rotas_escala_1);
    } 
    else if (escalas == 2) {
        ctx.rotas_escala_2 = criar_lista_voos_com_duas_escalas(ctx.rotas, iata_p, iata_c);
        remover_voos_escala_2(&(ctx.rotas_escala_2));
        if (ordem_tempo == 1) ordenar_crescente_escala_2(&(ctx.rotas_escala_2));
        else if (ordem_tempo == 2) ordenar_decrescente_escala_2(&(ctx.rotas_escala_2));
        if (ordem_dist == 1) ordenar_distancia_escala_2(ctx.rotas_escala_2);
        imprimir_lista_voos_com_duas_escalas(ctx.rotas_escala_2);
    }

    /* ==========================================================
     * 4. LIMPEZA (CLEANUP)
     * ========================================================== */
    limpa_listas(&ctx);
    if (fp1) fclose(fp1);
    if (fp2) fclose(fp2);
    
    return 0;
}