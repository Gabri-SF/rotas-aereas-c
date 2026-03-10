#ifndef MATEMATICA_H
#define MATEMATICA_H

#include "tipos.h"

double converte_graus_rad(double a);
double calcula_x(double lat, double lon);
double calcula_y(double lat, double lon);
double calcula_norma(double x, double y, double z);
double calcula_distancia_aeroportos(AEROPORTO a1, AEROPORTO a2);
void calcula_distancia_rotas(LISTA* topo_aer, BLOCO* topo_rotas);

#endif /* MATEMATICA_H */