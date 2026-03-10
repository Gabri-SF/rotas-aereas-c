#ifndef FICHEIROS_H
#define FICHEIROS_H

#include "tipos.h"

int testa_abertura_dos_ficheiros(FILE* fp1, FILE* fp2);
AEROPORTO le_dados_aeroportos(FILE* fp, int* nconv);
ROTA le_dados_rotas(FILE* fp, int* nconv);
int validar_aeroporto(AEROPORTO *aeroporto);
int validar_rota(ROTA *rota);

#endif /* FICHEIROS_H */